#include "stripHandler.h"

void StripHandler::setup (const Color &color, const uint8_t &group, const uint8_t &effect) {
  switch (effect) {
    case staticCol:
      currentEffect[group] = staticCol;
      primaryCol[group] = color;
      colorWipe (color, group);
      stripsOn[group] = true;
      break;
    case breathingSlow:
      currentEffect[group] = breathingSlow;
      primaryCol[group] = color;
      breathing (color, group, DELAY_BREATHING_SLOW);
      stripsOn[group] = true;
      break;
    case breathingFast:
      currentEffect[group] = breathingFast;
      primaryCol[group] = color;
      breathing (color, group, DELAY_BREATHING_FAST);
      stripsOn[group] = true;
      break;
    case rainbowSlow:
      currentEffect[group] = rainbowSlow;
      //primaryCol[group] = color;      //sollte nicht nötig sein, dadurch merkt er sich die alte farbe
      rainbowCycle (group, DELAY_RAINBOW_SLOW);
      stripsOn[group] = true;
      break;
    case rainbowFast:
      currentEffect[group] = rainbowFast;
      //primaryCol[group] = color;
      rainbowCycle (group, DELAY_RAINBOW_FAST);
      stripsOn[group] = true;
      break;
    case altRainbowSlow:
      currentEffect[group] = altRainbowSlow;
      //primaryCol[group] = color;
      altRainbow (group, DELAY_ALT_RAINBOW_SLOW);
      stripsOn[group] = true;
      break;
    case altRainbowFast:
      currentEffect[group] = altRainbowFast;
      //primaryCol[group] = color;
      altRainbow (group, DELAY_ALT_RAINBOW_FAST);
      stripsOn[group] = true;
      break;
    default:
      break;
  }
}

//reduce alphaUp and alphaDown alpha changes, but increase frequency in gesture board settings
void StripHandler::alphaUp () {
  if (stripsOn[groupTop] == false) {
    Serial.println("alpha up, but off");
    return;
  }

  Serial.println("alphaUp");
  uint8_t alpha;
  alpha = primaryCol[0].getCh_alpha();
  if (alpha > 250) {
    alpha = 255;
  } else {
    alpha += 5;
  }
  primaryCol[0].setCh_alpha (alpha);
}

void StripHandler::alphaDown () {
  if (stripsOn[groupTop] == false) {
    Serial.println("alpha down, but off");
    return;
  }

  Serial.println("alphaDown");
  uint8_t alpha;
  alpha = primaryCol[0].getCh_alpha();
  if (alpha < 25) {
    alpha = 20;
  } else {
    alpha -= 5;
  }
  primaryCol[0].setCh_alpha (alpha);
}

void StripHandler::cycleEffects (const uint8_t &group, const bool &up) {
  if (stripsOn[group]) {
    colorWipe (Color(255,255,255), group);
    delay(10);
    
    if (up) {
      currentEffect[group]++;
    } else {
      currentEffect[group]--;
    }

    if (currentEffect[group] > NR_EFFECTS + 1) {
      //currentEffect[group] = NR_EFFECTS;
      currentEffect[group] = 6;
    }

    //currentEffect[group] %= NR_EFFECTS - 1;
    currentEffect[group] %= 7;    //only for debugging
    Serial.print("Current Effect: "); Serial.println(currentEffect[group]);
  } else {
    if (group == 0) {
      toggle(0);
    }
  }
}

//flushes a desired LED group with a desired RGB color, use Strips enum to choose which strip to use
void StripHandler::colorWipe (const Color &color, const uint8_t &group) {
  uint8_t passes = 0;
  uint8_t strip = 0;

  if (group == groupTop) {
    passes = 2;
  } else if (group == groupDrawer) {
    passes = 3;
    strip = drawer;
  }

  for (; strip < passes; strip++) {
    for (uint8_t i = 0; i < strips[strip].numPixels(); i++) { //iterates through every pixel of the LED strip
      strips[strip].setPixelColor (i, color.getRGB());
    }
    strips[strip].show(); //shows the LED strip. Internal function of the Adafruit_Neopixel library. Is used to actually apply the color info
  }
}

