#include "gestureHandler.h"

void GestureHandler::checkTimeout () {
  if (millis() > timeOut && newCode) {
    cleanFlag_gC = true;
    newCode = false;
  }
}

void GestureHandler::setGestureBit (const uint8_t &pin) {
  gestureCode |= (1 << pin);
  cleanFlag_gC = false;
  newCode = true;
  timeOut = millis() + GESTURE_TIMEOUT;
}

