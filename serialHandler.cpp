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
  static uint8_t group = 0, effect = 0;
  static Color color;

  switch (byteOffset) {
    case 0:
      group = ((data & B00110000) >> 4);  //maybe make group to 1 bit only and expand effects?
      effect = (data & B00001111);
      byteOffset++;
      if (group == 2) {
        group = 0;
      }
      //Serial.print("Group: "); Serial.println(group);
      //Serial.print("Effect: "); Serial.println(effect);
      break;
    case 1:
      color.setCh_r (data);
      byteOffset++;
      //Serial.print("Red: "); Serial.println(data);
      break;
    case 2:
      color.setCh_g (data);
      byteOffset++;
      //Serial.print("Green: "); Serial.println(data);
      break;
    case 3:
      color.setCh_b (data);
      byteOffset++;
      //Serial.print("Blue: "); Serial.println(data);
      break;
    case 4:
      color.setCh_alpha (data);
      //Serial.print("Alpha: "); Serial.println(data);

      //more colors than one are possible by setting the byte offset back to 1 for a certain effect (eg: breathing with two
      //colors. A helper variable would also be needed which stores how often this got reseted, otherwise there'll be
      //an endless loop.
      strips->setup (color, group, effect);

      byteOffset = 0; //reset byteOffset
      break;
    default:
      break;
  }
}

void SerialHandler::parseAlarm (const uint8_t &data) {

}
