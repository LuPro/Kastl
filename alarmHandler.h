#ifndef alarmhandler_h
#define alarmhandler_h

#include "alarm.h"
#include "soundHandler.h"
#include "stripHandler.h"
#include "RTClib.h"

#define NR_ALARMS 60

class AlarmHandler {
  private:
    bool isRinging = false;
    bool setAlarms[NR_ALARMS];
    Alarm alarms[NR_ALARMS];
    Alarm snoozedAlarm;
    uint8_t snoozeTime = 0;
    uint8_t activeSound = 0;

    unsigned long nextUpdate = 0;

    StripHandler *strips;
    SoundHandler *buzzer;
    
  public:
    AlarmHandler (StripHandler &strips, SoundHandler &buzzer);
  
    void setAlarm (const Alarm &newAlarm);
    void deleteAlarm (const Alarm &alarm);
    void deleteAllAlarms();

    void pollAlarms (const DateTime &timeNow);

    void updateSound();

    void snooze (const DateTime &timeNow);

    void dismiss();

    inline bool getIsRinging () {
      return isRinging;
    }
};

#endif //alarmhandler_h
