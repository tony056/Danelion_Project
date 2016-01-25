#include "WindManager.h"
#include "LED15Controller.h"
#include <Time.h>
#include <TimeAlarms.h>

#define judgeTimeout 5
#define win_size 10
#define latchPin 2
#define clockPin 3
#define dataPin 4
#define pwmEnablePin 5
                        //2 5 1,2 5,6,7 ALL7 ALL8 ALL15 ALL15 
int westScript[4][8] = {{1024, 8192, 6, 224, 0, 0, 0, 0},
                      {0, 0, 0, 0, 32512, 255, 0, 0},
                      {0, 0, 0, 0, 0, 0, 32767, 0}, 
                      {0, 0, 0, 0, 0, 0, 0, 32767}};
int eastScript[4][8] = {{0, 0, 0, 0, 0, 0, 0, 32767}, 
                        {0, 0, 0, 0, 0, 0, 32767, 0}, 
                        {0, 0, 0, 0, 127, 65280, 0, 0}, 
                        {32, 2, 12288, 1792, 0, 0, 0, 0}};
int northScript[4][4] = {{16, 34, 16452, 2184}, 
                         {256, 8704, 1028, 18568}, 
                         {0, 0, 0, 0}, 
                         {0, 0, 0, 0}};
                         
int southScript[2][4] = {{128, 68, 34, 4369}, 
                         {2048, 9216, 4610, 273}};
int southWestScript[4][7] = {{2048, 16392, 8260, 34, 17, 0, 0},
                             {0, 0, 0, 17408, 8708, 4403, 0},
                             {0, 0, 0, 0, 0, 8704, 4371},
                             {0, 0, 0, 0, 0, 0, 4353}};


WindManager *windManager;
LED15Controller *leftController;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  windManager = new WindManager(win_size, A0, A1);
//  setTime(8,29,0,1,1,16);
//  Alarm.timerRepeat(judgeTimeout, CheckStatus);
//  pinMode(13, OUTPUT);
//  initLED();
  leftController = new LED15Controller(latchPin, dataPin, clockPin);
}

void loop() {
//  Serial.println("------------");
//  windManager->collectData();
//  Alarm.delay(1000);
  for(int i = 0; i < 7;i++){
    Serial.println(i);
    leftController->ledControl(southWestScript[3][i]);
//    Haha();
    delay(3000);
  }

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

