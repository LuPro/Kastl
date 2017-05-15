#ifndef gesturehandler_h
#define gesturehandler_h

#include "Arduino.h"

class GestureHandler {
  private:
    /*gesture codes:
     * xxx ... pin3, pin6, pin7
     * flick WE: 001
     * flick EW: 010
     * flick SN: 011
     * flick NS: 100
     */
    uint8_t gestureCode = 0;
    bool cleanFlag_gC = 0;

  public:

    inline void clear_gC () {
      gestureCode = 0;
    }
    inline bool gC_isClean () {
      return cleanFlag_gC;
    }
    inline void set_cleanFlag_gC (const bool &val) {
      cleanFlag_gC = val;
    }
    inline uint8_t getGestureCode() {
      return gestureCode;
    }

    void pollGesturePins ();

    void setGestureBit (const uint8_t &pin);

    void triggerTMR();
};

#endif
