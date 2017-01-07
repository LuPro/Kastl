#ifndef color_h
#define color_h

#include "Arduino.h"

enum Channels { //enumeration for the different channels, used in the getChannel function
  chR,
  chG,
  chB,
  chAlpha
};

class Color { //stores all needed information for one color and some helper functions
  private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t alpha;

    uint32_t RGBa_to_RGB (uint32_t RGBa);
    uint32_t generateRGBa (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);
    uint8_t getChannel (uint8_t channel, const uint32_t &RGBa); //extracts a color channel out of a RGBa color
    
  public:
    inline void setCh_r (const uint8_t &r) {
      this->r = r;
    }
    inline void setCh_g (const uint8_t &g) {
      this->g = g;
    }
    inline void setCh_b (const uint8_t &b) {
      this->b = b;
    }
    inline void setCh_alpha (const uint8_t &alpha) {
      this->alpha = alpha;
    }
    //void getRGBaSerial(); //reads the serial connection 

    inline uint32_t getRGB () {
      return RGBa_to_RGB (generateRGBa (r, g, b, alpha));
    }
};

#endif
