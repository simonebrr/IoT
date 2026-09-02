const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const cors = require('cors');
const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');
require('dotenv').config();

const app = express();
const server = http.createServer(app);
const io = socketIo(server, {
  cors: { origin: '*', methods: ['GET', 'POST'] }
});

app.use(cors());
app.use(express.json());
app.use(express.static('public'));

const SERIAL_PORT = process.env.SERIAL_PORT || '/dev/ttyUSB0';
const BAUD_RATE = parseInt(process.env.BAUD_RATE) || 9600;
const SERVER_PORT = process.env.SERVER_PORT || 3001;

let serialPort;
let parser;
let lastTelemetry = null;
let rxTotal = 0;

// "STATE:DRONE_INSIDE,TEMP:24.5,DIST:12.3,PREALARM:0,ALARM:0"
function parseTelemetry(line) {
  const data = {};
  line.split(',').forEach((pair) => {
    const idx = pair.indexOf(':');
    if (idx <= 0) return;
    const key = pair.slice(0, idx).trim().toLowerCase();
    const value = pair.slice(idx + 1).trim();
    if (key) data[key] = value;
  });

  const alarm = data.alarm === '1';
  const preAlarm = data.prealarm === '1';
  const hangar = alarm ? 'ALARM' : preAlarm ? 'PREALARM' : 'NORMAL';

  return {
    state: data.state || 'UNKNOWN',
    hangar,
    distance: data.dist !== undefined ? parseFloat(data.dist) : null,
    temperature: data.temp !== undefined ? parseFloat(data.temp) : null,
    pir: data.pir !== undefined ? data.pir === '1' : null,
    prealarm: preAlarm,
    alarm,
    seq: data.seq !== undefined ? parseInt(data.seq, 10) : null
  };
}
let lastAt = 0;
function handleSerialLine(line) {
  const msg = line.trim();
  if (msg.length === 0) return;
  const now = Date.now();
  console.log(`+${lastAt ? now - lastAt : 0}ms  ${msg}`);
  lastAt = now;

  if (msg.includes('STATE:')) {
    rxTotal++;
    lastTelemetry = parseTelemetry(msg);
    io.emit('hangar:telemetry', lastTelemetry);
  } else {
    console.log('[hangar]', msg);
  }
}

function initSerial() {
  try {
    serialPort = new SerialPort({ path: SERIAL_PORT, baudRate: BAUD_RATE });

    parser = serialPort.pipe(new ReadlineParser({ delimiter: '\n' }));
    parser.on('data', handleSerialLine);

    serialPort.on('open', () => {
      io.emit('hangar:connected', { port: SERIAL_PORT, baudRate: BAUD_RATE });
      console.log('Serial open on', SERIAL_PORT, '@', BAUD_RATE);
    });

    serialPort.on('error', (err) => {
      console.error('Serial error:', err.message);
      io.emit('hangar:error', { error: err.message });
    });

    serialPort.on('close', () => {
      console.warn('Serial closed, retry in 2s');
      io.emit('hangar:disconnected');
      setTimeout(reopenSerial, 2000);
    });
  } catch (err) {
    console.error('Serial init failed:', err.message);
    setTimeout(reopenSerial, 2000);
  }
}

function reopenSerial() {
  if (!serialPort) return initSerial();
  if (serialPort.isOpen) return;
  serialPort.open((err) => {
    if (err) setTimeout(reopenSerial, 2000);
  });
}

function sendCommand(command) {
  if (serialPort && serialPort.isOpen) {
    serialPort.write(command + '\n', (err) => {
      if (err) console.error('Write error:', err.message);
      else console.log('Sent:', command);
    });
    return true;
  }
  console.error('Cannot send, serial port not open');
  return false;
}

io.on('connection', (socket) => {
  // Push the latest known status
  if (serialPort && serialPort.isOpen) {
    socket.emit('hangar:connected', { port: SERIAL_PORT, baudRate: BAUD_RATE });
  } else {
    socket.emit('hangar:disconnected');
  }
  if (lastTelemetry) socket.emit('hangar:telemetry', lastTelemetry);

  socket.on('drone:takeoff', () => sendCommand('CMD:TAKEOFF'));
  socket.on('drone:land', () => sendCommand('CMD:LAND'));
  socket.on('drone:reset', () => sendCommand('CMD:RESET'));
});

// REST
app.post('/api/takeoff', (req, res) => res.json({ ok: sendCommand('CMD:TAKEOFF') }));
app.post('/api/land', (req, res) => res.json({ ok: sendCommand('CMD:LAND') }));
app.post('/api/reset', (req, res) => res.json({ ok: sendCommand('CMD:RESET') }));
app.get('/api/status', (req, res) =>
  res.json({
    connected: !!(serialPort && serialPort.isOpen),
    framesReceived: rxTotal,
    telemetry: lastTelemetry
  })
);

initSerial();

server.listen(SERVER_PORT, '0.0.0.0', () => {
  console.log(`DRU web GUI on http://localhost:${SERVER_PORT}`);
});

module.exports = app;