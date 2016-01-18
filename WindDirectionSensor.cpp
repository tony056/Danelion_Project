#include "WindDirectionSensor.h"

const float threshold = 0.4; //the base line of the output voltage
const int directionNum = 8;
int signalPin;


WindDirectionSensor::WindDirectionSensor(int pin){
  signalPin = pin;
  pinMode(signalPin, INPUT);
}

void WindDirectionSensor::setSignalPin(int pin){
  signalPin = pin;
}

int WindDirectionSensor::readDirection(){
  return calculateDirection();
}

float WindDirectionSensor::readRawVoltage(){
  return calculateVoltage();
}

int WindDirectionSensor::calculateDirection(){
  float voltage = calculateVoltage();
  float windDirection = (voltage - threshold) * 5.0;
  return round(windDirection) % directionNum;
}

float WindDirectionSensor::calculateVoltage(){
  int rawValue = analogRead(signalPin);
  float voltage = rawValue * 5.0 / 1024.0;
  return voltage;
}



