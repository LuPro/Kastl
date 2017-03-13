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
  //reset TMR2 value to 0, in case it already counted something before being turned off
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
        Serial.println("toggled");
        strips.toggle();
        gboard.set_cleanFlag_gC (false);
        gboard.clear_gC ();
        break;
      case fEW:
        Serial.println("toggled");
        strips.toggle();
        gboard.set_cleanFlag_gC (false);
        gboard.clear_gC ();
        break;
      case fSN:
        Serial.println("effects");
        strips.cycleEffects(0, true);
        gboard.set_cleanFlag_gC (false);
        gboard.clear_gC ();
        break;
      case fNS:
        Serial.println("effects");
        strips.cycleEffects(0, false);
        gboard.set_cleanFlag_gC (false);
        gboard.clear_gC ();
        break;
      default:
        break;
    }
  }
  
  serial.poll();
  strips.updateEffects();
}

//TMR2 will overflow every 16,384 milliseconds (with prescaler of 1024 on 16MHz). This is the duration of the timeout for gesture board codes
ISR (TIMER2_OVF_vect) {
  //select clocksource (none) == TMR2 stopped
  TCCR2B = B00000000;
  //disable TMR2 overflow interrupt
  TIMSK2 = B00000000;
  //reset TMR2 value to 0
  TCNT2 = 0;
  //reset TMR2 interrupt flag
  TIFR2 = B00000000;
  gboard.set_cleanFlag_gC (true);
}

//INT0: GPIN1: alphaUp
//INT1: GPIN2: alphaDown
//Interrupt Service Routine of the INT0 interrupt vector
ISR (INT0_vect) {
  //strips.alphaUp();
}

//Interrupt Service Routine of the INT1 interrupt vector
ISR (INT1_vect) {
  //strips.alphaDown();
}

//Interrupt Service Routine of the PCINT0 interrupt vector
ISR (PCINT0_vect) { //MSB
  gboard.setGestureBit (2);
}

//Interrupt Service Routine of the PCINT1 interrupt vector
ISR (PCINT1_vect) { //Bit 1
  gboard.setGestureBit (1);
}

//Interrupt Service Routine of the PCINT2 interrupt vector
ISR (PCINT2_vect) { //LSB
  gboard.setGestureBit (0);
}
