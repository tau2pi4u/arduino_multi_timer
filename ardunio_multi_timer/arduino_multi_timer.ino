/*
These definitions and the arrays are the bit you should edit
Make sure to make NUM_PINS the number of timers you have going
MAX_T is the time in milliseconds it will wait when the ADC reads 1023
MIN_T is the time in milliseconds it will wait when the ADC read 0
START_PIN_TYPE sets the mode of the start timer pin, should be either INPUT or INPUT_PULLUP
OUTPUT ACTIVE sets the signal type when the timer is complete, should be either HIGH or LOW
SIGNAL_TIME sets the time for which the output is active in milliseconds

startPins is the array of pins which will be used for starting each timer
potPins is the array of pins which will be used for the variable timer input, these must be analogue
outputPins is the array of pins which will be written for the output
*/

#define NUM_PINS 1
#define MAX_T 120000
#define MIN_T 500

#define START_PIN_TYPE INPUT_PULLUP
#define OUTPUT_ACTIVE HIGH
#define SIGNAL_TIME 200

unsigned char startPins[NUM_PINS] = {2};
unsigned char potPins[NUM_PINS] = {A0};
unsigned char outputPins[NUM_PINS] = {6};

/*********************************************
	   DON'T EDIT THIS ANYTHING BELOW
*********************************************/

#define POT_PIN_TYPE INPUT
#define OUTPUT_PIN_TYPE OUTPUT

#if OUTPUT_ACTIVE == HIGH
	#define OUTPUT_DEFAULT LOW
	#define OUTPUT_ACTIVE_READ true
#else
	#define OUTPUT_DEFAULT HIGH
	#define OUTPUT_ACTIVE_READ false
#endif

#if START_PIN_TYPE == INPUT_PULLUP
	#define TIMER_START false
#else 
	#define TIMER_START true
#endif

unsigned long long tEnd[NUM_PINS] = {0};

void setup() {
	// put your setup code here, to run once:
    Serial.begin(9600);
    for(unsigned int i = 0; i < NUM_PINS; i++)
    {
      pinMode(startPins[i], START_PIN_TYPE);
      pinMode(potPins[i], POT_PIN_TYPE);
      pinMode(outputPins[i], OUTPUT_PIN_TYPE);
	  digitalWrite(outputPins[i], OUTPUT_DEFAULT);
    }
}

void loop() {
  // put your main code here, to run repeatedly:
	for(unsigned char i = 0; i < NUM_PINS; i++)
	{
		unsigned long long tNow = millis();
		if(tEnd[i] == 0 && startPins[i] == TIMER_START)
		{
			unsigned short potInput = analogRead(potPins[i]);
			tEnd[i] = tNow + map(potInput, 0, 1023, MIN_T, MAX_T);
		}
		else if(tEnd[i] != 0 && tNow > tEnd[i] + SIGNAL_TIME)
		{
			digitalWrite(outputPins[i], OUTPUT_DEFAULT);
			tEnd[i] = 0;
		}
		else if(tEnd[i] != 0 && tNow > tEnd[i] && digitalRead(outputPins[i]) != OUTPUT_ACTIVE_READ)
		{
			digitalWrite(outputPins[i], OUTPUT_ACTIVE);
		}
	}
}
