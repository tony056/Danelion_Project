#include "WindManager.h"
//#include "DandelionDisplayController.h"
//#include "LED15Controller.h"
#include "Sparkfun_Tlc5940.h"
#include "tlc_fades.h"


#include <Time.h>
#include <TimeAlarms.h>

#define judgeTimeout 5
#define win_size 10
#define timeSlides 20
#define delayTime 1000
#define maxVal 0
#define minVal 4095

                        //2 5 1,2 5,6,7 ALL7 ALL8 ALL15 ALL15 


int westScript[4][8] = {{1024, 8192, 6, 224, 0, 0, 0, 0},
                      {0, 0, 0, 0, 32512, 255, 0, 0},
                      {0, 0, 0, 0, 0, 0, 32767, 0}, 
                      {0, 0, 0, 0, 0, 0, 0, 32767}};
int southWestScript[4][8] = {{2048, 16392, 8260, 34, 17, 0, 0, 0},
                             {0, 0, 0, 17408, 8708, 4403, 0, 0},
                             {0, 0, 0, 0, 0, 8704, 4371, 0},
                             {0, 0, 0, 0, 0, 0, 4353, 0}};

WindManager *windManager;
//DandelionDisplayController *displayController;
boolean isPlaying = false;
void setup() {
  Serial.begin(9600);
  windManager = new WindManager(win_size, A0, A1);
//  displayController = new DandelionDisplayController(latchPins, dataPins, clockPins);
  initLED();
//  left = new LED15Controller(2, 4, 3);
//  right = new LED15Controller(5, 7, 6);
//  setTime(8,29,0,1,1,16);
//  Alarm.timerRepeat(judgeTimeout, CheckStatus);
}

void loop() {
//  Serial.println("------------");
//  windManager->collectData();
//  Alarm.delay(1000);
//  displayController->testController(0, 0);
  CheckStatus();
  if(!isPlaying){
    Haha();
    
  }
//  CheckStatus();
  tlc_updateFades();
}

void CheckStatus(){
//  Serial.println("Size: " + String(tlc_fadeBufferSize));
//  int avgDir = windManager->getDirection();
//  float avgSpeed = windManager->getSpeed();
  isPlaying = false;
  for(int i = 0; i < NUM_TLCS * 16; i++){
    if(tlc_isFading(i)){
      isPlaying = true;
//      Serial.println("No. " + String(i));
      break;
    }
  }
//  Serial.println(isPlaying);
}

void Haha(){
//  Serial.println("HAha");
  uint32_t start = millis() + 50;
  uint32_t endTime = start + 3000;
  
//  for(int k = 0 ; k < 2; k++){ 

  int record = 9;
  int temp = 9;
  int count = 0;
  for(int i = 1; i < 4; i++){
    for(int k = 0; k < 4; k++){
     record = temp + k * 16;
     for(int j = record; j < record + i; j++){
       uint32_t istart = start + 1500 * (i - 1);
       uint32_t iend = istart + 3000;
       if(!tlc_isFading(j) && tlc_fadeBufferSize < TLC_FADE_BUFFER_LENGTH - 2){
         count++;
         tlc_addFade(j, minVal, maxVal, istart, iend);
         tlc_addFade(j, maxVal, minVal, iend, iend + 3000); 
       }else if(tlc_isFading(j)){
         Serial.println(String(j) + " is fading");
       }else if(tlc_fadeBufferSize < TLC_FADE_BUFFER_LENGTH - 2){
         Serial.println("Overload");
       }
      }
    }
    temp += i;
  }
  Serial.println("Count: " + String(tlc_fadeBufferSize));
}

void initLED(){
  Tlc.init();
//  Tlc.clear();
  for(int i = 0; i < NUM_TLCS * 16; i++){
    Serial.println(String(i));
    Tlc.set(i, minVal);
    tlc_removeFades(i);
  }
  Tlc.update();
  
}


