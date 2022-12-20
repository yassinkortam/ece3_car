#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef CONST_H
#define CONST_H
#include "const.h"
#endif

bool turn(uint16_t sensorValues[]){
    double MINDEV = 0.15;
    double avg = 0;
    for (uint16_t i=0; i<8; i++){
        avg += abs(sensorValues[i])*0.125;
    }
    double outlier = sensorValues[0];
    for (uint16_t i=0; i<8; i++){
       if (outlier < sensorValues[i]) outlier = sensorValues[i];
    }
    if (outlier < 10) return true;
    double delta = abs(avg - outlier)/avg;
    if (delta < MINDEV) return true;
    else return false;

}