import serial
import threading
import time
from core.state_machine import StateMachine, AUTOMATIC, MANUAL

WCS_MODE = {0: MANUAL, 1: AUTOMATIC}

# Reinvia lo stato al WCS almeno ogni HEARTBEAT secondi anche se invariato,
# cosi' un WCS appena avviato si allinea; altrimenti si invia solo sul cambio.
HEARTBEAT = 1.0

class SerialHandler:
  def __init__(self, state_machine: StateMachine, port: str, baud: int = 9600):
    self.state_machine = state_machine
    self.port = port
    self.baud = baud
    self.serial = None
    self.running = False
    self.thread = None
    self._last_sent_mode = None
    self._last_sent_valve = None
    self._last_send_time = 0.0

  def start(self):
    self.serial = serial.Serial(self.port, self.baud, timeout=1)
    self.running = True
    self.thread = threading.Thread(target=self._read_loop)
    self.thread.daemon = True
    self.thread.start()

  def stop(self):
    self.running = False
    if self.serial:
        self.serial.close()

  def send_command(self, command: str):
    if self.serial and self.serial.is_open:
      self.serial.write(f"{command}\n".encode())

  def send_state(self):
    state = self.state_machine.get_state()
    mode = state["mode"]
    valve = state["valve_percent"]

    now = time.time()
    changed = mode != self._last_sent_mode or valve != self._last_sent_valve
    if not changed and (now - self._last_send_time) < HEARTBEAT:
      return

    # Un concetto per riga, formato "CHIAVE:VALORE": il WCS li interpreta
    # entrambi e non dipende dall'ordine.
    self.send_command(f"MODE:{mode}")
    self.send_command(f"VALVE:{valve}")
    self._last_sent_mode = mode
    self._last_sent_valve = valve
    self._last_send_time = now


  def _read_loop(self):
    while self.running:
      try:
        line = self.serial.readline().decode().strip()
        if line:
          self._parse(line)
      except Exception as e:
        print(f"{e}")

  def _parse(self, line: str):
    print(f"{line}")
    if line == "TOGGLE":
      # Il bottone del WCS chiede di alternare la modalita'.
      self.state_machine.toggle_mode()
      self.send_state()
      return
    if line.startswith("STATUS:"):
      parts = line.split(":")
      if len(parts) == 3:
        try: 
          mode_raw = int(parts[1])
          valve = int (parts[2])
        except Exception:
          return
        mode = WCS_MODE.get(mode_raw)
        if mode is not None:
          self.state_machine.on_wcs_report(mode, valve)
          print(f"[Serial] Mode={mode} Valve={valve}%")