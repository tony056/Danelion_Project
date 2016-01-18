#ifndef WindDirectionSensor_h
#define WindDirectionSensor_h

#include<Arduino.h>
#include<math.h>

class WindDirectionSensor{
  public:
    WindDirectionSensor(int pin);
    ~WindDirectionSensor();
    void setSignalPin(int pin);
    int readDirection();
    float readRawVoltage();
  private:
    int calculateDirection();
    float calculateVoltage();
};


#endif
