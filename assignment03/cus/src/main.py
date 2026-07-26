import threading
import time
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

L1 = float(os.getenv("L1", 0.50))
L2 = float(os.getenv("L2", 0.75))
T1 = float(os.getenv("T1", 5.0))
T2 = float(os.getenv("T2", 10.0))
TANK_MAX_CM = float(os.getenv("TANK_MAX_CM", 30.0))

LOOP_INTERVAL = 0.2  # secondi

def main():
  sm = StateMachine(l1=L1, l2=L2, t1=T1, t2=T2, tank_max_cm=TANK_MAX_CM)

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
      sm.update()
      serial.send_state()
      time.sleep(LOOP_INTERVAL)

  except KeyboardInterrupt:
    mqtt.stop()
    serial.stop()

if __name__ == "__main__":
  main()
