import paho.mqtt.client as mqtt
from core.state_machine import StateMachine

TOPIC_LEVEL = "tms/water_level"

class MqttHandler:
  def __init__(self, state_machine: StateMachine, broker: str, port: int = 1883):
    self.state_machine = state_machine
    self.broker = broker
    self.port = port
    self.client = mqtt.Client()

    self.client.on_connect = self._on_connect
    self.client.on_message = self._on_message

  def start(self):
    self.client.connect(self.broker, self.port)
    self.client.loop_start()

  def stop(self):
    self.client.loop_stop()
    self.client.disconnect()

  def _on_connect(self, client, _, __, rc):
    if rc == 0:
      client.subscribe(TOPIC_LEVEL)
    else:
      print(f"Failed: rc = {rc}")

  def _on_message(self, _, __, msg):
    payload = msg.payload.decode("utf-8").strip()
    token = payload.split()[0] if payload.split() else ""
    try:
      level = float(token)
    except ValueError:
      print(f"[MQTT] payload non valido: {payload!r}")
      return
    print(f"{level}")
    self.state_machine.update_level(level)
