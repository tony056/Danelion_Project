#include "WindDirectionSensor.h"
#include "WindSpeedSensor.h"

WindDirectionSensor *wdSensor;
WindSpeedSensor *wspdSensor;

void setup() {
  // put your setup code here, to run once:
  wdSensor = new WindDirectionSensor(A0);
  wspdSensor = new WindSpeedSensor(A1);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("The d: " + String(wdSensor->readDirection()));
  Serial.println("The speed: " + String(wspdSensor->readSpeed()));
}
