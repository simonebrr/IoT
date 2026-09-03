import time
from collections import deque

AUTOMATIC = "AUTOMATIC"
MANUAL = "MANUAL"
UNCONNECTED = "UNCONNECTED"

HISTORY_SIZE = 30

class StateMachine:
  def __init__(self, l1=0.50, l2=0.75, t1=5.0, t2=10.0, tank_max_cm=30.0):
    self.L1 = l1
    self.L2 = l2
    self.T1 = t1
    self.T2 = t2
    self.tank_max_cm = tank_max_cm

    # La modalita' di avvio del sistema e' AUTOMATIC (da specifica).
    self.mode = AUTOMATIC
    self._prev_mode = AUTOMATIC
    self.valve_percent = 0
    self.level = 0.0
    self.connected = False
    self.last_data_time = 0.0
    self.above_l1_since = None
    self.history = deque(maxlen=HISTORY_SIZE)

    # Ultimi valori riportati dal WCS: servono per reagire solo quando il WCS
    # cambia davvero (bottone/potenziometro), non a ogni report ripetuto, cosi'
    # i comandi dalla dashboard non vengono sovrascritti dallo stream seriale.
    self._last_wcs_mode = None
    self._last_wcs_valve = None

  def _distance_to_level(self, distance_cm):

    fill = (self.tank_max_cm - distance_cm) / self.tank_max_cm
    return max(0.0, min(1.0, fill))

  def update_level(self, distance_cm):
    self.level = self._distance_to_level(distance_cm)
    self.last_data_time = time.time()
    self.history.append(round(self.level * 100, 1))
    self._apply_policy()

  def update(self):
    self._apply_policy()

  def _apply_policy(self):
    now = time.time()
    stale = self.last_data_time == 0.0 or (now - self.last_data_time > self.T2)

    if stale:
      self.connected = False
      if self.mode != UNCONNECTED:
        self._prev_mode = self.mode
        self.mode = UNCONNECTED
      return

    self.connected = True
    if self.mode == UNCONNECTED:
      self.mode = self._prev_mode

    if self.mode != AUTOMATIC:
      return

    if self.level >= self.L2:
      self.valve_percent = 100
      self.above_l1_since = None
    elif self.level >= self.L1:
      if self.above_l1_since is None:
        self.above_l1_since = now
      elif now - self.above_l1_since >= self.T1:
        self.valve_percent = 50
    else:
      self.valve_percent = 0
      self.above_l1_since = None

  def set_mode(self, mode):
    if mode not in (AUTOMATIC, MANUAL):
      return
    self._prev_mode = mode
    if self.mode != UNCONNECTED:
      self.mode = mode
    if mode == AUTOMATIC:
      self.above_l1_since = None

  def toggle_mode(self):
    # Richiesto dal bottone del WCS: alterna AUTOMATIC/MANUAL. Il CUS e'
    # l'autorita' sulla modalita', quindi il WCS non cambia stato da solo.
    base = self.mode if self.mode != UNCONNECTED else self._prev_mode
    self.set_mode(MANUAL if base == AUTOMATIC else AUTOMATIC)

  def set_valve(self, percent):
    if self.mode == MANUAL:
      self.valve_percent = max(0, min(100, int(percent)))

  def on_wcs_report(self, mode, valve_percent):
    # Adotta la modalita' del WCS solo quando il WCS l'ha appena cambiata
    # (fronte di salita), non a ogni report: altrimenti il flusso continuo di
    # STATUS riporterebbe subito indietro un cambio fatto dalla dashboard.
    if self._last_wcs_mode is not None and mode != self._last_wcs_mode:
      self.set_mode(mode)
    self._last_wcs_mode = mode

    # Stessa logica per la valvola in MANUAL: applica il valore del
    # potenziometro solo quando cambia, cosi' lo slider della dashboard regge.
    if self.mode == MANUAL:
      try:
        valve = max(0, min(100, int(valve_percent)))
      except (TypeError, ValueError):
        valve = None
      if valve is not None and valve != self._last_wcs_valve:
        self.valve_percent = valve
    self._last_wcs_valve = valve_percent

  def get_state(self):
    return {
      "mode": self.mode,
      "valve_percent": self.valve_percent,
      "level_percent": round(self.level * 100, 1),
      "connected": self.connected,
      "history": list(self.history),
      "last_data_time": self.last_data_time,
    }