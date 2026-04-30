import hashlib
import os
import requests
import zstandard as zstd

from pathlib import Path

from cereal import car, log
from openpilot.common.params import Params
from openpilot.common.utils import LOG_COMPRESSION_LEVEL
from openpilot.system.hardware.hw import Paths
from openpilot.system.version import get_build_metadata

from openpilot.frogpilot.common.frogpilot_variables import FROGPILOT_API, HD_LOGS_PATH, KONIK_LOGS_PATH

API_BASE = f"{FROGPILOT_API}/telemetry"
API_HEADERS = {"Content-Type": "application/json", "User-Agent": "frogpilot-api/1.0"}

HTTP_TIMEOUT = 15
LEAD_TRACKED_MIN_PCT = 0.20
MAX_BLOB_BYTES = 64 * 1024 * 1024
MAX_MODEL_LEADS = 2
MAX_SEGMENTS_PER_RUN = 50
MIN_ACTIVE_FRAMES = 100
SPEED_BIN_HIGH = 15.0
SPEED_BIN_MID = 5.0
SPEED_BIN_STOPPED = 0.5
STANDSTILL_RESET_SPEED = 0.1
UPLOAD_TIMEOUT = 60

LOGS_PATHS = tuple(dict.fromkeys((Path(Paths.log_root()), Path("/data/media/0/realdata"), HD_LOGS_PATH, KONIK_LOGS_PATH)))

RLOG_NAME = "rlog.zst"
TLOG_NAME = "tlog.zst"
TLOG_PROCESSED_MARKER = "tlog.uploaded"

CAR_CONTROL_FIELDS = (
  "enabled", "latActive", "longActive",
  ("actuators", ("accel", "longControlState")),
)
CAR_STATE_FIELDS = (
  "aEgo", "brakePressed", "gasPressed", "standstill", "vCruise", "vEgo",
  ("cruiseState", ("enabled", "speed", "standstill")),
)
CONTROLS_STATE_FIELDS = ("forceDecel", "longControlState", "ufAccelCmd", "uiAccelCmd", "upAccelCmd")
FROGPILOT_CAR_STATE_FIELDS = ("trafficModeEnabled",)
FROGPILOT_PLAN_FIELDS = (
  "accelerationJerk", "dangerFactor", "dangerJerk", "desiredFollowDistance", "maxAcceleration",
  "minAcceleration", "speedJerk", "tFollow", "trackingLead", "vCruise",
)
LEAD_FIELDS = ("aLeadK", "aLeadTau", "aRel", "dRel", "fcw", "modelProb", "radar", "status", "vLead", "vLeadK", "vRel")
LIVE_CALIBRATION_FIELDS = ("calPerc", "calStatus", "rpyCalib")
LIVE_DELAY_FIELDS = ("lateralDelay", "lateralDelayEstimate", "status")
LONGITUDINAL_PLAN_FIELDS = (
  "accels", "allowBrake", "allowThrottle", "aTarget", "fcw", "hasLead", "jerks",
  "longitudinalPlanSource", "shouldStop", "speeds",
)
MODEL_LEAD_FIELDS = ("a", "prob", "probTime", "t", "v", "x")
MODEL_V2_FIELDS = (
  ("acceleration", ("x",)),
  ("action", ("desiredAcceleration", "shouldStop")),
  ("leadsV3", MODEL_LEAD_FIELDS, MAX_MODEL_LEADS),
  ("position", ("x",)),
  ("velocity", ("x",)),
)
RADAR_ERRORS_FIELDS = ("canError", "radarFault", "radarUnavailableTemporary", "wrongConfig")
RADAR_STATE_FIELDS = (
  ("leadOne", LEAD_FIELDS),
  ("leadTwo", LEAD_FIELDS),
  ("radarErrors", RADAR_ERRORS_FIELDS),
)
SELFDRIVE_STATE_FIELDS = ("active", "enabled", "engageable", "experimentalMode", "personality", "state")

EVENT_FIELDS = {
  "carControl": CAR_CONTROL_FIELDS,
  "carState": CAR_STATE_FIELDS,
  "controlsState": CONTROLS_STATE_FIELDS,
  "frogpilotCarState": FROGPILOT_CAR_STATE_FIELDS,
  "frogpilotPlan": FROGPILOT_PLAN_FIELDS,
  "liveCalibration": LIVE_CALIBRATION_FIELDS,
  "liveDelay": LIVE_DELAY_FIELDS,
  "longitudinalPlan": LONGITUDINAL_PLAN_FIELDS,
  "modelV2": MODEL_V2_FIELDS,
  "radarState": RADAR_STATE_FIELDS,
  "selfdriveState": SELFDRIVE_STATE_FIELDS,
}
KEPT_EVENT_TYPES = frozenset(EVENT_FIELDS)

