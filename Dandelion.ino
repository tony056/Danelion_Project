#include "WindDirectionSensor.h"
WindDirectionSensor *wdSensor;

void setup() {
  // put your setup code here, to run once:
  wdSensor = new WindDirectionSensor(A0);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("The v: " + String(wdSensor->readDirection()));
}