void StripHandler::breathing (const Color &color, const uint8_t &group, const uint16_t &delayTime) {
  static Color col;
  static uint8_t alpha = 0;
  static bool up = false;
  static uint8_t borderDiff = (BREATH_BORDER_UP - BREATH_BORDER_DN) * 0.1;
  uint8_t distanceBorderDN = alpha - BREATH_BORDER_DN;
  uint8_t distanceBorderUP = BREATH_BORDER_UP - alpha;
  uint8_t generalDelay = 127;
  uint8_t delayFactor = 127;
  uint8_t passes = 0;
  uint8_t stripPos = 0;

  unsigned long now = 0;
  now = millis();

  if (now < nextUpdate[group]) {
    return;
  }
  nextUpdate[group] = now + ((delayTime / (delayFactor / 255.0) ) * (generalDelay / 255.0) );

  if (group == groupTop) {
    passes = 2;
  } else {
    passes = 3;
    stripPos = drawer;
  }

  generalDelay = distanceBorderUP;
  if (generalDelay < 100) {
    generalDelay = 100;
  }

  for (; stripPos < passes; stripPos++) {
    if (distanceBorderUP < distanceBorderDN) {
      delayFactor += distanceBorderUP & B01111111;
    } else {
      delayFactor += distanceBorderDN & B01111111;
    }

    //Serial.print("Alpha breath: "); Serial.println(alpha);

    if (up) {
      alpha++;
    } else {
      alpha--;
    }

    col = color;
    col.setCh_alpha ( (alpha / 255.0) * color.getCh_alpha());
    colorWipe (col, stripPos);

    if (alpha == BREATH_BORDER_UP) {
      up = false;
    }
    else if (alpha == BREATH_BORDER_DN) {
      up = true;
    }
  }
}

void StripHandler::rainbowCycle (const uint8_t &group, const uint16_t &delayTime) {
  static uint16_t rainbowPos = 0; //check if this is needed as uint16 (also in altRainbow)
  unsigned long now = millis();
  Color col;

  if (now < nextUpdate[group]) {
    return;
  }

  nextUpdate[group] = now + delayTime;
  for (int i = 0; i < strips[group].numPixels(); i++) {
    /*each pixel is a fraction of the full 96-color wheel
      (thats the i / strip.numPixels() part)
      Then add in rainbow_pos which makes the colors go around per pixel
      the % 96 is to make the wheel cycle around*/
    col = colorWheel( ((i * 256 / strips[group].numPixels()) + rainbowPos) % 256);
    col.setCh_alpha (primaryCol[group].getCh_alpha());
    strips[group].setPixelColor(i, col.getRGB());
  }
  strips[group].show();   // write all the pixels out
  ++rainbowPos;
  rainbowPos %= 256;
}

void StripHandler::altRainbow (const uint8_t &group, const uint16_t &delayTime) {
  static uint16_t rainbowPos = 0;
  unsigned long now = millis();
  Color col;

  if (now < nextUpdate[group]) {
    return;
  }

  nextUpdate[group] = now + delayTime;
  col.setCh_alpha (primaryCol[group].getCh_alpha());
  colorWipe (colorWheel(rainbowPos), group);
  ++rainbowPos;
  rainbowPos %= 256;
}

Color StripHandler::colorWheel (uint8_t WheelPos) {
  if (WheelPos < 85) {
    return Color(255 - WheelPos * 3, WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return Color(0, 255 - WheelPos * 3, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return Color(WheelPos * 3, 0, 255 - WheelPos * 3);
  }
}

void StripHandler::updateEffects () {
  for (uint8_t i = 0; i <= groupDrawer; i++) {
    if (stripsOn[i]) {
      for (uint8_t lightGroups = 0; lightGroups < 2; lightGroups++) {
        switch (currentEffect[lightGroups]) {
          case staticCol:
            colorWipe (primaryCol[lightGroups], lightGroups);
            break;
          case breathingSlow:
            breathing (primaryCol[lightGroups], lightGroups, DELAY_BREATHING_SLOW);
            break;
          case breathingFast:
            breathing (primaryCol[lightGroups], lightGroups, DELAY_BREATHING_FAST);
            break;
          case rainbowSlow:
            rainbowCycle (lightGroups, DELAY_RAINBOW_SLOW);
            break;
          case rainbowFast:
            rainbowCycle (lightGroups, DELAY_RAINBOW_FAST);
            break;
          case altRainbowSlow:
            altRainbow (lightGroups, DELAY_ALT_RAINBOW_SLOW);
            break;
          case altRainbowFast:
            altRainbow (lightGroups, DELAY_ALT_RAINBOW_FAST);
            break;
          case alarmEffect:
            colorWipe (Color(0, 255, 0), groupTop);
            break;
          default:
            break;
        }
      }
    }
  }
}

void StripHandler::alarm (const bool &on) {
  static uint8_t oldEffect = 0;
  if (on) {
    oldEffect = currentEffect[groupTop];
    currentEffect[groupTop] = alarmEffect;
  } else {
    currentEffect[groupTop] = oldEffect;
  }
}

