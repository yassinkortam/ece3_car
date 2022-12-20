#ifndef ARDUINO_H
#define ARDUINO_H
#include <Arduino.h>
#endif

#ifndef CONST_H
#define CONST_H
#include "const.h"
#endif

//drive object
class Drive{
private:
    //Proportional term PID
    double p(double pos);

    //Integral term PID
    double sum;
    double i(double pos);

    //Derivative term PID
    double prevPos;
    //double prevDer;
    double d(double pos);

    //double vel;
public:
    Drive();
    void update(uint16_t vForward, double pos, bool turn);
    uint16_t DIR_L;
    uint16_t DIR_R;
    uint16_t PWML;
    uint16_t PWMR;
    uint16_t nSLPL;
    uint16_t nSLPR;
};

Drive::Drive(){
  this->DIR_L = FORWARD;
  this->DIR_R = FORWARD;
  this->PWML = 0;
  this->PWMR = 0;
  this->nSLPL = HIGH;
  this->nSLPR = HIGH;
  this->prevPos = C;
  //this->prevDer = 0;
  this->sum = 0;
  //this->vel = 0;
}

double Drive::p(double pos){
    return (C - pos);
}

double Drive::i(double pos){
    sum += C - pos;
    return sum;
}

double Drive::d(double pos){
    double der = (C - pos) - (C - prevPos);
    prevPos = pos;
    return der;
}

void Drive::update(uint16_t vForward, double pos, bool turn){

    //STRAIGHT @255
    //Kp = 0.5, Kd = 10

    //CURVE @255
    //Kp = 5, Kd = 10

    double prop = p(pos);
    double intg = i(pos);
    double der = d(pos);

    double kp = 0.7*PWMAX/DMAX;
    double ki = 0*PWMAX/DMAX;
    double kd = 14*PWMAX/DMAX;

    double vDiff = kp*prop + ki*intg + kd*der;

    if (turn){
        vForward = VTURN;
        vDiff = 32*kp*prop + ki*intg + 32*kd*der;
    }

    //detect curve
    /*
    if (abs(prop) > 0.4*DMAX){
        vel = 200;
        vDiff = 2*kp*prop + ki*intg + kd*der;
    }
    
    if (abs(der) > 100*0.6*vForward*0.01){
        vel = 200;
        vDiff = 1*kp*prop + ki*intg + kd*der;
    }
    
    if (abs(der - prevDer) > 100*1*vForward*0.01){
        vel = 50;
        vDiff = 80*kp*prop + ki*intg + 20*kd*der;
    }
    prevDer = der;
    */

    double V = vForward - 0.5*abs(vDiff);
    PWML = V + 0.5*vDiff;
    PWMR = V - 0.5*vDiff;
}