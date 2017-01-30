#ifndef serialhandler_h
#define serialhandler_h

#include "color.h"
#include "stripHandler.h"
#include "Arduino.h"

enum Modes {
  lights,
  alarm
};

class SerialHandler {
  private:
    uint8_t byteOffset = 0; //keeps track of how many bytes got read since the status byte
    uint8_t mode = 0;       //stores the mode (light, alarm)

    StripHandler *strips;
    
    void parseColor (const uint8_t &data);
    void parseAlarm (const uint8_t &data);
    
  public:
    inline SerialHandler (StripHandler &strips) {
      this->strips = &strips;
    }
    void poll();
};

#endif
