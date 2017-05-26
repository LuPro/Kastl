#include "soundHandler.h"

void SoundHandler::playAlarm (const uint16_t &frequency, const uint16_t &duration) {
  tone (PIEZO_PIN, frequency, duration);
}

