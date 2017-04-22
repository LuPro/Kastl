#ifndef alarmhandler_h
#define alarmhandler_h

#include "alarm.h"

#define NR_ALARMS 20

class AlarmHandler {
  private:
    //make as many alarms as possible with RAM (at the end of the project; ~10% should stay for local variables)
    bool setAlarms[NR_ALARMS];
    Alarm alarms[NR_ALARMS];
    
  public:
    AlarmHandler();
  
    void setAlarm (const Alarm &newAlarm);
    void editAlarm (const Alarm &alarmToEdit, const Alarm &newAlarm);
    void deleteAlarm (const Alarm &alarm);  //currently unused
    void deleteAllAlarms();
};

#endif //alarmhandler_h
