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
  for (uint8_t i = 0; i < NR_ALARMS; i++) {
    if (alarms[i] == alarmToEdit) {
      alarms[i] = newAlarm;
    }
  }
}

void AlarmHandler::deleteAlarm (const Alarm &alarm) {
  for (uint8_t i = 0; i < NR_ALARMS; i++) {
    if (alarms[i] == alarm) {
      setAlarms[i] = false;
      return;
    }
  }
}

void AlarmHandler::deleteAllAlarms () {
  for (uint8_t i = 0; i < NR_ALARMS; i++) {
    setAlarms[i] = false;
  }
}

