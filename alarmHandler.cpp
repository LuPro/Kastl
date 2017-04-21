#include "alarmHandler.h"

AlarmHandler::AlarmHandler () {
  for (uint8_t i = 0; i < NR_ALARMS; i++) {
    setAlarms[i] = false;
  }
}

void AlarmHandler::setAlarm (const Alarm &newAlarm) {
  uint8_t i;
  for (i = 0; (i < NR_ALARMS); i++) {
    if (!setAlarms[i]) {
      continue;
    }
  }

  alarms[i] = newAlarm;
  setAlarms[i] = true;
}

void AlarmHandler::editAlarm (const Alarm &alarmToEdit, const Alarm &newAlarm) {
  
}

void AlarmHandler::deleteAlarm (const uint8_t &index) {
  
}

void AlarmHandler::deleteAlarm (const Alarm &alarm) {
  
}

void AlarmHandler::deleteAllAlarms () {
  
}

