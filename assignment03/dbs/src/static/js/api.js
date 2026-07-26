async function updateStatus() {

  try {

    let response = await fetch("/api/state");
    let data = await response.json();

    document.getElementById("state").innerHTML = data.mode;
    document.getElementById("level").innerHTML = data.water_level;
    document.getElementById("valve").innerHTML = data.valve_percent;

  } catch (error) {

    document.getElementById("state").innerHTML = "ERROR";
  }
}


setInterval(updateStatus, 1000);

updateStatus();