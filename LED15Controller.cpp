#include "LED15Controller.h"

#define led_num 15

int latch_pin = 0;
int data_pin = 0;
int clock_pin = 0;

LED15Controller::LED15Controller(int latchPin, int dataPin, int clockPin){
  latch_pin = latchPin;
  data_pin = dataPin;
  clock_pin = clockPin;
  pinMode(latch_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);  
}

LED15Controller::~LED15Controller(){
}

void LED15Controller::ledControl(int pins){
    byte secondChip = highByte(pins);
    byte firstChip = lowByte(pins);
    writeToSRs(secondChip, firstChip);
}

void LED15Controller::writeToSRs(byte secondSR, byte firstSR){
  digitalWrite(latch_pin, LOW);
  shiftOut(data_pin, clock_pin, MSBFIRST, secondSR);
  shiftOut(data_pin, clock_pin, MSBFIRST, firstSR);
  digitalWrite(latch_pin, HIGH); 
}

