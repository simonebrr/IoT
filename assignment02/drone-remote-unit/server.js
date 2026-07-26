// Drone Remote Unit (DRU)
// PC subsystem: talks to the Arduino hangar over the serial line and exposes a
// small web GUI (socket.io) to command take-off/landing and visualise status.

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

// Parse a telemetry line:
// "STATE:DRONE_INSIDE,TEMP:24.5,DIST:12.3,PREALARM:0,ALARM:0"
function parseTelemetry(line) {
  const data = {};
  line.split(',').forEach((pair) => {
    const [key, value] = pair.split(':');
    if (key && value !== undefined) {
      data[key.trim().toLowerCase()] = value.trim();
    }
  });

  const alarm = data.alarm === '1';
  const preAlarm = data.prealarm === '1';
  const hangar = alarm ? 'ALARM' : preAlarm ? 'PREALARM' : 'NORMAL';

  return {
    state: data.state || 'UNKNOWN',
    hangar,
    distance: data.dist !== undefined ? parseFloat(data.dist) : null,
    temperature: data.temp !== undefined ? parseFloat(data.temp) : null
  };
}

function handleSerialLine(line) {
  const msg = line.trim();
  if (msg.length === 0) return;

  if (msg.startsWith('STATE:')) {
    lastTelemetry = parseTelemetry(msg);
    io.emit('hangar:telemetry', lastTelemetry);
  } else {
    // Any other line (debug, etc.)
    console.log('[hangar]', msg);
  }
}

function initSerial() {
  try {
    serialPort = new SerialPort({ path: SERIAL_PORT, baudRate: BAUD_RATE });

    serialPort.on('open', () => {
      parser = serialPort.pipe(new ReadlineParser({ delimiter: '\n' }));
      parser.on('data', handleSerialLine);
      io.emit('hangar:connected', { port: SERIAL_PORT, baudRate: BAUD_RATE });
      console.log('Serial open on', SERIAL_PORT);
    });

    serialPort.on('error', (err) => {
      console.error('Serial error:', err.message);
      io.emit('hangar:error', { error: err.message });
    });

    serialPort.on('close', () => {
      io.emit('hangar:disconnected');
    });
  } catch (err) {
    console.error('Serial init failed:', err.message);
  }
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
  // Push the latest known status to a freshly connected client.
  if (serialPort && serialPort.isOpen) {
    socket.emit('hangar:connected', { port: SERIAL_PORT });
  } else {
    socket.emit('hangar:disconnected');
  }
  if (lastTelemetry) socket.emit('hangar:telemetry', lastTelemetry);

  socket.on('drone:takeoff', () => sendCommand('CMD:TAKEOFF'));
  socket.on('drone:land', () => sendCommand('CMD:LAND'));
});

// REST equivalents (optional)
app.post('/api/takeoff', (req, res) => res.json({ ok: sendCommand('CMD:TAKEOFF') }));
app.post('/api/land', (req, res) => res.json({ ok: sendCommand('CMD:LAND') }));
app.get('/api/status', (req, res) =>
  res.json({ connected: !!(serialPort && serialPort.isOpen), telemetry: lastTelemetry })
);

initSerial();

server.listen(SERVER_PORT, '0.0.0.0', () => {
  console.log(`DRU web GUI on http://localhost:${SERVER_PORT}`);
});

module.exports = app;
