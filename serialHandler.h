#ifndef serialhandler_h
#define serialhandler_h

#include "color.h"
#include "stripHandler.h"
#include "alarmHandler.h"
#include "alarm.h"
#include "RTClib.h"
#include "Arduino.h"

enum Modes {
  lights,
  alarm,
  SPACER,
  rtcTime
};

enum AlarmActions {
  create,
  deleteAlarm,
  clearAll
};

class SerialHandler {
  private:
    uint8_t byteOffset = 0; //keeps track of how many bytes got read since the status byte
    uint8_t mode = 0;       //stores the mode (light, alarm, ...)

    //pointers to every other class the serialHandler gets information about so it can pass this information
    AlarmHandler *alarms;
    StripHandler *strips;
    RTC_DS3231 *rtc;
    
    void parseColor (const uint8_t &data);
    void parseAlarm (const uint8_t &data);
    void parseTime (const uint8_t &data);
    
  public:
    inline SerialHandler (StripHandler &strips, AlarmHandler &alarms, RTC_DS3231 &rtc) {
      this->strips = &strips;
      this->alarms = &alarms;
      this->rtc = &rtc;
    }
    
    void poll();
};

#endif
