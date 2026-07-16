#include "../../include/Tasks/ControlTask.h"

#include <Arduino.h>

#include "../../include/config.h"

void ControlTask::init() {}

void ControlTask::execute() {}

unsigned long int ControlTask::getInterval() { return CONTROL_TASK_INTERVAL; }
