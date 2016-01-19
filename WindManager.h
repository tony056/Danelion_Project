#ifndef WindManager_h
#define WindManager_h

#include <Arduino.h>
#include <stdlib.h>
#include "WindSpeedSensor.h"
#include "WindDirectionSensor.h"

class WindManager{
   public:
    WindManager(int windowSize, int directionPin, int speedPin);
    ~WindManager();
    void collectData();
    int getDirection();
    float getSpeed();
};

#endif
