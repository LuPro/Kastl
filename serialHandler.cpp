#include "serialHandler.h"

void serialHandler::pollSerial () {
  if (Serial.available()) {
    uint8_t inData = 0;
    uint8_t mode = 0;

    //reads the serial buffer
    inData = Serial.read();
    mode = (inData >> 6);

    //chooses which function mode was sent
    switch (mode) {
      case lights:
        parseColor (inData);
        break;
      case alarm:
        parseAlarm (inData);
        break;
      default:
        break;
    }
  }
}

void serialHandler::parseColor (const uint8_t &firstByte) {
  uint8_t strip, effects, effSetting;

  strip = ((firstByte & B00110000) >> 4);
  effects = ((firstByte & B00001100) >> 2);
  effSetting = (firstByte & B00000011);
  /*uint32_t colBuffer;     //buffer has to be 32 bit, otherwise it cannot be shifted far enough
  static uint8_t byteCount = 0;

  for (; Serial.available(); byteCount++) {
    colBuffer = Serial.read();

    switch (byteCount) {
      case (chR):                   //Stores the red channel, sets cleanFlag to false, so RGBa doesn't get read in the process
        cleanFlagRGBa = false;
        RGBa = 0;
        RGBa |= colBuffer;
        break;
      case (chG):                   //Stores the green channel
        RGBa |= (colBuffer << 8);
        break;
      case (chB):                   //Stores the blue channel
        RGBa |= (colBuffer << 16);
        break;
      case (chAlpha):               //Stores the alpha channel, resets the byte count, sets cleanFlag to true, so RGBa can be read
        RGBa |= (colBuffer << 24);
        byteCount = 0;
        cleanFlagRGBa = true;
        break;
      default:
        break;
    }
  }*/
}

void serialHandler::parseAlarm (const uint8_t &firstByte) {
  
}

