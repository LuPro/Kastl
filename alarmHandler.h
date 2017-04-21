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
    Alarm alarms[10];
    
    void deleteAlarm (const uint8_t &index);
    
  public:
    void setAlarm (const Alarm &newAlarm);
    void editAlarm (const Alarm &alarmToEdit, const Alarm &newAlarm);
    void deleteAlarm (const Alarm &alarm);  //currently unused
    void deleteAllAlarms();
};

#endif //alarmhandler_h
