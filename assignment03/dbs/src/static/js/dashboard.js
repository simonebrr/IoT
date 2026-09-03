let sliderDragging = false;
let currentMode = null;

async function updateStatus() {
  try {
    const response = await fetch("/api/state");
    if (!response.ok) throw new Error("bad status");
    const data = await response.json();

    if (data.error) throw new Error(data.error);

    currentMode = data.mode;
    setBadge(data.mode, data.connected);
    document.getElementById("level").innerHTML = fmt(data.level_percent);
    document.getElementById("valve").innerHTML = fmt(data.valve_percent);

    // lo slider e' attivo solo in manual, non lo aggiorno mentre l'utente trascina
    const slider = document.getElementById("slider");
    const manual = data.mode === "MANUAL";
    slider.disabled = !manual;
    if (!sliderDragging) {
      slider.value = data.valve_percent;
      document.getElementById("slider-value").innerHTML = data.valve_percent;
    }

    highlightModeButtons(data.mode);
    drawChart("chart", data.history || []);
  } catch (error) {
    setBadge("NOT AVAILABLE", false);
  }
}

function fmt(v) {
  return v === undefined || v === null ? "---" : v;
}

function setBadge(text, connected) {
  const el = document.getElementById("state");
  el.innerHTML = text;
  el.className = "badge " + (connected ? "ok" : "warn");
}

function highlightModeButtons(mode) {
  document.getElementById("btn-auto").classList.toggle("active", mode === "AUTOMATIC");
  document.getElementById("btn-manual").classList.toggle("active", mode === "MANUAL");
}

async function setMode(mode) {
  await fetch("/api/mode", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ mode: mode }),
  });
  updateStatus();
}

function onSliderInput(value) {
  sliderDragging = true;
  document.getElementById("slider-value").innerHTML = value;
}

async function setValve(value) {
  sliderDragging = false;
  await fetch("/api/valve", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ percent: parseInt(value, 10) }),
  });
  updateStatus();
}

setInterval(updateStatus, 1000);
updateStatus();
