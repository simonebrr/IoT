import time

# Livelli e tempi
L1 = 0.50  # 50%
L2 = 0.75  # 75%
T1 = 5.0   # secondi
T2 = 10.0  # secondi

AUTOMATIC = "AUTOMATIC"
MANUAL = "MANUAL"
UNCONNECTED = "UNCONNECTED"


class StateMachine:
  def __init__(self):
    self.mode = AUTOMATIC
    self.valve_percent = 0
    self.water_level = 0.0
    self.last_data_time = time.time()
    self.above_l1_since = None

  def update_level(self, level:float) :
    self.water_level = level
    self.last_data_time = time.time()

    if self.mode == MANUAL:
      return

    self._apply_policy()

  def _apply_policy(self):
    now = time.time()

    if now - self.last_data_time > T2:
      self.mode = UNCONNECTED
      return

    if self.mode == UNCONNECTED:
      self.mode = AUTOMATIC

    if self.water_level >= L2:
      self.valve_percent = 100
      self.above_l1_since = None

    elif self.water_level >= L1:
      if self.above_l1_since is None:
        self.above_l1_since = now
      elif now - self.above_l1_since >= T1:
        self.valve_percent = 50

    else:
      self.valve_percent = 0
      self.above_l1_since = None

  def set_mode(self, mode:str):
    self.mode = mode

  def set_valve(self, percent: int):
    if self.mode == MANUAL:
      self.valve_percent = percent

  def get_state(self):
    return {
      "mode": self.mode,
      "valve_percent": self.valve_percent,
      "water_level": self.water_level,
      "last_data_time": self.last_data_time
      }