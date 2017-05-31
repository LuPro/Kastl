#include "soundHandler.h"

void SoundHandler::playAlarm (const uint8_t &sound) {
  tone (PIEZO_PIN, frequencies[sound] * 100, durations[sound] * 100);
}

