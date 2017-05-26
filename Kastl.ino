#include "stripHandler.h"
#include "color.h"
#include "serialHandler.h"
#include "gestureHandler.h"
#include "alarmHandler.h"
#include "soundHandler.h"
#include "RTClib.h"

#define DS3231_I2C_ADDRESS 104

#define REED_PIN 17//PC3

GestureHandler gboard;
RTC_DS3231 rtc;

volatile bool brightnessChange = false;
volatile bool brightnessUp = false;

enum Gestures {
  fWE = 1,
  fEW = 2,
  fSN = 3,
  fNS = 4
};

void setup() {
  PORTB = B00000100;
  DDRB  = B00010110;
  PINB  = 0;

  PORTC = B00000000;
  DDRC  = B00000110;
  PINC  = 0;

  PORTD = B00000000;
  DDRD  = B11100010;
  PIND  = 0;

  analogReference (EXTERNAL);

  Serial.begin(9600); //this only works if the Serial library has been edited to work with the 8MHz clock
  //if this is not the case, use 4800 baud instead to get 9600 baud

  while (!rtc.begin());

  if (rtc.lostPower()) {
    //maybe make a warning sound here
  }

  //airwheel data
  //set INT1 & INT0 to trigger on rising. INT1 B[3:2], INT0 B[1:0]
  EICRA = B00001111;
  //resets interrupt flags to 1 (active LOW)
  EIFR = B00000011;
  //activate INT1 & INT0
  EIMSK = B00000011;

  //gesture data
  //enable the individual pins for interrupts
  PCMSK0 = B00000001; //enable PCINT on PCINT0, which corresponds to hardware pin 14 (pin 8 on arduino uno)
  PCMSK1 = B00000001; //enable PCINT on PCINT8, which corresponds to hardware pin 23 (pin 14 on arduino uno)
  PCMSK2 = B00010000; //enable PCINT on PCINT20, which corresponds to hardware pin 6 (pin 4 on arduino uno)
  //resets interrupt flags to 1 (active LOW)
  PCIFR = B00000111;
  //enable Pin change interrupts 2, 1 and 0
  //PCIE0 PCINT[7:0], PCIE1 PCINT[14:8], PCIE2 PCINT[23:16]
  PCICR = B00000111;

  //enables all interrupts: sets the I-flag in the SREG (status register)
  sei();
}

void loop() {
  static SoundHandler buzzer;
  static StripHandler strips;
  static AlarmHandler alarms (strips, buzzer);
  static SerialHandler serial (strips, alarms, rtc);

  if (millis() < gboard.getCooldown() && gboard.gC_isClean()) {
    gboard.set_cleanFlag_gC (false);
    gboard.clear_gC ();
  }

  if (gboard.gC_isClean()) {
    gboard.setCooldown();
    switch (gboard.getGestureCode()) {
      case fWE:
        //Serial.println("WE, toggled");
        if (alarms.getIsRinging()) {
          alarms.snooze (rtc.now());
        } else {
          strips.toggle(groupTop);
        }
        gboard.set_cleanFlag_gC (false);
        gboard.clear_gC ();
        break;
      case fEW:
        //Serial.println("EW, toggled");
        if (alarms.getIsRinging()) {
          alarms.snooze (rtc.now());
        } else {
          strips.toggle(groupTop);
        }
        gboard.set_cleanFlag_gC (false);
        gboard.clear_gC ();
        break;
      case fSN:
        //Serial.println("SN, effects");
        if (alarms.getIsRinging()) {
          alarms.dismiss();
        } else {
          strips.cycleEffects(0, true);
        }
        gboard.set_cleanFlag_gC (false);
        gboard.clear_gC ();
        break;
      case fNS:
        //Serial.println("NS, effects");
        if (alarms.getIsRinging()) {
          alarms.dismiss();
        } else {
          strips.cycleEffects(0, false);
        }
        gboard.set_cleanFlag_gC (false);
        gboard.clear_gC ();
        break;
      default:
        break;
    }
  }

  if (brightnessChange) {
    brightnessChange = false;
    if (brightnessUp) {
      strips.alphaUp();
    } else {
      strips.alphaDown();
    }
  }

  strips.setStripsOn (digitalRead(REED_PIN), groupDrawer);

  //polling information and effect updates
  gboard.checkTimeout();
  alarms.pollAlarms (rtc.now());
  serial.poll();
  alarms.updateSound();
  strips.updateEffects();
}

//INT0: GPIN1: alphaDown
//INT1: GPIN2: alphaUp
//Interrupt Service Routine of the INT0 interrupt vector
ISR (INT0_vect) {
  brightnessChange = true;
  brightnessUp = false;
}

//Interrupt Service Routine of the INT1 interrupt vector
ISR (INT1_vect) {
  brightnessChange = true;
  brightnessUp = true;
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
