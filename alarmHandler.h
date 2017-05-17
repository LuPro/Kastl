#ifndef alarmhandler_h
#define alarmhandler_h

#include "alarm.h"
#include "soundHandler.h"
#include "stripHandler.h"
#include "RTClib.h"

#define NR_ALARMS 20

#define PAUSE_ALARM 500

class AlarmHandler {
  private:
    bool isRinging = false;
    //make as many alarms as possible with RAM (at the end of the project; ~10% should stay for local variables)
    bool setAlarms[NR_ALARMS];
    Alarm alarms[NR_ALARMS];
    Alarm snoozedAlarm;
    uint8_t snoozeTime = 0;

    unsigned long nextUpdate = 0;

    StripHandler *strips;
    SoundHandler *buzzer;
    
  public:
    AlarmHandler (StripHandler &strips, SoundHandler &buzzer);
  
    void setAlarm (const Alarm &newAlarm);
    void editAlarm (const Alarm &alarmToEdit, const Alarm &newAlarm);   //ToDo: Work out whether or not this is really needed (Does the dataprotocoll leave any use cases for it?
    void deleteAlarm (const Alarm &alarm);
    void deleteAllAlarms();

    void pollAlarms (const DateTime &timeNow);

    void updateSound();

    void snooze (const DateTime &timeNow);

    void dismiss();

    inline bool getIsRinging () {
      return isRinging;
    }

    inline void __debug_startAlarm() {
      Serial.println("starting alarm");
      isRinging = true;
    }
};

#endif //alarmhandler_h
