#ifndef striphandler_h
#define striphandler_h

#include "Adafruit_NeoPixel.h"

#define NR_STRIPS 3
#define NR_LEDS_UP 10
#define DATA_PIN_UP 6

#define NR_LEDS_MID 8
#define DATA_PIN_MID 7

#define NR_LEDS_DRAWER 6
#define DATA_PIN_DRAWER 8

enum Effects {
  staticCol,
  breathingSlow,
  breathingFast,
  rainbowSlow,
  rainbowFast,
  altRainbowSlow,
  altRainbowFast
};

enum Strips { //enumeration for the different LED strips
  top,
  mid,
  drawer
};

//colors are comprised of R, G, B and alpha channel
class StripHandler {
  private:
    uint8_t currentEffect = staticCol;
  
    Adafruit_NeoPixel strips[NR_STRIPS] = { //define the individual LED strips (top, mid, drawer)
      //Still need to test if this is a NEO_RGB, or NEO_GRB. If while testing R and G channel are inverted, choose NEO_GRB.
      //frequency (NEO_KHZ800) should be fine like this, look in the Adafruit_Neopixel library for more options if this isn't right
      Adafruit_NeoPixel(NR_LEDS_UP, DATA_PIN_UP, NEO_RGB + NEO_KHZ800),
      Adafruit_NeoPixel(NR_LEDS_MID, DATA_PIN_MID, NEO_RGB + NEO_KHZ800),
      Adafruit_NeoPixel(NR_LEDS_DRAWER, DATA_PIN_DRAWER, NEO_RGB + NEO_KHZ800)
    };
    
  public:
    inline StripHandler () { //constructor, initializes all strips
      for (uint8_t pos = 0; pos < NR_STRIPS; pos++) {
        strips[pos].begin();
        strips[pos].show();
      }
    }
    //this possibly needs more variables when effects get actually implemented (eg: secondary color)
    StripHandler (const Adafruit_NeoPixel strips[], const uint8_t &curEffect);

    StripHandler operator= (const StripHandler &stripsIn);
    //Strip functions
    //Currently no effects included in setup function
    void setup (const uint32_t &color, const uint8_t &strip, const uint8_t &effect);
    
    void colorWipe (uint32_t color, uint8_t stripPos); //flushes a desired LED strip with a desired RGB color
    void updateEffects();
};

#endif
