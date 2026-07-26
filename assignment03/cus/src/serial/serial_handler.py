import serial
import threading
from core.state_machine import StateMachine, AUTOMATIC, MANUAL

WCS_MODE = {0: MANUAL, 1: AUTOMATIC}

class SerialHandler:
  def __init__(self, state_machine: StateMachine, port: str, baud: int = 9600):
    self.state_machine = state_machine
    self.port = port
    self.baud = baud
    self.serial = None
    self.running = False
    self.thread = None

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
    angle = int(valve * 90 / 100)

    self.send_command(mode)
    self.send_command(f"ANGLE:{angle}")


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