#ifndef alarmhandler_h
#define alarmhandler_h

#include "alarm.h"

//does this need to be here?
enum DayOfWeek {
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday,
  Sunday
};

class AlarmHandler {
  private:
    //make as many alarms as possible with RAM (at the end of the project)
    Alarm alarms[8];
  public:
};

#endif //alarmhandler_h
