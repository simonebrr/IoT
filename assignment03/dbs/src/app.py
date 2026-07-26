import os
from flask import Flask
from routes.dashboard import dashboard

app = Flask(
  __name__,
  template_folder="templates",
  static_folder="static",
)

app.register_blueprint(dashboard)

if __name__ == "__main__":
  port = int(os.getenv("DBS_PORT", 8080))
  app.run(host="0.0.0.0", port=port, debug=True)