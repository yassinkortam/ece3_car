
// PIN ASSIGNMENTS

const int LED_RF = 41;

//left motor
const int nSLPL = 31;
const int DIR_L  = 29;
const int PWML  = 40;

//right motor
const int nSLPR = 11;
const int DIR_R  = 30;
const int PWMR  = 39;

// ENCODER VARIABLES
long enc_bin_cnt;
const unsigned long enc_bin_len = 50; // 50 ms bins
    // Encoder Speed Calculation Explanation:
    // We wait for a set amount of time (enc_bin_len), and find how many
    // times the encoder has incremented in that period. We call 
    // this period a bin when refering to the encoder. The number 
    // encoder counts per bin is a proportional to speed.

//BAUD
const int BAUD = 9600;

//SENSOR VARIABLES
const int sensor_width = 8;

//IO VARIABLES
const int startBufferLength = 10;
const int endBufferLength = 10;

//DRIVE VARIABLES
const double pDiff = 0.6; //pDiff = 1 - kp
const uint16_t VTURN = 200;
const uint16_t VMAX = 255;
const uint16_t PWMAX = 255;
const long D = 0.25;
const long C = 4.5;
const long DMAX = 3.5;
const uint16_t FORWARD = 0;
const uint16_t REVERSE = 1;

//DONUT VARIABLE
