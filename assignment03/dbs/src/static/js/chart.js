function drawChart(canvasId, data) {
  const canvas = document.getElementById(canvasId);
  if (!canvas) return;
  const ctx = canvas.getContext("2d");
  const W = canvas.width;
  const H = canvas.height;
  const pad = 30;

  ctx.clearRect(0, 0, W, H);

  // assi
  ctx.strokeStyle = "#bbb";
  ctx.lineWidth = 1;
  ctx.beginPath();
  ctx.moveTo(pad, 5);
  ctx.lineTo(pad, H - pad);
  ctx.lineTo(W - 5, H - pad);
  ctx.stroke();

  ctx.fillStyle = "#888";
  ctx.font = "11px sans-serif";
  [0, 50, 100].forEach((v) => {
    const y = H - pad - (v / 100) * (H - pad - 5);
    ctx.strokeStyle = "#eee";
    ctx.beginPath();
    ctx.moveTo(pad, y);
    ctx.lineTo(W - 5, y);
    ctx.stroke();
    ctx.fillText(v.toString(), 6, y + 4);
  });

  if (!data || data.length === 0) return;

  // linea dei dati
  const plotW = W - pad - 5;
  const plotH = H - pad - 5;
  const step = data.length > 1 ? plotW / (data.length - 1) : 0;

  ctx.strokeStyle = "#1976d2";
  ctx.lineWidth = 2;
  ctx.beginPath();
  data.forEach((v, i) => {
    const x = pad + i * step;
    const y = H - pad - (Math.max(0, Math.min(100, v)) / 100) * plotH;
    if (i === 0) ctx.moveTo(x, y);
    else ctx.lineTo(x, y);
  });
  ctx.stroke();
}
