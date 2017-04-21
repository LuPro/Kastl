#ifndef alarm_h
#define alarm_h

#include "RTClib.h"

//struct Alarm inherits from Time
class Alarm : DateTime {
  private:
    //dictates whether or not the alarm is active. If so, it will be triggered, if not it can be considered as deleted.
    uint8_t activeDays = 0; //contains every day the alarm can be active as a flag (Bit 0-6 == Monday-Sunday)
    uint8_t snoozeTime = 0; //in minutes. Maybe make another default value (such as 5 min?)
    bool active = false;

  public:
    Alarm();
    Alarm(const uint8_t &activeDays, const uint8_t &h, const uint8_t &m, const bool &active, const uint8_t &sound, const uint8_t &volume, const uint8_t &snoozeTime);

    uint8_t getNextDay(const uint8_t &currentDay);
};

#endif //alarm_h
