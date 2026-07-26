import threading
import os
from dotenv import load_dotenv
from core.state_machine import StateMachine
from mqtt.mqtt_handler import MqttHandler
from serial.serial_handler import SerialHandler
import http.http_server as http_server

load_dotenv()

MQTT_BROKER = os.getenv("MQTT_BROKER", "localhost")
MQTT_PORT = int(os.getenv("MQTT_PORT", 1883))
SERIAL_PORT = os.getenv("SERIAL_PORT", "/dev/ttyUSB0")
SERIAL_BAUD = int(os.getenv("SERIAL_BAUD", 9600))
HTTP_HOST = os.getenv("HTTP_HOST", "0.0.0.0")
HTTP_PORT = int(os.getenv("HTTP_PORT", 5000))

def main():
  sm = StateMachine()

  mqtt = MqttHandler(sm, MQTT_BROKER, MQTT_PORT)
  serial = SerialHandler(sm, SERIAL_PORT, SERIAL_BAUD)

  http_server.init(sm, serial)

  mqtt.start()
  serial.start()

  thread = threading.Thread(target=lambda: http_server.start(HTTP_HOST, HTTP_PORT))
  thread.daemon = True
  thread.start()

  try:
    while True:
      sm._apply_policy()
      serial.send_state()

  except KeyboardInterrupt:
    mqtt.stop()
    serial.stop()

if __name__ == "__main__":
  main()
