#include "WindManager.h"
#include <Time.h>
#include <TimeAlarms.h>

#define judgeTimeout 5
#define win_size 10
#define latchPin 2
#define clockPin 3
#define dataPin 4
#define pwmEnablePin 5

WindManager *windManager;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  windManager = new WindManager(win_size, A0, A1);
  setTime(8,29,0,1,1,16);
  Alarm.timerRepeat(judgeTimeout, CheckStatus);
  pinMode(13, OUTPUT);
  initLED();
}

void loop() {
//  Serial.println("------------");
  windManager->collectData();
  Alarm.delay(1000);
}

void CheckStatus(){
  Serial.println("Check");
  int avgDir = windManager->getDirection();
  float avgSpeed = windManager->getSpeed();
  Serial.println("The D: " + String(avgDir) + "\nThe Speed: " + String(avgSpeed));
  Haha();
}

void Haha(){
  for (int i = 0; i < 16; i++) {
    int numToDisplay = 1 << i;
    byte high_byte = highByte(numToDisplay);
    byte low_byte = lowByte(numToDisplay);
    //take the latchPin low so the LEDs don't change while we are writing data
    digitalWrite(latchPin, LOW);
 
    //shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, high_byte);  
    shiftOut(dataPin, clockPin, MSBFIRST, low_byte);
    //take the latch pin high so the pins reflect
    //the data we have sent
    digitalWrite(latchPin, HIGH);

    // pause before next value:
    delay(50);
  }
}

void ledTest(){
  
}

void initLED(){
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(pwmEnablePin, OUTPUT);
}

