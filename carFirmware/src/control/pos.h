#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

//Find average position of track line on sensor array
double posFind(uint16_t sensorValues[]){
  
  //find two largest values
  double max1 = 0;
  double pos1 = 0;
  for (uint16_t i=0; i<8; i++){
    if (sensorValues[i] > max1){
      max1=sensorValues[i];
      pos1 = i;
    }
  }
  double max2 = 0;
  double pos2 = 0;
  for (int i=0; i<8; i++){
    if (sensorValues[i] > max2 && i != pos1){
      max2=sensorValues[i];
      pos2 = i;
    }
  }
  double norm = max1 + max2;
  double weighted = max1*(pos1+1) + max2*(pos2+1);
  return weighted/norm;

}