#include "alarm.h"

Alarm::Alarm () {
  this->hour = 0;
  this->minute = 0;
  this->activeDays = 0;
  this->sound = 0;
  this->volume = 0;
  this->snoozeTime = 0;
}

Alarm::Alarm (const uint8_t &activeDays, const uint8_t &h, const uint8_t &m, const bool &active, const uint8_t &sound, const uint8_t &volume, const uint8_t &snoozeTime) {
  this->hour = h;
  this->minute = m;
  this->activeDays = activeDays;
  this->activeDays |= (active << 7);
  this->sound = sound;
  this->volume = volume;
  this->snoozeTime = snoozeTime;
}

Alarm Alarm::operator= (const Alarm &alarm) {
  this->hour = alarm.hour;
  this->minute = alarm.minute;
  this->activeDays = alarm.activeDays;
  this->sound = alarm.sound;
  this->volume = alarm.volume;
  this->snoozeTime = alarm.snoozeTime;
}

bool Alarm::operator== (const Alarm &alarm) {
  return (hour == alarm.hour) && (minute == alarm.minute) && (activeDays == alarm.activeDays) && (sound == alarm.sound) && (volume == alarm.volume) && (snoozeTime == alarm.snoozeTime);
}

uint8_t Alarm::getAlarmMinute () {
  return minute;
}

uint8_t Alarm::getAlarmHour () {
  return hour;
}

uint8_t Alarm::getNextDay (const uint8_t &currentDay) {
  uint8_t i;
  for (i = currentDay; i < 7; i++) {
    if (activeDays & (1 << i)) {
      return i;
    }
  }
  for (i = currentDay; i; i--) {
    if (activeDays & (1 << i)) {
      return i;
    }
  }
}

