#include "timeHandler.h"

TimeHandler::TimeHandler () {
  Wire.begin();
}

void TimeHandler::setTime (const uint8_t &s, const uint8_t &m, const uint8_t &h, const uint8_t &doW, const uint8_t &doM, const uint8_t &month, const uint8_t &year) {
  Wire.beginTransmission (RTC_I2C_ADDRESS);
  Wire.write (0);   // set next input to start at the seconds register
  Wire.write (decToBcd(s));
  Wire.write (decToBcd(m));
  Wire.write (decToBcd(h));
  Wire.write (decToBcd(doW));
  Wire.write (decToBcd(doM));
  Wire.write (decToBcd(month));
  Wire.write (decToBcd(year));
  Wire.endTransmission();
}

