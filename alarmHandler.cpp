#include "alarmHandler.h"

AlarmHandler::AlarmHandler (StripHandler &strips, SoundHandler &buzzer) {
  this->strips = &strips;
  this->buzzer = &buzzer;
  for (uint8_t i = 0; i < NR_ALARMS; i++) {
    setAlarms[i] = false;
  }
}

void AlarmHandler::setAlarm (const Alarm &newAlarm) {
  Serial.println("Set an alarm");
  Serial.print(newAlarm.getAlarmHour()); Serial.print(":"); Serial.println(newAlarm.getAlarmMinute());
  uint8_t i;
  for (i = 0; (i < NR_ALARMS); i++) {
    if (!setAlarms[i]) {
      break;
    }
  }

  alarms[i] = newAlarm;
  setAlarms[i] = true;
}

void AlarmHandler::deleteAlarm (const Alarm &alarm) {
  Serial.print("Delete an alarm");
  Serial.print(alarm.getAlarmHour()); Serial.print(":"); Serial.println(alarm.getAlarmMinute());
  for (uint8_t i = 0; i < NR_ALARMS; i++) {
    if (alarms[i] == alarm) {
      setAlarms[i] = false;
      return;
    }
  }
}

void AlarmHandler::deleteAllAlarms () {
  Serial.print("Delete all alarms");
  for (uint8_t i = 0; i < NR_ALARMS; i++) {
    setAlarms[i] = false;
  }
}

void AlarmHandler::pollAlarms (const DateTime &timeNow) {
  uint8_t nextDay = 0;
  uint8_t doW = timeNow.dayOfTheWeek();
  
  for (uint8_t i = 0; i < NR_ALARMS; i++) {
    if (alarms[i].isActive()) {
      nextDay = alarms[i].getNextDay (doW);

      if (nextDay == doW) {
        if (alarms[i].getAlarmHour() == timeNow.hour() && alarms[i].getAlarmMinute() == timeNow.minute() && timeNow.second() == 1) {
          if (alarms[i] == snoozedAlarm) {
            deleteAlarm (alarms[i]);
            snoozedAlarm = Alarm();
          }
          Serial.println("ring ring ring fucker");
          snoozeTime = alarms[i].getSnoozeTime();
          activeSound = alarms[i].getSound();
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
    nextUpdate = now + buzzer->getDuration (activeSound);
    buzzer->playAlarm (activeSound);
    strips->setStripsOn (true, groupTop);
    strips->setTimeOff (now + (buzzer->getDuration (activeSound) >> 1));
  }
}

void AlarmHandler::snooze (const DateTime &timeNow) {
  if (snoozeTime) {
    Serial.println("Alarm snoozes");
    uint8_t h, m;

    h = timeNow.hour();
    m = timeNow.minute();
    if (m >= (60 - snoozeTime)) {
      h++;
    }

    m += snoozeTime;
    m %= 60;

    Alarm newSnoozedAlarm (B11111111, h, m, 1, 0, snoozeTime);

    snoozedAlarm = newSnoozedAlarm;
    setAlarm (newSnoozedAlarm);
  }
  
  dismiss();
}

void AlarmHandler::dismiss() {
  Serial.println("Alarm dismissed");
  isRinging = false;
  strips->alarm (false);
}

