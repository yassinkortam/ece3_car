
#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

String atos(int size, uint16_t a[]){
    String s = "[";
    for (int i=0; i<size; i++){
        s = s + a[i];
        if (i < size -1) s+= ",";
    }

    s += "]";
    return s;
}