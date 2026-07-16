const express = require('express');
const http = require('http');
const socketIo = require('socket.io');
const cors = require('cors');
const { SerialPort } = require('serialport');
const { ReadlineParser } = require('@serialport/parser-readline');
const { connected } = require('process');
require('dotenv').config();

const app = express();
const server = http.createServer(app);
const io = socketIo(server, {
  cors: { origin: "*", methods: ["GET", "POST"] }
});

app.use(cors());
app.use(express.json());
app.use(express.static('public'));

const SERIAL_PORT = process.env.SERIAL_PORT || '/dev/ttyUSB0';
const BAUD_RATE = parseInt(process.env.BAUD_RATE) || 9600;
const SERVER_PORT = process.env.SERVER_PORT || 3001;

let serialPort;
let parser;

function initSerial() {
  try {
    serialPort = new SerialPort({
      path: SERIAL_PORT,
      baudRate: BAUD_RATE
    });

    serialPort.on('open', () => {

      parser = serialPort.pipe(new ReadlineParser({ delimiter: "\n" }));

      parser.on('data', (data) => {
        const msg = data.trim();
        console.log(msg);
        io.emit('arduino:telemetry', msg)
      });

      io.emit('arduino:connected', {
        status: 'connected',
        port: SERIAL_PORT,
        baudRate: BAUD_RATE
      });
    });



    serialPort.on('error', (err) => {
      console.error(err.message);
      io.emit('arduino:error', { error: err.message })
    });

    serialPort.on('close', () => {
      console.log("Stop");
      io.emit('arduino:disconnected');
    });
  } catch (err) {
    console.error("Errore: ", err.message);
  }
}


function sendCommand(command) {
  console.log('sendCommand called with:', command);
  if (serialPort && serialPort.isOpen) {
    console.log('Port is OPEN, sending...');
    const cmd = command.endsWith('\n') ? command : command + '\n';
    serialPort.write(cmd, (err) => {
      if (err) {
        console.error('Write error:', err);
      } else {
        console.log('✅ Sent to Arduino:', command);
      }
    })
  } else {
    console.error('❌ Port NOT OPEN');
  }
}

io.on('connection', (socket) => {
  console.log(socket.id);
  if (serialPort && serialPort.isOpen) {
    socket.emit('arduino:connected', { status: 'connected' });
  } else {
    socket.emit('arduino:disconnected');
  }
  socket.on('drone:command', (command) => {
    console.log(command);
    sendCommand(command);
  });
  socket.on('drone:telemetry-request', () => {
    sendCommand('TELEMETRY_REQUEST');
  });

  socket.on('disconnect', () => {
    console.log("Disconesso: ", socket.id);
  });
});

app.get('/api/status', (req, res) => {
  res.json({
    connected: serialPort && serialPort.isOpen,
    port: SERIAL_PORT,
    baudRate: BAUD_RATE
  });
});

app.post('/api/command', (req, res) => {
  const { command } = req.body;
  if (!command) {
    return res.status(400).json({ error: 'comando mancante' });
  }
  sendCommand(command);
  res.json({ success: true, command: command });
});

app.post('/api/drone/arm', (req, res) => {
  sendCommand("CMD:ARM");
  res.json({ success: true });
});

app.post('/api/drone/takeoff', (req, res) => {
  sendCommand('CMD:TAKEOFF');
  res.json({ success: true });
});

app.post('/api/drone/land', (req, res) => {
  sendCommand('CMD:LAND');
  res.json({ success: true });
});

app.post('/api/drone/emergency', (req, res) => {
  sendCommand('CMD:EMERGENCY');
  res.json({ success: true });
});

app.get('/api/testConnection', (req, res) => {
  res.json({ message: "Connesso" });
});


initSerial();

const PORT = SERVER_PORT;

server.listen(PORT, "0.0.0.0", () => {
  console.log(`\nhttp://localhost:${PORT}`);
  console.log(SERVER_PORT);
});

module.exports = app;