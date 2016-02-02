#include "DandelionDisplayController.h"
#include "LED15Controller.h"


#define DISPLAY_SIZE 8
#define delay_time 100

//int westScript[4][DISPLAY_SIZE] = {{1024, 8192, 6, 224, 0, 0, 0, 0},
//                      {0, 0, 0, 0, 32512, 255, 0, 0},
//                      {0, 0, 0, 0, 0, 0, 32767, 0}, 
//                      {0, 0, 0, 0, 0, 0, 0, 32767}};
int eastScript[4][DISPLAY_SIZE] = {{0, 0, 0, 0, 0, 0, 0, 32767}, 
                        {0, 0, 0, 0, 0, 0, 32767, 0}, 
                        {0, 0, 0, 0, 127, 65280, 0, 0}, 
                        {32, 2, 12288, 1792, 0, 0, 0, 0}};
int northScript[2][DISPLAY_SIZE] = {{16, 34, 16452, 2184, 0, 0, 0, 0}, 
                         {256, 8704, 1028, 18568, 0, 0, 0, 0}};
                         
int southScript[2][DISPLAY_SIZE] = {{128, 68, 34, 4369, 0, 0, 0, 0}, 
                         {2048, 9216, 4610, 273, 0, 0, 0, 0}};
int southEastScript[4][DISPLAY_SIZE] = {{0, 0, 0, 0, 0, 0, 4369, 0},
                             {0, 0, 0, 0, 64, 54, 13057, 0},
                             {0, 0, 64, 16420, 9234, 4865, 0, 0},
                             {136, 18432, 9216, 512, 0, 0, 0, 0}};

int northWestScript[4][DISPLAY_SIZE] = {{256, 4097, 8210, 36, 72, 128, 0, 0},
                             {0, 0, 0, 4608, 9218, 18540, 128, 0},
                             {0, 0, 0, 0, 0, 1024, 18636, 0},
                             {0, 0, 0, 0, 0, 0, 2048, 0}};

int northEastScript[4][DISPLAY_SIZE] = {{0, 0, 0, 0, 0, 0, 200, 0},
                             {0, 0, 0, 0, 0, 8294, 19592, 0},
                             {0, 0, 16, 34, 8772, 19464, 0, 0},
                             {1, 4098, 8704, 17408, 2048, 0, 0, 0}};

#define groups 4
LED15Controller *controllers[4];
LED15Controller *left;
LED15Controller *leftC;
LED15Controller *rightC;
LED15Controller *right;
LED15Controller *test;

DandelionDisplayController::DandelionDisplayController(int latchpins[], int datapins[], int clockpins[]){
  Serial.println("Init");
//  controllers = new LED15Controller[4];
//  for(int i = 0; i < groups; i++){
////    LED15Controller *controller = 
//    controllers[i] = new LED15Controller(latchpins[i], datapins[i], clockpins[i]); 
//  }
//  left = new LED15Controller(latchpins[0], datapins[0], clockpins[0]);
  
  rightC = new LED15Controller(latchpins[2], datapins[2], clockpins[2]);
  right = new LED15Controller(latchpins[3], datapins[3], clockpins[3]);
  test = new LED15Controller(latchpins[0], datapins[0], clockpins[0]);
  leftC = new LED15Controller(latchpins[1], datapins[1], clockpins[1]);
  randomSeed(analogRead(A2));
}

DandelionDisplayController::~DandelionDisplayController(){
 delete controllers; 
}

//void DandelionDisplayController::displayEffect(int windDirection, int brightness){ 
//  long part = 0;
//  Serial.println("Display");
//  switch(windDirection){
//    case 0:
//      Serial.println("D" + String(windDirection));
//      part = random(0, 2) * 2;
//      playScript(2, 4, northScript, part);
//      break;
//    case 1:
//      Serial.println("D" + String(windDirection));
//      playScript(4, 7, northEastScript, 0);
//      break;
//    case 2:
//      Serial.println("D" + String(windDirection));
//      playScript(4, 8, eastScript, 0);
//      break;
//    case 3:
//      Serial.println("D" + String(windDirection));
//      playScript(4, 7, southEastScript, part);
//      break;
//    case 4:
//      part = random(0, 2) * 2;
//      Serial.println("D" + String(windDirection));
//      playScript(2, 4, southScript, part);
//      break;
//    case 5:
//      Serial.println("D" + String(windDirection));
//      playScript(4, 7, southWestScript, part);
//      break;
//    case 6:
//      Serial.println("D" + String(windDirection));
//      playScript(4, 8, westScript, part);
//      break;
//    case 7:
//      Serial.println("D" + String(windDirection));
//      playScript(4, 7, northWestScript, part);
//      break;
//    case 8:
//      Serial.println("D" + String(windDirection));
//      playScript(2, 4, northScript, part);
//      break;
//    default:
//      Serial.println("No direction!");  
//      break;  
//  }
//}
//
//void DandelionDisplayController::playScript(int groupSize, int timeSize, int script[][DISPLAY_SIZE], int offset){
//  for(int i = 0; i < timeSize; i++){
//    for(int j = 0; j < groupSize; j++){
//      controllers[j]->ledControl(script[j][i]);
//    }
//    delay(delay_time);
//  }
//}
//
//void DandelionDisplayController::testController(int controllerIndex, int windDirection){
//  Serial.println("test");
//  for (int i = 0; i < 16; i++) {
//      int light = 1 << i;
////      left->ledControl(light);
//      
////      rightC->ledControl(light);
////      right->ledControl(light);
//      test->ledControl(light);
//      leftC->ledControl(light);
//    // pause before next value:
//    delay(500);
//  }
//  
//}

