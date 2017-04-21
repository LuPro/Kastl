#ifndef timehandler_h
#define timehandler_h

#include "Wire.h"
#include "RTClib.h"

//I2C address of DS3231 module: B1101000, 104
#define RTC_I2C_ADDRESS 104

class TimeHandler {
  private:
    RTC_DS3231 rtcModule;

  public:
    TimeHandler ();

    void setTime (const uint8_t &s, const uint8_t &m, const uint8_t &h, const uint8_t &doW, const uint8_t &doM, const uint8_t &month, const uint8_t &year);
};

#endif //timehandler_h
