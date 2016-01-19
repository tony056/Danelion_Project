#include "WindSpeedSensor.h"

const float threshold = 0.4;
int speedPin = 1;



WindSpeedSensor::WindSpeedSensor(int pin){
  speedPin = pin;
  pinMode(speedPin, INPUT);
}

WindSpeedSensor::~WindSpeedSensor(){
  
}

void WindSpeedSensor::setSignalPin(int pin){
  speedPin = pin;
  pinMode(speedPin, INPUT);
}

float WindSpeedSensor::readSpeed(){
  return calculateSpeed();
}

float WindSpeedSensor::calculateSpeed(){
  int rawValue = analogRead(speedPin);
  float voltage = rawValue * 5.0 / 1024.0;
  float windSpeed = (voltage - threshold) * 81.0 / 4.0;
  return windSpeed;
}



