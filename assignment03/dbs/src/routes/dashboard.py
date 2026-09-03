from flask import Blueprint, jsonify, render_template, request
from services.cus_client import get_status, set_mode, set_valve

dashboard = Blueprint("dashboard", __name__)

CUS_UNAVAILABLE = 502
BAD_REQUEST = 400


@dashboard.route("/")
def index():
  return render_template("index.html")

@dashboard.route("/api/state")
def state():
  try:
    return jsonify(get_status())
  except Exception as e:
    return jsonify({"error": f"CUS unavailable: {e}"}), CUS_UNAVAILABLE

@dashboard.route("/api/mode", methods=["POST"])
def mode():
  data = request.get_json(force=True, silent=True) or {}
  try:
    return jsonify(set_mode(data.get("mode")))
  except Exception as e:
    return jsonify({"error": f"CUS unavailable: {e}"}), CUS_UNAVAILABLE

@dashboard.route("/api/valve", methods=["POST"])
def valve():
  data = request.get_json(force=True, silent=True) or {}
  raw = data.get("percent")
  if raw is None:
    return jsonify({"error": "missing 'percent'"}), BAD_REQUEST
  try:
    percent = int(raw)
  except (TypeError, ValueError):
    return jsonify({"error": "invalid 'percent'"}), BAD_REQUEST
  try:
    return jsonify(set_valve(percent))
  except Exception as e:
    return jsonify({"error": f"CUS unavailable: {e}"}), CUS_UNAVAILABLE