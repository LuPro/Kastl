#ifndef alarmhandler_h
#define alarmhandler_h

#include "alarm.h"
#include "RTClib.h"

#define NR_ALARMS 20

class AlarmHandler {
  private:
    //make as many alarms as possible with RAM (at the end of the project; ~10% should stay for local variables)
    bool setAlarms[NR_ALARMS];
    Alarm alarms[NR_ALARMS];
    
  public:
    AlarmHandler();
  
    void setAlarm (const Alarm &newAlarm);
    void editAlarm (const Alarm &alarmToEdit, const Alarm &newAlarm);   //ToDo: Work out whether or not this is really needed (Does the dataprotocoll leave any use cases for it?
    void deleteAlarm (const Alarm &alarm);
    void deleteAllAlarms();

    bool checkForAlarm (const DateTime &timeNow);
};

#endif //alarmhandler_h
