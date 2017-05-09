#include "soundHandler.h"

//Volume is a value from 0-1, where 0 is the most quiet and 1 is the loudest
void SoundHandler::playAlarm (const float &volume, const uint16_t &frequency, const uint16_t &baseDuration) {
  uint16_t calcDuration = 0;

  calcDuration = baseDuration/(1 - volume);
  tone (PIEZO_PIN, frequency, calcDuration);
}

