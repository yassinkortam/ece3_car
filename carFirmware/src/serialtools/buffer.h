#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

//Allows for buffering of data being sent to serial with strings of start and end markers
class BufferIO{
private:
    String output;
    String data;
    String startBuffer;
    String endBuffer;
public:
    //Data to be sent to serial
    void setData(String data);
    //Set the length of the start buffer
    void setStartBuffer(int length);
    //Set the length of the end buffer
    void setEndBuffer(int length);
    //Set the final buffered output
    String getOutput();
};

void BufferIO::setData(String data){
    this->data = data;
}

void BufferIO::setStartBuffer(int length){
    startBuffer = "";
    for (int i=0; i<length; i++) startBuffer += "S";
}

void BufferIO::setEndBuffer(int length){
    endBuffer = "";
    for (int i=0; i<length; i++) endBuffer += "E";
}

String BufferIO::getOutput(){
    return startBuffer + data + endBuffer;
}