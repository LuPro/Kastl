#ifndef soundhandler_h
#define soundhandler_h

#include <Arduino.h>

#define PIEZO_PIN 9//PB1

class SoundHandler {
  private:
    
  public:
    void playAlarm (const uint16_t &frequency, const uint16_t &duration);
};

#endif //soundhandler_h
