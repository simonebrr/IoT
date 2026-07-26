import os
import requests

CUS_URL = os.getenv("CUS_URL", "http://localhost:5000")
TIMEOUT = 2


def get_status():
  r = requests.get(f"{CUS_URL}/api/state", timeout=TIMEOUT)
  r.raise_for_status()
  return r.json()

def set_mode(mode):
  r = requests.post(f"{CUS_URL}/api/mode", json={"mode": mode}, timeout=TIMEOUT)
  r.raise_for_status()
  return r.json()

def set_valve(percent):
  r = requests.post(f"{CUS_URL}/api/valve", json={"percent": percent}, timeout=TIMEOUT)
  r.raise_for_status()
  return r.json()
