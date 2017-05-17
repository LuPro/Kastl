#include "alarmHandler.h"

AlarmHandler::AlarmHandler (StripHandler &strips, SoundHandler &buzzer) {
  this->strips = &strips;
  this->buzzer = &buzzer;
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

void AlarmHandler::pollAlarms (const DateTime &timeNow) {
  uint8_t nextDay = 0;
  for (uint8_t i = 0; i < NR_ALARMS; i++) {
    if (alarms[i].isActive()) {
      nextDay = alarms[i].getNextDay (timeNow.dayOfTheWeek());

      if (!nextDay) {
        if (alarms[i].getAlarmHour() == timeNow.hour() && alarms[i].getAlarmMinute() == timeNow.minute() && timeNow.second() == 1) {
          if (alarms[i] == snoozedAlarm) {
            deleteAlarm (alarms[i]);
            snoozedAlarm = Alarm();
          }
          snoozeTime = alarms[i].getSnoozeTime();
          isRinging = true;
          strips->alarm (true);
        }
      }
    }
  }
}

void AlarmHandler::updateSound () {
  unsigned long now = millis();

  if (isRinging && now > nextUpdate) {
    nextUpdate = now + PAUSE_ALARM;
    buzzer->playAlarm(500, 250);    //this needs to be changeable, not hardcoded
  }
}

void AlarmHandler::snooze (const DateTime &timeNow) {
  if (snoozeTime) {
    uint8_t h, m;

    h = timeNow.hour();
    m = timeNow.minute();
    if (m > 54) {
      h++;
    }

    m += snoozeTime;
    m %= 60;

    Alarm newSnoozedAlarm (0, h, m, 1, 0, snoozeTime);

    snoozedAlarm = newSnoozedAlarm;
    setAlarm (newSnoozedAlarm);
  }
  
  dismiss();
}

void AlarmHandler::dismiss() {
  isRinging = false;
  strips->alarm (false);
}

