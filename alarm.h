#ifndef alarm_h
#define alarm_h

#include "RTClib.h"

//struct Alarm inherits from Time
struct Alarm : DateTime {
    //dictates whether or not the alarm is active. If so, it will be triggered, if not it can be considered as deleted.
    bool active = false;
};

#endif //alarm_h
