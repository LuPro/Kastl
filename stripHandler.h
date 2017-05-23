#ifndef striphandler_h
#define striphandler_h

#include "Adafruit_NeoPixel.h"
#include "color.h"

#define NR_EFFECTS altRainbowFast
#define NR_STRIPS 3
#define NR_LEDS_UP 10
#define DATA_PIN_UP PD5       //HW Pin 11

#define NR_LEDS_MID_UP 4
#define DATA_PIN_MID_UP PD7      //HW Pin 12

#define NR_LEDS_MID_DN NR_LEDS_MID_UP
#define DATA_PIN_MID_DN DATA_PIN_MID_UP      //HW Pin 12

#define NR_LEDS_DRAWER 6
#define DATA_PIN_DRAWER PD6   //HW Pin 13

#define ALPHA_STEP_SIZE 5
#define ALPHA_BORDER_DN 20

#define DELAY_BREATHING_SLOW 80
#define DELAY_BREATHING_FAST 20

#define DELAY_RAINBOW_SLOW 30
#define DELAY_RAINBOW_FAST 5

#define DELAY_ALT_RAINBOW_SLOW 30
#define DELAY_ALT_RAINBOW_FAST 5

#define BREATH_BORDER_UP 255
#define BREATH_BORDER_DN 60
#define BREATH_BORDER_DIFF (BREATH_BORDER_UP - BREATH_BORDER_DN)

enum Effects {
  staticCol,
  breathingSlow,
  breathingFast,
  rainbowSlow,
  rainbowFast,
  altRainbowSlow,
  altRainbowFast,
  alarmEffect
};

enum LightGroup {
  groupTop,
  groupDrawer
};

enum Strips { //enumeration for the different LED strips
  top,
  mid_up,
  //mid_dn,
  drawer
};

//colors are comprised of R, G, B and alpha channel
class StripHandler {
  private:
    bool stripsOn[2] = {0, 0};
    uint8_t currentEffect[2] = {staticCol, staticCol};
    unsigned long nextUpdate[2] = {0, 0};
    Color primaryCol[2] = {Color(255, 0, 0), Color(255, 255, 255)};
  
    Adafruit_NeoPixel strips[NR_STRIPS] = { //define the individual LED strips (top, mid_up, mid_dn, drawer)
      //Still need to test if this is a NEO_RGB, or NEO_GRB. If while testing R and G channel are inverted, choose NEO_GRB.
      Adafruit_NeoPixel(NR_LEDS_UP, DATA_PIN_UP, NEO_RGB + NEO_KHZ800),
      Adafruit_NeoPixel(NR_LEDS_MID_UP, DATA_PIN_MID_UP, NEO_RGB + NEO_KHZ800),
      //Adafruit_NeoPixel(NR_LEDS_MID_DN, DATA_PIN_MID_DN, NEO_RGB + NEO_KHZ800),
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

    inline void toggle (const uint8_t &group) {
      Color col;
      col.setColorRGB (0);
      
      if (stripsOn[group]) {
        stripsOn[group] = false;
      } else {
        stripsOn[group] = true;
        col = primaryCol[group];
      }
      
      if (!stripsOn[group]) {
        colorWipe (col, group);
      } else {
        updateEffects();
      }
    }

    void alphaUp();
    void alphaDown();

    void cycleEffects (const uint8_t &group, const bool &up);
    
    void colorWipe (const Color &color, const uint8_t &stripPos); //flushes a desired LED strip with a desired RGB color

    void breathing (const Color &color, const uint8_t &stripPos, const uint16_t &delayTime);

    void rainbowCycle (const uint8_t &group, const uint16_t &delayTime);

    void altRainbow (const uint8_t &group, const uint16_t &delayTime);

    Color colorWheel (uint8_t wheelPos);
    
    void updateEffects();

    void alarm(const bool &on);
    
    inline uint8_t getCurrentEffect() {
      return currentEffect[2];
    }
};

#endif
