#include "soundHandler.h"

//VOLUME DOESN'T WORK, AS THERE IS NO VOLUME CONTROL FOR THE TONE FUNCTION! Volume could control the duration of the beep
void SoundHandler::playAlarm (const uint8_t &volume, const uint16_t &frequency, const uint16_t &duration) {
  tone (PIEZO_PIN, frequency, duration);
}

