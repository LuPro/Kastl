#ifndef colorhandler_h
#define colorhandler_h

#include "Adafruit_NeoPixel.h"

#define NR_STRIPS 3
#define NR_LEDS_UP 10
#define DATA_PIN_UP 6

#define NR_LEDS_MID 8
#define DATA_PIN_MID 7

#define NR_LEDS_DRAWER 6
#define DATA_PIN_DRAWER 8

enum Channels { //enumeration for the different channels, used in the getColorChannel function
  chR,
  chG,
  chB,
  chAlpha
};

enum Strips { //enumeration for the different LED strips
  top,
  mid,
  drawer
};

//colors are comprised of R, G, B and alpha channel
class ColorHandler {
  private:
    Adafruit_NeoPixel strips[NR_STRIPS] = { //define the individual LED strips (top, mid, drawer)
      //Still need to test if this is a NEO_RGB, or NEO_GRB. If while testing R and G channel are inverted, choose NEO_GRB.
      //frequency (NEO_KHZ800) should be fine like this, look in the Adafruit_Neopixel library for more options if this isn't right
      Adafruit_NeoPixel(NR_LEDS_UP, DATA_PIN_UP, NEO_RGB + NEO_KHZ800),
      Adafruit_NeoPixel(NR_LEDS_MID, DATA_PIN_MID, NEO_RGB + NEO_KHZ800),
      Adafruit_NeoPixel(NR_LEDS_DRAWER, DATA_PIN_DRAWER, NEO_RGB + NEO_KHZ800)
    };
    
    uint32_t RGBa = 0;
    bool cleanFlagRGBa = false; //Tells wether RGBa can be used (clean), or if it isn't transmitted completely (dirty)
    //Note to myself: maybe handle this as an interrupt?

    uint8_t getColorChannel (uint8_t channel, const uint32_t &RGBa); //extracts a color channel out of a RGBa color
    
  public:
    inline ColorHandler () { //constructor, initializes all strips
      for (uint8_t pos = 0; pos < NR_STRIPS; pos++) {
        strips[pos].begin();
        strips[pos].show();
      }
    }

    //Color functions
    uint32_t generateRGBa (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha); //is only used for debugging purposes
    uint32_t getRGBaSerial(); //reads the serial connection 
    uint32_t RGBa_to_RGB (uint32_t RGBa); //converts RGBa color to RGB color

    inline uint32_t getRGBa() {
      cleanFlagRGBa = false;
      return RGBa;
    }
    inline bool RGBaIsClean() {
      //ATTENTION!, this is only for debugging purposes, otherwise RGBa would always be true!
      return true;
      //return cleanFlagRGBa;
    }

    //Strip functions
    void colorWipe (uint32_t color, uint8_t stripPos); //flushes a desired LED strip with a desired RGB color
};

#endif
