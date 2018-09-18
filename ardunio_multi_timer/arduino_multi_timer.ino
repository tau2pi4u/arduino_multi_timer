/*********************************************
		  ONLY EDIT THE HEADER
*********************************************/

#include "arduino_multi_timer.h"

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
		else if(tEnd[i] != 0 && tNow > tEnd[i] + signal_time[i])
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
