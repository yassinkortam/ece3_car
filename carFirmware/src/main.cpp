#include <Arduino.h>
#ifndef CONST_H
#define CONST_H
#include "const.h"
#endif
#include "serialtools/atos.h"
#include "serialtools/json.h"
#include "serialtools/buffer.h"
#include "control/drive.h"
#include "control/pos.h"
#include "control/turn.h"
#include "ece3/ECE3.h" // Used for encoder functionality

Drive drive; //drive object 
void setup() {
// This function runs once

  // Pin Settings
  pinMode(LED_RF, OUTPUT);

  pinMode(nSLPL, OUTPUT);
  pinMode(DIR_L, OUTPUT);
  pinMode(PWML, OUTPUT);

  pinMode(nSLPR, OUTPUT);
  pinMode(DIR_R, OUTPUT);
  pinMode(PWMR, OUTPUT);

  ECE3_Init(); // Used for encoder functionality

  Serial.begin(BAUD); // data rate for serial data transmission
  Serial.print("Starting up....");
  delay(2000);
  
}

int donuts = 0;
void loop() {
  
  //reading the IR sensor data
  uint16_t sensorValues[sensor_width];
  ECE3_read_IR(sensorValues);
  
  uint16_t v = VMAX;

  if (donuts > 1){
    v = 0;
    digitalWrite(nSLPL, HIGH);
    digitalWrite(nSLPR, HIGH);
    digitalWrite(DIR_L, FORWARD);
    digitalWrite(DIR_R, FORWARD);
    analogWrite(PWML, 0);
    analogWrite(PWMR, 0);
  }
  else if (!turn(sensorValues)){

    bool curve = false;
    int loc = (getEncoderCount_left() + getEncoderCount_right())/360;

    //way there
    if (donuts < 1){
      if (loc < 2) curve = true;
      if (loc > 13 && loc < 20) curve = true;
      if (loc > 24) curve = true;  
    }
    else{
      if (loc < 3) curve = true;
      if (loc > 7 && loc < 14) curve = true;
      if (loc > 24) curve = true;
    }

    double pos = posFind(sensorValues);
    drive.update(v, pos, curve);

    digitalWrite(nSLPL, drive.nSLPL);
    digitalWrite(nSLPR, drive.nSLPR);

    digitalWrite(DIR_L, drive.DIR_L);
    digitalWrite(DIR_R, drive.DIR_R);
    analogWrite(PWML, drive.PWML);
    analogWrite(PWMR, drive.PWMR);

  }
  else{

    donuts++;

    resetEncoderCount_left();
    resetEncoderCount_right();

    digitalWrite(DIR_L, FORWARD);
    digitalWrite(DIR_R, REVERSE);
    analogWrite(PWML, PWMAX);
    analogWrite(PWMR, PWMAX);

    while(true){
      double revs = (getEncoderCount_left() + getEncoderCount_right())/360.0;
      if (revs >= 1.5) break;
    }
    
    digitalWrite(DIR_L, FORWARD);
    digitalWrite(DIR_R, FORWARD);
    
    analogWrite(PWML, PWMAX);
    analogWrite(PWMR, PWMAX);

    resetEncoderCount_left();
    resetEncoderCount_right();

  }

  /*
  //making a JSON string for export
  Json json;
  String sensor = atos(sensor_width, sensorValues);
  json.push("sensor", sensor); 

  //Buffer the output to protect data
  BufferIO bufferedData;
  bufferedData.setData(json.stringify());
  bufferedData.setStartBuffer(startBufferLength);
  bufferedData.setEndBuffer(endBufferLength);

  //Output the buffered data
  Serial.print(bufferedData.getOutput());
  */
  
}
