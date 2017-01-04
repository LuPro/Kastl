#ifndef serialhandler_h
#define serialhandler_h

#include "Arduino.h"

enum Modes {
  lights,
  alarm
};

class serialHandler {
  private:
    void parseColor (const uint8_t &firstByte);
    void parseAlarm (const uint8_t &firstByte);
    
  public:
    serialHandler();
  
    void pollSerial();
};

#endif
