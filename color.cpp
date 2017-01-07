#include "color.h"

//converts RGBa color to RGB color
uint32_t Color::RGBa_to_RGB (uint32_t RGBa) {
  uint32_t val_RGB = 0;
  uint8_t r, g, b, alpha;

  //gets the individual channels
  r = getChannel (chR, RGBa);
  g = getChannel (chG, RGBa);
  b = getChannel (chB, RGBa);
  alpha = getChannel (chAlpha, RGBa);

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

//generates a RGBa color, is only used for debugging purposes, could be used later on for advanced strip effects as a helper function
uint32_t Color::generateRGBa (uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {
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

//returns a desired channel of a RGBa color, use the Channels enum for selection of the channel
uint8_t Color::getChannel (uint8_t channel, const uint32_t &RGBa) {
  return (RGBa >> (8 * channel)) & B11111111;
}
