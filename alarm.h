#ifndef alarm_h
#define alarm_h

enum DayOfWeek {
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday,
  Sunday
};

class Alarm {
private:
  uint8_t dayOfWeek;
  uint8_t hour, minute;

  //dictates whether or not the alarm is active. If so, it will be triggered, if not it can be considered as deleted.
  bool active = false;

public:
  inline void setAlarm (uint8_t dayOfWeek, uint8_t hour, uint8_t minute) {
    this->dayOfWeek = dayOfWeek;
    this->hour = hour;
    this->minute = minute;
  }

  inline uint8_t getDayOfWeek() {
    return dayOfWeek;
  }

  inline uint8_t getHour() {
    return hour;
  }

  inline uint8_t getMinute() {
    return minute;
  }
};

#endif //timehandler_h
