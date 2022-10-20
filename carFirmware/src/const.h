
// PIN ASSIGNMENTS

//left motor
const int nSLPL = 31;
const int DIR_L  = 29;
const int PWML  = 40;

//right motor
const int nSLPR = 31;
const int DIR_R  = 30;
const int PWMR  = 39;

// Encoder Variables
long enc_bin_cnt;
const unsigned long enc_bin_len = 50; // 50 ms bins
    // Encoder Speed Calculation Explanation:
    // We wait for a set amount of time (enc_bin_len), and find how many
    // times the encoder has incremented in that period. We call 
    // this period a bin when refering to the encoder. The number 
    // encoder counts per bin is a proportional to speed.