from flask import Blueprint, jsonify
from services.cus_client import get_status


dashboard = Blueprint(
  "dashbord",
 __name__
)

@dashboard.route("/api/state")
def state():
  return jsonify(get_status())