from flask import Flask, jsonify, request
from core.state_machine import StateMachine, AUTOMATIC, MANUAL
from serial.serial_handler import SerialHandler

app = Flask(__name__)
state_machine: StateMachine
serial_handler: SerialHandler

def init(sm: StateMachine, serial: SerialHandler):
    global state_machine, serial_handler
    state_machine = sm
    serial_handler = serial

@app.route("/api/state", methods=["GET"])
def get_state():
    return jsonify(state_machine.get_state())

@app.route("/api/mode", methods=["POST"])
def set_mode():
    data = request.json
    mode = data.get("mode")
    if mode not in [AUTOMATIC, MANUAL]:
        return jsonify({"error": "Invalid"}), 400
    state_machine.set_mode(mode)
    serial_handler.send_state()
    return jsonify({"mode": mode})

@app.route("/api/valve", methods=["POST"])
def set_valve():
    data = request.json
    percent = data.get("percent")
    if percent is None or not (0 <= percent <= 100):
        return jsonify({"error": "Invalid"}), 400
    state_machine.set_valve(percent)
    serial_handler.send_state()
    return jsonify({"valve_percent": percent})

def start(host: str = "0.0.0.0", port: int = 5000):
    app.run(host=host, port=port)