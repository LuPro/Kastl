#ifndef alarm_h
#define alarm_h

#include "time.h"
//#include "RTClib.h"

#include "Arduino.h"

enum DayOfWeek {
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday,
  Sunday
};

//struct Alarm inherits from Time
class Alarm : Time {
  private:
    //dictates whether or not the alarm is active. If so, it will be triggered, if not it can be considered as deleted.
    //ATTENTION: activeDay ALSO contains the active flag!!!! Bit 7 is a bool for active!!!
    uint8_t sound = 0;      //alarm sound
    uint8_t volume = 0;     //alarm volume
    uint8_t activeDays = 0; //contains every day the alarm can be active as a flag (Bit 0-6 == Monday-Sunday)
    uint8_t snoozeTime = 0; //in minutes. Maybe make another default value (such as 5 min?)

  public:
    Alarm();
    Alarm(const uint8_t &activeDays, const uint8_t &h, const uint8_t &m, const bool &active, const uint8_t &sound, const uint8_t &volume, const uint8_t &snoozeTime);

    Alarm operator= (const Alarm &alarm);
    bool operator== (const Alarm &alarm);

    uint8_t getAlarmMinute();
    uint8_t getAlarmHour();
    uint8_t getNextDay (const uint8_t &currentDay);
    inline bool isActive() {
      return (activeDays & B10000000) == true;
    }
};

#endif //alarm_h
