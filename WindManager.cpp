#include "WindManager.h"
#define dir_num 8

int window_size = 100;
int pos = 0;
WindDirectionSensor *wdSensor;
WindSpeedSensor *wspdSensor;
int *directionWindow;
float *speedWindow;

WindManager::WindManager(int windowSize, int directionPin, int speedPin){
  window_size = windowSize;
  wdSensor = new WindDirectionSensor(directionPin);
  wspdSensor = new WindSpeedSensor(speedPin);
  directionWindow = new int[dir_num];
  speedWindow = new float[window_size];
}

WindManager::~WindManager(){
  delete wdSensor;
  delete wspdSensor;
}

void WindManager::collectData(){
  pos = pos % window_size;
  speedWindow[pos] = wspdSensor->readSpeed();
  pos++;
  int dir = wdSensor->readDirection();
  directionWindow[dir]++;
}

int WindManager::getDirection(){
  int maxDir = 0;
  int dir = 0;
  for(int i = 0; i < dir_num; i++){
    if(directionWindow[i] > maxDir){
      maxDir = directionWindow[i];
      dir = i;
    }
    directionWindow[i] = 0;
  }
  return dir;
}

float WindManager::getSpeed(){
  float avg = 0;
  for(int i = 0; i < window_size; i++){
    avg += speedWindow[i];
  }
  avg = avg / window_size;
  return avg;
}

float WindManager::getDirRawVoltage(){
  return wdSensor->readRawVoltage();
}



