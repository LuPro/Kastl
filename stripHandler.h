#ifndef striphandler_h
#define striphandler_h

#include "Adafruit_NeoPixel.h"
#include "color.h"

#define NR_STRIPS 3
#define NR_LEDS_UP 10
#define DATA_PIN_UP PD5       //HW Pin 11

#define NR_LEDS_MID 8
#define DATA_PIN_MID PD6      //HW Pin 12

#define NR_LEDS_DRAWER 6
#define DATA_PIN_DRAWER PD7   //HW Pin 13

#define DELAY_BREATHING_SLOW 80
#define DELAY_BREATHING_FAST 20

#define BREATH_BORDER_UP 255
#define BREATH_BORDER_DN 120
#define BREATH_BORDER_DIFF (BREATH_BORDER_UP - BREATH_BORDER_DN)

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
    bool stripsOn = 0;
    uint8_t currentEffect[2] = {staticCol, staticCol};   //reduce this to 2 effects, since there are only 2 light groups
    unsigned long long prevUpdate[2] = {0, 0};                   //reduce this to 2 effects, since there are only 2 light groups
    Color primaryCol[2];                             //reduce this to 2 effects, since there are only 2 light groups
  
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
    //Strip functions
    void setup (const Color &color, const uint8_t &group, const uint8_t &effect);

    inline void toggle() {
      Color col;
      col.setColorRGB (0);
      
      if (stripsOn) {
        stripsOn = false;
      } else {
        stripsOn = true;
        col = primaryCol[0];
      }
      
      if (!stripsOn) {
        colorWipe (col, 0);
      } else {
        updateEffects();
      }
    }
    
    void alphaUp();
    void alphaDown();

    void cycleEffects (const uint8_t &group, const bool &up);
    
    void colorWipe (const Color &color, const uint8_t &stripPos); //flushes a desired LED strip with a desired RGB color

    void breathing (const Color &color, const uint8_t &stripPos, const uint16_t &delayTime);
    
    void updateEffects();

    void setCurrentEffect() {
      currentEffect[2] = 1;
    }
    uint8_t getCurrentEffect() {
      return currentEffect[2];
    }
};

#endif
