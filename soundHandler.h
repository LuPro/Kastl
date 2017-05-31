#ifndef soundhandler_h
#define soundhandler_h

#include <Arduino.h>

#define PIEZO_PIN 9//PB1

#define NR_SOUNDS 6

class SoundHandler {
  private:
    uint8_t frequencies[NR_SOUNDS] = {10, 10, 15, 15, 30, 30};    //frequency in 1/100 Hz. To get the actual Hz value multiply by 100
    uint8_t durations[NR_SOUNDS] = {10, 5, 10, 5, 10, 5};        //duration of sound cycle (half of it with sound, half of it without) in 1/100 ms
    
  public:
    void playAlarm (const uint8_t &sound);

    inline uint16_t getDuration (const uint8_t &sound) {
      return durations[sound] * 100;
    }
};

#endif //soundhandler_h
