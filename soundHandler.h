#ifndef soundhandler_h
#define soundhandler_h

#include <Arduino.h>

#define PIEZO_PIN 9 //WARNING THIS IS DEFINITELY NOT RIGHT AND JUST SOME RANDOM VALUE I PUT SO AT LEAST SOMETHING IS HERE

class SoundHandler {
  private:
    
  public:
    void playAlarm (const float &volume, const uint16_t &frequency, const uint16_t &baseDuration);
};

#endif //soundhandler_h
