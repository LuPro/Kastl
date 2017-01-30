#include "gestureHandler.h"

void GestureHandler::setGestureBit (const uint8_t &pin) {
  //Serial.print("set Bit: "); Serial.println(pin);
  gestureCode |= (1 << pin);
  cleanFlag_gC = false;
  triggerTMR();
}

void GestureHandler::triggerTMR () {
  //set clocksource to prescaled clock (prescaler: 1024)
  TCCR2B = B00000111;
  //reset TMR2 value to 0, in case it already coutned something before being turned off
  TCNT2 = 0;
  //reset the interrupt flag
  TIFR2 = B00000000;
  //enable TMR2 overflow interrupt
  TIMSK2 = B00000001;
}

