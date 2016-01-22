#ifndef LED15Controller_h
#define LED15Controller_h

#include <Arduino.h>


class LED15Controller {
  public:
    LED15Controller(int latchPin, int dataPin, int clockPin);
    ~LED15Controller();
    void ledControl(int pins);
  private:
    void writeToSRs(byte secondSR, byte firstSR);
    
};

#endif