def build_sweep_metadata(frogpilot_toggles):
  metadata = {"frogpilot_version": get_build_metadata().openpilot.git_commit[:12]}

  cp_bytes = Params().get("CarParamsPersistent")
  if cp_bytes:
    with car.CarParams.from_bytes(cp_bytes) as CP:
      if CP.brand:
        metadata["device_brand"] = CP.brand

  metadata["slider_config"] = {
    "acceleration_profile": frogpilot_toggles.acceleration_profile,
    "custom_personalities": frogpilot_toggles.custom_personalities,
    "deceleration_profile": frogpilot_toggles.deceleration_profile,
    "human_acceleration": frogpilot_toggles.human_acceleration,
    "human_following": frogpilot_toggles.human_following,
    "increase_stopped_distance": frogpilot_toggles.increase_stopped_distance,
    "traffic_mode_follow": frogpilot_toggles.traffic_mode_follow[0],
    "traffic_mode_jerk_acceleration": frogpilot_toggles.traffic_mode_jerk_acceleration[0],
    "traffic_mode_jerk_danger": frogpilot_toggles.traffic_mode_jerk_danger[0],
    "traffic_mode_jerk_deceleration": frogpilot_toggles.traffic_mode_jerk_deceleration[0],
    "traffic_mode_jerk_speed": frogpilot_toggles.traffic_mode_jerk_speed[0],
    "traffic_mode_jerk_speed_decrease": frogpilot_toggles.traffic_mode_jerk_speed_decrease[0],
  }
  return metadata

def copy_field(src, dst, name):
  value = getattr(src, name)
  if hasattr(value, "__iter__") and not isinstance(value, (bytes, str)):
    value = list(value)
  setattr(dst, name, value)

def copy_fields(src, dst, fields):
  for field in fields:
    if isinstance(field, str):
      copy_field(src, dst, field)
      continue

    name, child_fields, *limit = field
    if not limit:
      copy_fields(getattr(src, name), getattr(dst, name), child_fields)
      continue

    src_items = getattr(src, name)
    dst_items = dst.init(name, min(len(src_items), limit[0]))
    for index, dst_item in enumerate(dst_items):
      copy_fields(src_items[index], dst_item, child_fields)

