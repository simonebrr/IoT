from flask import Blueprint, jsonify, render_template, request
from services.cus_client import get_status, set_mode, set_valve

dashboard = Blueprint("dashboard", __name__)


@dashboard.route("/")
def index():
  return render_template("index.html")

@dashboard.route("/api/state")
def state():
  try:
    return jsonify(get_status())
  except Exception:
    return jsonify({"Error"})

@dashboard.route("/api/mode", methods=["POST"])
def mode():
  data = request.get_json(force=True, silent=True) or {}
  try:
    return jsonify(set_mode(data.get("mode")))
  except Exception:
    return jsonify(f"Error")

@dashboard.route("/api/valve", methods=["POST"])
def valve():
  data = request.get_json(force= True, silent=True) or {}
  try:
    return jsonify(set_valve(int(data.get("percent"))))
  except Exception:
    return jsonify(f"Error")