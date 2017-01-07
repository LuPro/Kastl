#include "serialHandler.h"

void SerialHandler::poll () {
  if (Serial.available()) {
    uint8_t inData = 0;

    //reads the serial buffer
    inData = Serial.read();

    //the first byte of data includes mode
    if (byteOffset == 0) {
      mode = (inData >> 6);
    }

    //chooses which function mode was sent and runs the correct function for this mode
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

void SerialHandler::parseColor (const uint8_t &data) {
  static uint8_t strip = 0, effect = 0;
  static uint8_t r = 0, g = 0, b = 0, alpha = 0;

  static Color color;

  switch (byteOffset) {
    case 0:
      strip = ((data & B00110000) >> 4);
      effect = (data & B00001111);
      break;
    case 1:
      r = data;
      break;
    case 2:
      g = data;
      break;
    case 3:
      b = data;
      break;
    case 4:
      alpha = data;

      color.setCh_r (r);
      color.setCh_g (g);
      color.setCh_b (b);
      color.setCh_alpha (alpha);

      //more colors than one are possible by setting the byte offset back to 1 for a certain effect (eg: breathing with two
      //colors. A helper variable would also be needed which stores how often this got reseted, otherwise there'll be
      //an endless loop
      strips.setup (strip, color.getRGB (), effect);  //Strip effects currently ignored
      
      byteOffset = 0; //reset byteOffset
      break;
    default:
      break;
  }

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

void SerialHandler::parseAlarm (const uint8_t &firstByte) {

}
