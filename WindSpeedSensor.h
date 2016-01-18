#ifndef WindSpeedSensor_h
#define WindSpeedSensor_h

#include <Arduino.h>

class WindSpeedSensor{
  public:
    WindSpeedSensor(int pin);
    ~WindSpeedSensor();
    void setSignalPin(int pin);
    float readSpeed();
  private:
    float calculateSpeed();
};

#endif
