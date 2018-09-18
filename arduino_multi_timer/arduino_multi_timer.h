/*
These definitions and the arrays are the bit you should edit
Make sure to make NUM_PINS the number of timers you have going
MAX_T is the time in milliseconds it will wait when the ADC reads 1023
MIN_T is the time in milliseconds it will wait when the ADC read 0
START_PIN_TYPE sets the mode of the start timer pin, should be either INPUT or INPUT_PULLUP
OUTPUT ACTIVE sets the signal type when the timer is complete, should be either HIGH or LOW

signal_time sets the time for which the output is active in milliseconds
startPins is the array of pins which will be used for starting each timer
potPins is the array of pins which will be used for the variable timer input, these must be analogue
outputPins is the array of pins which will be written for the output
*/

#define NUM_PINS 1
#define MAX_T 120000
#define MIN_T 500

#define START_PIN_TYPE INPUT_PULLUP
#define OUTPUT_ACTIVE HIGH

unsigned char startPins[NUM_PINS] = {2};
unsigned char potPins[NUM_PINS] = {A0};
unsigned char outputPins[NUM_PINS] = {6};
unsigned long long signal_time[NUM_PINS] = {200};