from cereal import car, log

from opendbc.car.hyundai.values import HyundaiFlags

MAX_REBOOT_WHILE_STARTED_SPEED = 0.1


def _car_flags(CP: car.CarParams) -> int:
  return int(getattr(CP, "flags", 0))


def is_hyundai_canfd_openpilot_longitudinal(CP: car.CarParams) -> bool:
  return (
    getattr(CP, "brand", "") == "hyundai" and
    bool(getattr(CP, "openpilotLongitudinalControl", False)) and
    bool(_car_flags(CP) & int(HyundaiFlags.CANFD))
  )


def should_deinit_on_shutdown(CP: car.CarParams) -> bool:
  return is_hyundai_canfd_openpilot_longitudinal(CP)


def can_reboot_while_started(CP: car.CarParams, selfdrive_state: log.SelfdriveState,
                             car_state: car.CarState, *, messages_alive: bool) -> bool:
  if not messages_alive or not should_deinit_on_shutdown(CP):
    return False

  if bool(getattr(selfdrive_state, "enabled", False)):
    return False

  if bool(car_state.cruiseState.enabled):
    return False

  return bool(car_state.standstill) or abs(float(car_state.vEgo)) <= MAX_REBOOT_WHILE_STARTED_SPEED
