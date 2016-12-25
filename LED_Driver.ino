#include "colorHandler.h"

void setup() {
  //Initialize Serial connection, only for debug purposes
  Serial.begin(9600);
}

void loop() {
  static ColorHandler lights;   //ColorHandler handles everything related to LED strips and color functions

  //RGBa consists of 4 channels (in this order): 8b alpha, 8b blue, 8b green, 8b red
  //color consists of 3 channels (in this order): 8b blue, 8b green, 8b red
  uint32_t RGBa, color;

  //If there is serial data available, read this data
  //available means new (unread as of yet) data in the dedicated serial buffer (buffer size default: 64 byte)
  if (Serial.available()) {
    lights.getRGBaSerial();
  }

  //if RGBa is clean, the value can be extracted
  //clean means, that the complete RGBa value is received and stored. If this would not be here, the could be cases where
  //the RGBa value is used even if only half of it got transmitted via serial connection. This ensures data integrity
  if (lights.RGBaIsClean()) {
    RGBa = lights.getRGBa();
  }

  RGBa = lights.generateRGBa (127, 127, 127, 127);    //generate a test color, only for debug

  color = lights.RGBa_to_RGB(RGBa);
  lights.colorWipe (color, top);

  //use this delay only if debugging via serial interface - with this delay you can read the individual debug infos, but
  //the program won't work properly if this is left for normal use
  delay(500);
}

