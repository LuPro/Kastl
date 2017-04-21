#ifndef serialhandler_h
#define serialhandler_h

#include "color.h"
#include "stripHandler.h"
#include "alarmHandler.h"
#include "RTClib.h"
#include "Arduino.h"

enum Modes {
  lights,
  alarm
};

class SerialHandler {
  private:
    uint8_t byteOffset = 0; //keeps track of how many bytes got read since the status byte
    uint8_t mode = 0;       //stores the mode (light, alarm)

    AlarmHandler *alarms;
    StripHandler *strips;
    RTC_DS3231 *rtc;
    
    void parseColor (const uint8_t &data);
    void parseAlarm (const uint8_t &data);
    
  public:
    inline SerialHandler (StripHandler &strips, AlarmHandler &alarms, RTC_DS3231 &rtc) {
      this->strips = &strips;
      this->alarms = &alarms;
      this->rtc = &rtc;
    }
    void poll();
};

#endif
