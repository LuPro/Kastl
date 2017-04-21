#ifndef alarmhandler_h
#define alarmhandler_h

#include "alarm.h"

#define NR_ALARMS 10

class AlarmHandler {
  private:
    //make as many alarms as possible with RAM (at the end of the project)
    bool setAlarms[NR_ALARMS];
    Alarm alarms[NR_ALARMS];
    
    void deleteAlarm (const uint8_t &index);
    
  public:
    AlarmHandler();
  
    void setAlarm (const Alarm &newAlarm);
    void editAlarm (const Alarm &alarmToEdit, const Alarm &newAlarm);
    void deleteAlarm (const Alarm &alarm);  //currently unused
    void deleteAllAlarms();
};

#endif //alarmhandler_h
