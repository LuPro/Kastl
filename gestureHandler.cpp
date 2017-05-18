#include "gestureHandler.h"

//This function just reads in the gesture board data pins, it does not interpret them or anythingg
void GestureHandler::pollGesturePins () {
    uint8_t pinStatus = 0;

    pinStatus = PIND4;
    pinStatus |= (PINC0 << 1);
    pinStatus |= (PINB0 << 2);
    //Serial.print("Pin status: "); Serial.println(pinStatus, BIN);
    //Serial.print("Old status: "); Serial.println(oldPinStatus, BIN);

    static uint8_t oldPinStatus = pinStatus;
    if (pinStatus != oldPinStatus) {
      Serial.print("\nPin status: "); Serial.println(pinStatus, BIN);
      Serial.print("Old status: "); Serial.println(oldPinStatus, BIN);
      Serial.print("Pin changed! ");
      gestureCode |= oldPinStatus ^ pinStatus;
      oldPinStatus = pinStatus;
      Serial.println(gestureCode, BIN);
      timeOut = millis() + GESTURE_TIMEOUT;
    }
}

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

//Could possibly be problematic, because I'm unsure whether ATmega queues the interrupts or just forgets everything
//ToDo: Either test this, or poll the status of the pins
void GestureHandler::triggerTMR () {
  //set clocksource to prescaled clock (prescaler: 1024)
  TCCR2B = B00000111;
  //reset TMR2 value to 0, in case it already counted something before being turned off
  TCNT2 = 0;
  //reset the interrupt flag
  TIFR2 = B00000000;
  //enable TMR2 overflow interrupt
  TIMSK2 = B00000001;
}

