#include "colorHandler.h"

//converts RGBa color to RGB color
uint32_t ColorHandler::RGBa_to_RGB (uint32_t RGBa) {
  uint32_t val_RGB = 0;
  uint8_t r, g, b, alpha;

  //gets the individual channels
  r = getColorChannel (chR, RGBa);
  g = getColorChannel (chG, RGBa);
  b = getColorChannel (chB, RGBa);
  alpha = getColorChannel (chAlpha, RGBa);

  //scales the individual color channels by the alpha channel
  r *= (alpha / 255.0);
  g *= (alpha / 255.0);
  b *= (alpha / 255.0);

  //stores the resulting RGB color
  val_RGB = b;
  val_RGB = val_RGB << 8;
  val_RGB |= g;
  val_RGB = val_RGB << 8;
  val_RGB |= r;

  return val_RGB;
}

//flushes a desired LED strip with a desired RGB color, use Strips enum to choose which strip to use
void ColorHandler::colorWipe (uint32_t color, uint8_t stripPos) {
  for (uint8_t i = 0; i < strips[stripPos].numPixels(); i++) { //iterates through every pixel of the LED strip
    strips[stripPos].setPixelColor (i, color);
  }
  strips[stripPos].show(); //shows the LED strip. Internal function of the Adafruit_Neopixel library. Is used to actually apply the color info
}

//generates a RGBa color, is only used for debugging purposes, could be used later on for advanced strip effects as a helper function
uint32_t ColorHandler::generateRGBa (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {
  uint32_t RGBa = 0;

  //shifts the individual channels on the right position
  RGBa = alpha;
  RGBa = RGBa << 8;
  RGBa |= b;
  RGBa = RGBa << 8;
  RGBa |= g;
  RGBa = RGBa << 8;
  RGBa |= r;

  return RGBa;
}

//--[[does nothing as of yet,]]-- should get the RGBa data via serial. Whether there is a Raspberry Pi or not changes if this function has to
//be able to decipher the whole data protocol defined by BCH and SAL, or just the Lights part
//expects the order R, G, B, alpha
//still doesn't store the values correctly, something probably goes wrong with the bit shifting
void ColorHandler::getRGBaSerial () {
  uint32_t colBuffer;     //buffer has to be 32 bit, otherwise it cannot be shifted far enough
  static uint8_t byteCount = 0;

  for (; Serial.available(); byteCount++) {
    colBuffer = Serial.read();

    switch (byteCount) {
      case (chR):                   //Stores the red channel, sets cleanFlag to false, so RGBa doesn't get read in the process
        cleanFlagRGBa = false;
        RGBa = 0;
        RGBa |= colBuffer;
        break;
      case (chG):
        RGBa |= (colBuffer << 8);
        break;
      case (chB):
        RGBa |= (colBuffer << 16);
        break;
      case (chAlpha):
        RGBa |= (colBuffer << 24);
        byteCount = 0;
        cleanFlagRGBa = true;
        break;
      default:
        break;
    }
  }
}

//returns a desired channel of a RGBa color, use the Channels enum for selection of the channel
uint8_t ColorHandler::getColorChannel (uint8_t channel, const uint32_t &RGBa) {
  return (RGBa >> (8 * channel)) & B11111111;
}
