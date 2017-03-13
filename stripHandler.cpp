#include "stripHandler.h"

void StripHandler::setup (const Color &color, const uint8_t &group, const uint8_t &effect) {
  switch (effect) {
    case staticCol:
      currentEffect[group] = staticCol;
      primaryCol[group] = color;
      colorWipe (color, group);
      stripsOn = true;
      break;
    case breathingSlow:
      currentEffect[group] = breathingSlow;
      primaryCol[group] = color;
      breathing (color, group, DELAY_BREATHING_SLOW);
      stripsOn = true;
      break;
    default:
      break;
  }
}

//reduce alphaUp and alphaDown alpha changes, but increase frequency in gesture board settings
void StripHandler::alphaUp () {
  Serial.println("alphaUp");
  uint8_t alpha;
  Serial.println("Alpha Up");
  alpha = primaryCol[0].getCh_alpha();
  if (alpha > 250) {
    alpha = 255;
  } else {
    alpha += 5;
  }
  primaryCol[0].setCh_alpha (alpha);
}

void StripHandler::alphaDown () {
  Serial.println("alphaDown");
  uint8_t alpha;
  Serial.println("Alpha Down");
  alpha = primaryCol[0].getCh_alpha();
  if (alpha < 25) {
    alpha = 20;
  } else {
    alpha -= 5;
  }
  primaryCol[0].setCh_alpha (alpha);
}

void StripHandler::cycleEffects (const uint8_t &group, const bool &up) {
  if (stripsOn) {
    if (up) {
      currentEffect[group]++;
    } else {
      currentEffect[group]--;
    }
    //currentEffect[group] %= 7;
    currentEffect[group] %= 3;    //only for debugging
    Serial.print("Current Effect: "); Serial.println(currentEffect[group]);
  } else {
    toggle();
  }

}

//flushes a desired LED strip with a desired RGB color, use Strips enum to choose which strip to use
void StripHandler::colorWipe (const Color &color, const uint8_t &group) {
  uint8_t passes = 0;
  uint8_t strip = 0;

  if (group == 0) {
    passes = 2;
  } else {
    passes = 3;
    strip = 2;
  }

  for (; strip < passes; strip++) {
    for (uint8_t i = 0; i < strips[strip].numPixels(); i++) { //iterates through every pixel of the LED strip
      strips[strip].setPixelColor (i, color.getRGB());
    }
    strips[strip].show(); //shows the LED strip. Internal function of the Adafruit_Neopixel library. Is used to actually apply the color info
  }
}

//effects need to use a seperate alpha channel for global brightness adjustments to work - IMPLEMENT THIS!!!
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

  unsigned long long now = 0;
  now = millis();

  if (now < nextUpdate[group]) {
    return;
  }
  nextUpdate[group] = now + ((delayTime / (delayFactor / 255.0) ) * (generalDelay / 255.0) );

  if (group == 0) {
    passes = 2;
  } else {
    passes = 3;
    stripPos = 2;
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

void StripHandler::updateEffects () {
  if (stripsOn) {
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
        default:
          break;
      }
    }
  }
}
