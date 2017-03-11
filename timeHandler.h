#ifndef timehandler_h
#define timehandler_h

#include "Wire.h"

//I2C address of DS3231 module: B1101000, 104
#define RTC_I2C_ADDRESS 104

class TimeHandler {
  private:
    //Convert normal decimal numbers to binary coded decimal
    inline uint8_t decToBcd(const uint8_t &val) {
      return ( (val / 10 * 16) + (val % 10) );
    }
    //Convert binary coded decimal to normal decimal numbers
    inline uint8_t bcdToDec(const uint8_t &val) {
      return ( (val / 16 * 10) + (val % 16) );
    }

  public:
    TimeHandler ();

    void setTime (const uint8_t &s, const uint8_t &m, const uint8_t &h, const uint8_t &doW, const uint8_t &doM, const uint8_t &month, const uint8_t &year);
};

#endif //timehandler_h
