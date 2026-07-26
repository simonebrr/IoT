import requests

CUS_URL = "http://localhost:8080"

def get_status():
  response = requests.get(f"{CUS_URL}/status")
  return response.json()