def filter_segment(rlog_path, tlog_path):
  raw = zstd.ZstdDecompressor().decompress(rlog_path.read_bytes(), max_output_size=512 * 1024 * 1024)

  kept = bytearray()
  traffic_mode_active = False
  traffic_mode_seen = False

  active_frames = 0
  high_frames = 0
  lead_tracked_frames = 0
  manual_takeover_count = 0
  mid_frames = 0
  slow_frames = 0
  stop_go_transitions = 0
  stopped_frames = 0
  v_egos = []

  last_lead_status = False
  last_long_active = False
  was_stopped = True

  for event in log.Event.read_multiple_bytes(raw):
    which = event.which()

    if which == "carControl":
      last_long_active = event.carControl.longActive
    elif which == "radarState":
      last_lead_status = event.radarState.leadOne.status

    if traffic_mode_active and which == "carState":
      cs = event.carState
      v = cs.vEgo
      active_frames += 1
      v_egos.append(v)
      if v < SPEED_BIN_STOPPED:
        stopped_frames += 1
      elif v < SPEED_BIN_MID:
        slow_frames += 1
      elif v < SPEED_BIN_HIGH:
        mid_frames += 1
      else:
        high_frames += 1
      if last_lead_status:
        lead_tracked_frames += 1
      if was_stopped and v > SPEED_BIN_STOPPED:
        stop_go_transitions += 1
        was_stopped = False
      elif v < STANDSTILL_RESET_SPEED:
        was_stopped = True
      if last_long_active and (cs.gasPressed or cs.brakePressed):
        manual_takeover_count += 1

    if which not in KEPT_EVENT_TYPES:
      continue

    if which == "frogpilotCarState":
      was_active = traffic_mode_active
      traffic_mode_active = event.frogpilotCarState.trafficModeEnabled
      traffic_mode_seen |= traffic_mode_active
      if not traffic_mode_active and not (traffic_mode_seen and was_active):
        continue
    elif not traffic_mode_active:
      continue

    sanitized = sanitize_event(event, which)
    if sanitized is not None:
      kept.extend(sanitized.to_bytes())

  if not kept or active_frames < MIN_ACTIVE_FRAMES:
    return None

  pct_lead_tracked = lead_tracked_frames / active_frames
  if pct_lead_tracked < LEAD_TRACKED_MIN_PCT:
    return None

  v_egos.sort()

  tlog_path.write_bytes(zstd.ZstdCompressor(level=LOG_COMPRESSION_LEVEL).compress(bytes(kept)))

  return {
    "manual_takeover_count": manual_takeover_count,
    "pct_high": high_frames / active_frames,
    "pct_lead_tracked": pct_lead_tracked,
    "pct_mid": mid_frames / active_frames,
    "pct_slow": slow_frames / active_frames,
    "pct_stopped": stopped_frames / active_frames,
    "stop_go_transitions": stop_go_transitions,
    "v_ego_p50": v_egos[len(v_egos) // 2],
  }

def find_completed_segments():
  segments = []
  for base in LOGS_PATHS:
    for name in listdir_by_creation(str(base)):
      seg_dir = base / name
      if (seg_dir / RLOG_NAME).is_file() and not has_lock_file(seg_dir):
        segments.append(seg_dir)

  return segments

def get_directory_sort(path):
  prefix = ["0"] if path.startswith("2024-") else ["1"]
  return prefix + [part.rjust(10, "0") for part in path.rsplit("--", 1)]

def has_lock_file(path):
  try:
    return any(name.endswith(".lock") for name in os.listdir(path))
  except OSError:
    return True

def listdir_by_creation(path):
  if not os.path.isdir(path):
    return []

  try:
    paths = [name for name in os.listdir(path) if os.path.isdir(os.path.join(path, name))]
  except OSError:
    return []
  return sorted(paths, key=get_directory_sort)

def run_offroad_sweep(frogpilot_toggles):
  sweep_metadata = build_sweep_metadata(frogpilot_toggles)
  segments_uploaded = 0
  for seg_dir in find_completed_segments():
    if segments_uploaded >= MAX_SEGMENTS_PER_RUN:
      break

    processed_marker_path = seg_dir / TLOG_PROCESSED_MARKER
    if processed_marker_path.is_file():
      continue

    rlog_path = seg_dir / RLOG_NAME
    tlog_path = seg_dir / TLOG_NAME

    try:
      stats = filter_segment(rlog_path, tlog_path)
    except Exception as error:
      print(f"Telemetry filter failed: {error}")
      continue

    if stats is None:
      processed_marker_path.touch(exist_ok=True)
      continue

    if tlog_path.stat().st_size > MAX_BLOB_BYTES:
      tlog_path.unlink(missing_ok=True)
      processed_marker_path.touch(exist_ok=True)
      continue

    if upload_segment(tlog_path, sweep_metadata, stats):
      processed_marker_path.touch(exist_ok=True)
      tlog_path.unlink(missing_ok=True)
      segments_uploaded += 1

def sanitize_event(event, which):
  sanitized = log.Event.new_message(valid=event.valid, logMonoTime=event.logMonoTime)
  sanitized.init(which)
  copy_fields(getattr(event, which), getattr(sanitized, which), EVENT_FIELDS[which])
  return sanitized

def upload_segment(tlog_path, sweep_metadata, segment_stats):
  blob = tlog_path.read_bytes()
  if not blob:
    return False

  payload = {
    "byte_count": len(blob),
    "regime_stats": segment_stats,
    "route_id": hashlib.sha256(blob).hexdigest()[:32],
    "segment_id": 0,
    **sweep_metadata,
  }

  try:
    init_response = requests.post(f"{API_BASE}/upload", json=payload, headers=API_HEADERS, timeout=HTTP_TIMEOUT)
  except requests.exceptions.RequestException as error:
    print(f"Telemetry upload init failed: {error}")
    return False

  if init_response.status_code == 409:
    return True
  if init_response.status_code != 201:
    print(f"Telemetry upload init {init_response.status_code}: {init_response.text[:200]}")
    return False

  signed_url = init_response.json().get("signed_url")
  if not signed_url:
    return False

  try:
    put_response = requests.put(signed_url, data=blob, headers={"Content-Type": "application/zstd"}, timeout=UPLOAD_TIMEOUT)
  except requests.exceptions.RequestException as error:
    print(f"Telemetry upload PUT failed: {error}")
    return False

  return put_response.status_code in (200, 201)
