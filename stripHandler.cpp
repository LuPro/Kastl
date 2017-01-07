#include "stripHandler.h"

StripHandler::StripHandler (const Adafruit_NeoPixel strips[], const uint8_t &curEffect) {
  for (uint8_t i = 0; i < 3; i++) {
    for (uint8_t n = 0; n < this->strips[i].numPixels(); n++) {
      this->strips[i].setPixelColor (n, strips[i].getPixelColor (n));
    }
  }
  this->currentEffect = curEffect;  //"this->" is not needed, but is included in case I want to change curEffect to currentEffect
}

StripHandler StripHandler::operator= (const StripHandler &stripsIn) {
  return StripHandler(stripsIn.strips, stripsIn.currentEffect);
}

void StripHandler::setup (const uint32_t &color, const uint8_t &stripPos, const uint8_t &effect) {
  switch (effect) {
    case staticCol:
      colorWipe (color, stripPos);
      break;
    default:
      break;
  }  
}

//flushes a desired LED strip with a desired RGB color, use Strips enum to choose which strip to use
void StripHandler::colorWipe (uint32_t color, uint8_t stripPos) {
  for (uint8_t i = 0; i < strips[stripPos].numPixels(); i++) { //iterates through every pixel of the LED strip
    strips[stripPos].setPixelColor (i, color);
  }
  strips[stripPos].show(); //shows the LED strip. Internal function of the Adafruit_Neopixel library. Is used to actually apply the color info
}

void StripHandler::updateEffects () {
  switch (currentEffect) {
    case staticCol:
      break;
    default:
      break;
  }
}

/*
//--[[does nothing as of yet,]]-- should get the RGBa data via serial. Whether there is a Raspberry Pi or not changes if this function has to
//be able to decipher the whole data protocol defined by BCH and SAL, or just the Lights part
//expects the order R, G, B, alpha
//still doesn't store the values correctly, something probably goes wrong with the bit shifting
void StripHandler::getRGBaSerial () {
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
*/
