#include <Arduino.h>
#include "const.h"
#include "atos.h"

#include "/Users/yassinkortam/Documents/Arduino/libraries/ECE3/src/ECE3.h" // Used for encoder functionality

void setup() {
// This function runs once

  // Pin Settings
  pinMode(nSLPL, OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(PWML, OUTPUT);

  pinMode(nSLPR, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(PWMR, OUTPUT);

  ECE3_Init(); // Used for encoder functionality

  Serial.begin(9600); // data rate for serial data transmission
  Serial.print("Starting up....");
  delay(2000);
  
}

void loop() {
  uint16_t sensorValues[8];
  ECE3_read_IR(sensorValues);
  String sensor = atos(8, sensorValues);
  String json = "{\"sensor\":" + sensor + "}";
  Serial.println(json);
  delay(100);
}
