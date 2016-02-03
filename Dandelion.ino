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
// #define duration 3000
#define SCRIPT_SIZE 20

#define NORTH_SIZE 17 
#define SOUTH_SIZE 27
#define EAST_SIZE  46
#define WEST_SIZE  50
#define NORTH_EAST_SIZE 32
#define SOUTH_EAST_SIZE 32
#define SOUTH_WEST_SIZE 19
#define NORTH_WEST_SIZE 19

#define NORTH_PERIOD_SIZE 5  
#define SOUTH_PERIOD_SIZE 6
#define EAST_PERIOD_SIZE 7
#define WEST_PERIOD_SIZE 7
#define NORTH_EAST_PERIOD_SIZE 6
#define SOUTH_EAST_PERIOD_SIZE 6
#define SOUTH_WEST_PERIOD_SIZE 5
#define NORTH_WEST_PERIOD_SIZE 5
#define WHOLE_SIZE 7                     //2 5 1,2 5,6,7 ALL7 ALL8 ALL15 ALL15 


int northScript[NORTH_SIZE] = {22, 
                               19, 26,
                               17, 23, 31, 
                               18, 20, 27, 29, 34,
                               21, 24, 25, 28, 30, 32};
int northPeriod[NORTH_PERIOD_SIZE] = {1, 2, 3, 5, 6};

int southScript[SOUTH_SIZE] = {54, 48, 53, 43, 47, 58, 39, 42, 
                                  52, 60, 36, 38, 41, 46, 51, 57, 
                                  59, 33, 35, 37, 40, 45, 44, 49, 
                                  50, 55, 56};
int southPeriod[SOUTH_PERIOD_SIZE] = {1, 2, 3, 4, 7, 10};  

int eastScript[EAST_SIZE] = {59, 
                             57, 60, 
                             46, 51, 52,
                             38, 39, 42, 43, 47,
                             28, 29, 30, 31, 32, 33, 34, 36,
                             15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
                             1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};  
int eastPeriod[EAST_PERIOD_SIZE] = {1, 2, 3, 5, 8, 13, 14};

int westScript[WEST_SIZE] = {2,
                             5, 6, 
                             8, 9, 11, 
                             12, 13, 14, 16, 17, 
                             18, 20, 21, 24, 25, 27, 28, 
                             29, 31, 32, 33, 34, 35, 36, 37, 38, 39, 41, 42, 43, 
                             40, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60};
int westPeriod[WEST_PERIOD_SIZE] = {1, 2, 3, 5, 8, 13, 18};                             

int northEastScript[NORTH_EAST_SIZE] = {49, 
                                        44, 50, 
                                        40, 45, 51, 
                                        33, 35, 36, 37, 41, 
                                        19, 23, 26, 27, 29, 31, 32, 34, 
                                        10, 12, 13, 14, 16, 17, 18, 20, 21, 24, 25, 28, 30};
int northEastPeriod[NORTH_EAST_PERIOD_SIZE] = {1, 2, 3, 5, 8, 13};

int southEastScript[SOUTH_EAST_SIZE] = {54,
                                        48, 53, 
                                        39, 43, 47, 
                                        30, 32, 34, 38, 42, 
                                        21, 24, 25, 27, 28, 29, 31, 36, 
                                        7, 11, 13, 15, 16, 17, 18, 19, 20, 22, 23, 26, 33};
int southEastPeriod[SOUTH_EAST_PERIOD_SIZE] = {1, 2, 3, 5, 8, 13};

int southWestScript[SOUTH_WEST_SIZE] = {3, 
                                        6, 10,
                                        9, 12, 14, 
                                        13, 15, 16, 17, 18, 
                                        19, 20, 21, 22, 23, 24, 26, 27};
int southWestPeriod[SOUTH_WEST_PERIOD_SIZE] = {1, 2, 3, 5, 8};

int northWestScript[NORTH_WEST_SIZE] = {7, 
                                        15, 16,
                                        17, 19, 22, 
                                        20, 23, 24, 26, 27, 
                                        25, 28, 29, 30, 31, 32, 33, 34};
int northWestPeriod[NORTH_WEST_PERIOD_SIZE] = {1, 2, 3, 5, 8};


int eachDuration[7] = {13, 8, 5, 3, 2, 1, 1};
int strength[7] = {0, 768, 1532, 2560, 3072, 3584, 3584};


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
   windManager->collectData();
//  Alarm.delay(1000);
//  displayController->testController(0, 0);
  CheckStatus();
  if(!isPlaying){
    // Haha();
    int avgDir = windManager->getDirection();
    setScript(avgDir);
  }
  tlc_updateFades();
}

void CheckStatus(){
//  Serial.println("Size: " + String(tlc_fadeBufferSize));
  
//  float avgSpeed = windManager->getSpeed();
  isPlaying = false;
  for(int i = 0; i < NUM_TLCS * 16; i++){
    if(tlc_isFading(i)){
      isPlaying = true;
//      Serial.println("No. " + String(i));
      break;
    }
  }
}

void Haha(){
//  Serial.println("HAha");
  uint32_t start = millis() + 50;
  uint32_t endTime = start + 3000;
  
//  for(int k = 0 ; k < 2; k++){ 

  int record = 0;
  int temp = 0;
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

void addFading(TLC_CHANNEL_TYPE channel, uint32_t maxValue, uint32_t minValue, uint32_t startTime, uint32_t endTime){
  if(!tlc_isFading(channel) && tlc_fadeBufferSize < TLC_FADE_BUFFER_LENGTH - 2){
    tlc_addFade(channel, minValue, maxValue, startTime, endTime);
    uint32_t allEnd = endTime + (endTime - startTime);
    tlc_addFade(channel, maxValue, minValue, endTime, allEnd);
    // return true;
  }else{
    Serial.println("cannot add");
  }
  // return false;
}

void setScript(int dir){
  switch (dir) {
      case 0:
        runScript(northScript, northPeriod, NORTH_PERIOD_SIZE);
        break;
      case 1:
        runScript(northEastScript, northEastPeriod, NORTH_EAST_PERIOD_SIZE);
        break;
      case 2: //east
        runScript(eastScript, eastPeriod, EAST_PERIOD_SIZE);
        // runScript(westScript, westPeriod, WEST_PERIOD_SIZE);
        break;
      case 3:
        runScript(southEastScript, southEastPeriod, SOUTH_EAST_PERIOD_SIZE);
        break;
      case 4: //south
        runScript(southScript, southPeriod, SOUTH_PERIOD_SIZE);
        break;
      case 5:
        runScript(southWestScript, southWestPeriod, SOUTH_WEST_PERIOD_SIZE);
        break;
      case 6: //west
        runScript(westScript, westPeriod, WEST_PERIOD_SIZE);
        break;
      case 7:
        runScript(northWestScript, northWestPeriod, NORTH_WEST_PERIOD_SIZE);
        break;
      default:
        Serial.println("default");
        break;
        // do something
  }
}

void runScript(int* script, int* period, int period_size){
  int startIndex = WHOLE_SIZE - period_size;
  int temp = 0;
  uint32_t prevStart = 0;

  for(int i = 0; i < period_size; i++){
    int durationIndex = startIndex + i;
    uint32_t startTime = 0;
    if(i == 0)
      startTime = millis() + 50;
    else 
      startTime = prevStart + eachDuration[durationIndex - 1] * 500;
    uint32_t endTime = startTime + eachDuration[durationIndex] * 500;
    for(int j = temp; j < temp + period[i]; j++){
      addFading(script[j] - 1, strength[durationIndex], minVal, startTime, endTime);
    }
    prevStart = startTime;
    temp += period[i];
  }
}


