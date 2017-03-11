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

    uint32_t RGBa_to_RGB (const uint32_t &RGBa) const;
    uint32_t generateRGBa (const uint8_t &r, const uint8_t &g, const uint8_t &b, const uint8_t &alpha) const;
    uint8_t getChannel (uint8_t channel, const uint32_t &RGBa) const; //extracts a color channel out of a RGBa color
    
  public:
    Color ();
    Color (const uint8_t &setting);
  
    Color operator= (const Color color);
  
    void setColorRGB (uint32_t color);
  
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
    
    inline uint8_t getCh_r() const {
      return r;
    }
    inline uint8_t getCh_g() const {
      return g;
    }
    inline uint8_t getCh_b() const {
      return b;
    }
    inline uint8_t getCh_alpha() const {
      return alpha;
    }

    inline uint32_t getRGB () const {
      return RGBa_to_RGB (generateRGBa (r, g, b, alpha));
    }
};

#endif
