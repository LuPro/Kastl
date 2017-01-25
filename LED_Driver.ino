#include "stripHandler.h"
#include "color.h"
#include "serialHandler.h"
#include "gestureHandler.h"

GestureHandler gboard;

enum Gestures {
  fWE = 1,
  fEW = 2,
  fSN = 3,
  fNS = 4
};

void setup() {
  Serial.begin(9600);

  //turn TMR2 completely off
  //select clocksource (none) == TMR2 stopped
  TCCR2B = B00000000;
  //reset TMR2 value to 0, in case it already coutned something before being turned off
  TCNT2 = 0;
  //reset the interrupt flag
  TIFR2 = B00000000;
  //disable TMR2 overflow interrupt
  TIMSK2 = B00000000;

  //airwheel data
  //activate INT1 & INT0
  EIMSK = B00000011;
  
  //set INT1 & INT0 to trigger on rising. INT1 B[3:2], INT0 B[1:0]
  EICRA = B00001111;
  
  //gesture data
  //enable Pin change interrupts 2, 1 and 0
  //PCIE0 PCINT[7:0], PCIE1 PCINT[14:8], PCIE2 PCINT[23:16]
  PCICR = B00000111;
  //enable the individual pins for interrupts
  //enable pin 7
  PCMSK0 = B00000001; //enable PCINT on PCINT0, which corresponds to hardware pin 14 (pin 8 on arduino nano(?))
  PCMSK1 = B00000001; //enable PCINT on PCINT8, which corresponds to hardware pin 23 (pin 14 on arduino nano(?))
  PCMSK2 = B00010000; //enable PCINT on PCINT20, which corresponds to hardware pin 6 (pin 4 on arduino nano(?))
  
  //enables all interrupts: sets the I-flag in the SREG (status register)
  sei();
}

void loop() {
  static StripHandler strips;            //contains all strips and the needed information for them
  static SerialHandler serial (strips);  //ATTENTION! explain this (class structure)

  if (gboard.gC_isClean()) {
    switch (gboard.getGestureCode()) {
      case fWE:
        strips.toggle();
        break;
      case fEW:
        strips.toggle();
        break;
      case fSN:
        strips.cycleEffects(0, true);
        break;
      case fNS:
        strips.cycleEffects(0, false);
        break;
      default:
        break;
    }
  }
  
  serial.poll();
  strips.updateEffects();
}

//TODO: write TMR interrupt that applies gesture inputs to the correct handlers (stripHandler, alarmHandler)

//TMR2 will overflow every 16,384 milliseconds (with prescaler of 1024 on 16MHz). This is the duration of the timeout for gesture board codes
ISR (TIMER2_OVF_vect) {
  Serial.println("Reset Timer");
  //select clocksource (none) == TMR2 stopped
  TCCR2B = B00000000;
  //reset TMR2 value to 0
  TCNT2 = 0;
  gboard.set_cleanFlag_gC (true);
}

//functions need to be renamed to the correct ISR handler
//INT0: GPIN1: alphaUp
//INT1: GPIN2: alphaDown
void gesturePin1 () {
  //strips.alphaUp();
}

void gesturePin2 () {
  //strips.alphaDown();
}

void gesturePin3 () { //MSB
  gboard.setGestureBit (2);
}

void gesturePin6 () { //Bit 1
  gboard.setGestureBit (1);
}

void gesturePin7 () { //LSB
  gboard.setGestureBit (0);
}
