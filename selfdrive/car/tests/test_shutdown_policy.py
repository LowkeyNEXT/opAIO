from cereal import car, log

from opendbc.car.hyundai.values import HyundaiFlags

from openpilot.selfdrive.car.shutdown_policy import (
  can_reboot_while_started,
  should_deinit_on_shutdown,
)


def make_cp(*, brand="hyundai", flags=HyundaiFlags.CANFD, op_long=True):
  cp = car.CarParams.new_message()
  cp.brand = brand
  cp.flags = int(flags)
  cp.openpilotLongitudinalControl = op_long
  return cp


def make_car_state(*, v_ego=0.0, standstill=True, cruise_enabled=False):
  cs = car.CarState.new_message()
  cs.vEgo = v_ego
  cs.standstill = standstill
  cs.cruiseState.enabled = cruise_enabled
  return cs


def make_selfdrive_state(*, enabled=False):
  ss = log.SelfdriveState.new_message()
  ss.enabled = enabled
  return ss


def test_shutdown_deinit_is_needed_for_hyundai_canfd_openpilot_long():
  assert should_deinit_on_shutdown(make_cp())


def test_shutdown_deinit_is_not_needed_without_hyundai_canfd_openpilot_long():
  assert not should_deinit_on_shutdown(make_cp(op_long=False))
  assert not should_deinit_on_shutdown(make_cp(flags=0))
  assert not should_deinit_on_shutdown(make_cp(brand="toyota"))


def test_started_reboot_allowed_when_hyundai_canfd_is_disabled_and_stopped():
  assert can_reboot_while_started(make_cp(), make_selfdrive_state(), make_car_state(), messages_alive=True)


def test_started_reboot_blocked_when_missing_safe_state_or_not_hyundai_canfd():
  cp = make_cp()

  assert not can_reboot_while_started(cp, make_selfdrive_state(enabled=True), make_car_state(), messages_alive=True)
  assert not can_reboot_while_started(cp, make_selfdrive_state(), make_car_state(v_ego=0.5, standstill=False), messages_alive=True)
  assert not can_reboot_while_started(cp, make_selfdrive_state(), make_car_state(cruise_enabled=True), messages_alive=True)
  assert not can_reboot_while_started(cp, make_selfdrive_state(), make_car_state(), messages_alive=False)
  assert not can_reboot_while_started(make_cp(flags=0), make_selfdrive_state(), make_car_state(), messages_alive=True)
