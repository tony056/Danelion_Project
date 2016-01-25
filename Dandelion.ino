#include "WindManager.h"
#include "DandelionDisplayController.h"
#include <Time.h>
#include <TimeAlarms.h>

#define judgeTimeout 5
#define win_size 10
//#define latchPin 2
//#define clockPin 3
//#define dataPin 4
#define pwmEnablePin 5
                        //2 5 1,2 5,6,7 ALL7 ALL8 ALL15 ALL15 

int latchPins[] = {2, 5, 8, 11};
int clockPins[] = {3, 6, 9, 12};
int dataPins[] = {4, 7, 10, 13};

WindManager *windManager;
//LED15Controller *leftController;
DandelionDisplayController *displayController;

void setup() {
  Serial.begin(9600);
  windManager = new WindManager(win_size, A0, A1);
  displayController = new DandelionDisplayController(latchPins, dataPins, clockPins);
//  setTime(8,29,0,1,1,16);
  Alarm.timerRepeat(judgeTimeout, CheckStatus);
//  pinMode(13, OUTPUT);
//  initLED();
//  leftController = new LED15Controller(latchPin, dataPin, clockPin);
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
  displayController->displayEffect(avgDir, 0);
}

//void Haha(){
//  for (int i = 0; i < 16; i++) {
//    int numToDisplay = 1 << i;
//    byte high_byte = highByte(numToDisplay);
//    byte low_byte = lowByte(numToDisplay);
//    //take the latchPin low so the LEDs don't change while we are writing data
//    digitalWrite(latchPin, LOW);
// 
//    //shift out the bits
//    shiftOut(dataPin, clockPin, MSBFIRST, high_byte);  
//    shiftOut(dataPin, clockPin, MSBFIRST, low_byte);
//    digitalWrite(latchPin, HIGH);
//
//    // pause before next value:
//    delay(50);
//  }
//}


