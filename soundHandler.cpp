#include "soundHandler.h"

//Volume is a value from 0-255, where 0 is the most quiet and 255 is the loudest
void SoundHandler::playAlarm (const uint16_t &frequency, const uint16_t &duration) {
  tone (PIEZO_PIN, frequency, duration);
  //analogWrite(PIEZO_PIN, 127);
}

