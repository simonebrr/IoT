#ifndef CONTROL_TASK_H
#define CONTROL_TASK_H

#include "Actuators/Door.h"
#include "Actuators/LcdDisplay.h"
#include "Actuators/Led.h"
#include "BlinkTask.h"
#include "SensorTask.h"
#include "Sensors/Button.h"
#include "Task.h"
#include "TemperatureTask.h"

/*
 * FSM principale dell'hangar.
 *
 * Il drone passa da DRONE_INSIDE a TAKING_OFF con il comando TAKEOFF,
 * poi a DRONE_OUTSIDE quando supera D1 per almeno T1.
 *
 * Con il comando LAND e il rilevamento del PIR inizia l'atterraggio.
 * Se la distanza resta sotto D2 per T2, torna in DRONE_INSIDE.
 *
 * Un allarme di temperatura porta il sistema in HANGAR_ALARM da
 * qualsiasi stato. Dopo il reset, il sistema riparte dallo stato
 * corretto in base alla posizione del drone.
 *
 * In pre-allarme non vengono avviate nuove operazioni, mentre quelle
 * già iniziate vengono completate.
 */

enum HangarState {
  DRONE_INSIDE,
  TAKING_OFF,
  DRONE_OUTSIDE,
  LANDING,
  HANGAR_ALARM
};

class ControlTask : public Task {
  SensorTask* sensors;
  TemperatureTask* tempMonitor;
  Door* door;
  Led* l1;
  Led* l3;
  BlinkTask* blink;
  LcdDisplay* lcd;
  Button* resetButton;

  HangarState state;
  bool droneInside;  // dove tornare quando l'allarme viene resettato
  bool takeoffRequested;
  bool landRequested;

  void changeState(HangarState newState);
  bool operationsAllowed();

 public:
  ControlTask(SensorTask* sensors, TemperatureTask* tempMonitor, Door* door,
              Led* l1, Led* l3, BlinkTask* blink, LcdDisplay* lcd,
              Button* resetButton);

  void start();  // porta la FSM nello stato iniziale (da chiamare in setup)
  void tick() override;

  /* chiamate dal SerialTask quando arriva un comando dal PC */
  void requestTakeoff() { takeoffRequested = true; }
  void requestLand() { landRequested = true; }

  const char* getStateName();
};

#endif
