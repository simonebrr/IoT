# IoT — Embedded Systems & Internet of Things

Assignment del corso di **Embedded Systems and IoT** — Ingegneria e Scienze Informatiche, Università di Bologna.

| Assignment | Progetto | Tecnologie |
|---|---|---|
| [`assignment01`](assignment01) | Gioco di riflessi su Arduino: riprodurre con i pulsanti la sequenza mostrata sull'LCD entro un tempo che si riduce a ogni round; difficoltà regolabile, modalità sleep | Arduino UNO · C++ |
| [`assignment02`](assignment02) | **Smart Drone Hangar**: hangar con porta motorizzata, sonar, PIR e allarme temperatura; architettura a task + FSM sincrone; GUI web di controllo via seriale | Arduino UNO · C++ · Node.js · socket.io |
| [`assignment03`](assignment03) | **Sistema di monitoraggio serbatoio** distribuito in 4 sottosistemi comunicanti via MQTT, seriale e HTTP | ESP32 · Arduino UNO · Python · Flask · MQTT |

## Assignment 03 — sottosistemi

- **`tms`** — Tank Monitoring System: ESP32 con sonar, pubblica il livello via MQTT
- **`wcs`** — Water Channel Subsystem: Arduino UNO con servo (valvola), LCD, pulsante ed encoder
- **`cus`** — Control Unit Subsystem: logica centrale in Python (MQTT + seriale + API HTTP)
- **`dbs`** — Dashboard Subsystem: dashboard web in Flask

## Struttura

```
assignment01/   src/ (sketch .ino) · doc/ (schema e video)
assignment02/   drone-hangar/ (PlatformIO) · drone-remote-unit/ (Node.js) · doc/ (relazione, FSM)
assignment03/   tms/ · wcs/ (PlatformIO) · cus/ · dbs/ (Python)
```

I progetti Arduino/ESP32 si compilano con [PlatformIO](https://platformio.org/); la documentazione di ogni assignment è nella rispettiva cartella `doc/`.
