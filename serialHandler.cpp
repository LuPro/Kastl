#include "serialHandler.h"

void SerialHandler::poll () {
  if (Serial.available()) {
    uint8_t inData = 0;

    //reads the serial buffer
    inData = Serial.read();

    //the first byte of data includes mode
    if (byteOffset == 0) {
      mode = (inData >> 6);
    }

    //chooses which function mode was sent and runs the correct function for this mode
    switch (mode) {
      case lights:
        parseColor (inData);
        break;
      case alarm:
        parseAlarm (inData);
        break;
      case rtcTime:
        parseTime (inData);
        break;
      default:
        break;
    }
  }
}

void SerialHandler::parseColor (const uint8_t &data) {
  static uint8_t group = 0, effect = 0;
  static Color color;

  switch (byteOffset) {
    case 0:
      group = ((data & B00110000) >> 4);  //maybe make group to 1 bit only and expand effects?
      effect = (data & B00001111);
      byteOffset++;
      if (group == 2) {
        group = 0;
      }
      //Serial.print("Group: "); Serial.println(group);
      //Serial.print("Effect: "); Serial.println(effect);
      break;
    case 1:
      color.setCh_r (data);
      byteOffset++;
      //Serial.print("Red: "); Serial.println(data);
      break;
    case 2:
      color.setCh_g (data);
      byteOffset++;
      //Serial.print("Green: "); Serial.println(data);
      break;
    case 3:
      color.setCh_b (data);
      byteOffset++;
      //Serial.print("Blue: "); Serial.println(data);
      break;
    case 4:
      color.setCh_alpha (data);
      //Serial.print("Alpha: "); Serial.println(data);

      strips->setup (color, group, effect);

      byteOffset = 0; //reset byteOffset
      break;
    default:
      break;
  }
}

void SerialHandler::parseAlarm (const uint8_t &data) {
  static uint8_t sound = 0, volume = 0, snoozeTime = 0;
  static uint8_t action = 0;
  static uint8_t doW = 0, h = 0, m = 0;

  switch (byteOffset) {
    case 0:
      sound = (data & B00111110) >> 1;
      doW = (data & B00000001) << 6;
      byteOffset++;
      break;
    case 1:
      doW |= (data & B11111100) >> 2;
      action = data & B00000011;
      byteOffset++;
      break;
    case 2:
      snoozeTime = (data & B11111000) >> 3;
      h = (data & B00000111) << 2;
      byteOffset++;
      break;
    case 3:
      h |= (data & B11000000) >> 6;
      m = data & B00111111;
      byteOffset++;
      break;
    case 4:
      volume = data;

      switch (action) {
        case create:
          alarms->setAlarm (Alarm(doW, h, m, true, sound, snoozeTime));
          break;
        case edit:
          //probably not needed, look at alarmHandler.h for more information
          //edit can also delete (?)
          break;
        case deleteAlarm:
          alarms->deleteAlarm ( Alarm(doW, h, m, true, sound, snoozeTime) );
          break;
        case clearAll:
          alarms->deleteAllAlarms();
          break;
        default:
          break;
      }
      byteOffset = 0;
      break;
    default:
      break;  
  }
}

void SerialHandler::parseTime (const uint8_t &data) {
  static uint8_t s, m, h, doW, doM, mon, y;
  
  switch (byteOffset) {
    case 0:
      s = data & B00111111;
      byteOffset++;
      break;
    case 1:
      m = data & B00111111;
      byteOffset++;
      break;
    case 2:
      h = (data & B11111000) >> 3;
      doW = data & B00000111;
      byteOffset++;
      break;
    case 3:
      doM = (data & B11111000) >> 3;
      mon = (data & B00000111) << 1;
      byteOffset++;
      break;
    case 4:
      mon |= (data & B10000000) >> 7;
      y = data & B01111111;

      //ToDo: doW can't be saved, add this yourself so alarms can work properly
      rtc->adjust (DateTime (y, mon, doM, h, m, s));
      byteOffset = 0;
      break;
  }
}

