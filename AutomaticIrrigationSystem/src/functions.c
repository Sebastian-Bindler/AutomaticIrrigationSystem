/*
 * functions.c
 *
 * Created: 23.01.2021 01:35:47
 * Author: Bindler, Sebastian
 */ 
#define F_CPU 3686400UL // CPU clock

#include <avr/io.h>
#include <util/delay.h>
#include "../inc/functions.h"
#include "../inc/digital.h"

// Error function declaration 
void error(uint8_t _pumpport, uint8_t _pump, uint8_t _alarmport, uint8_t _alarm, uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin){
	
	// Pump shutdown
	setPinLow(_pumpport, _pump);
	
	// Set lamps to error
	lampsError(_lampokport, _lampokpin, _lamperrorport, _lamperrorpin);	
	
	// Turn alarm buzzer on
	setPinHigh(_alarmport, _alarm);		
}

// Filling function
void filling(uint8_t _pumpport, uint8_t _pump, uint8_t _alarmport, uint8_t _alarm, uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin, uint8_t _resetport, uint8_t _reset, uint8_t _fillingport, uint8_t _filling, uint8_t _fillingtime, uint8_t _maxport, uint8_t _maxpin, uint8_t _maxmaxport, uint8_t _pinmaxmax){
	
	// Set lamps to error
	lampsError(_lampokport, _lampokpin, _lamperrorport, _lamperrorpin);
	
	// Toggle filling with time function
	toggleDigitalByTime(_fillingport, _filling, _fillingtime);
	
	// Check if MAXMAX pin is high
	maxAlarm(_pumpport, _pump, _alarmport, _alarm, _lampokport, _lampokpin, _lamperrorport, _lamperrorpin, _resetport, _reset, _maxmaxport, _pinmaxmax);
	
	// check if enough water has been filled in the canister 
	if (checkPin(_maxport, _maxpin) == 0)
	{
		// Wait for reset
		reset(_pumpport, _pump, _alarmport, _alarm, _lampokport, _lampokpin, _lamperrorport, _lamperrorpin, _resetport, _reset);
	}
}

// Reset function
void reset(uint8_t _pumpport, uint8_t _pump, uint8_t _alarmport, uint8_t _alarm, uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin, uint8_t _resetport, uint8_t _reset){
	
	// Wait for reset pin to get high
	while(checkPin(_resetport, _reset) == 1){
		
		// Force error repeatedly
		error(_pumpport, _pump, _alarmport, _alarm, _lampokport, _lampokpin, _lamperrorport, _lamperrorpin);
	}
	// Set lamps to normal
	lampsOk(_lampokport, _lampokpin, _lamperrorport, _lamperrorpin);
}

// Alarm function
void alarm(uint8_t _port, uint8_t _pin){
	
	// Set alarm buzzer on
	setPinHigh(_port, _pin);
}

// Lamperror function
void lampsError(uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin){
	
	// Set Lamp normal to low
	setPinLow(_lampokport, _lampokpin);
	
	// Set Lamp error to high
	setPinHigh(_lamperrorport, _lamperrorpin);
}

void lampsOk(uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin){
	
	// Set Lamp normal to high
	setPinHigh(_lampokport, _lampokpin);
	
	// Set Lamp error to low
	setPinLow(_lamperrorport, _lamperrorpin);
}

// Lampok function
void maxAlarm(uint8_t _pumpport, uint8_t _pump, uint8_t _alarmport, uint8_t _alarm, uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin, uint8_t _resetport, uint8_t _reset, uint8_t _maxmaxport, uint8_t _pinmaxmax){
	
	
	if (checkPin(_portmaxmax, _pinmaxmax) == 1)
	{
		// Wait for reset
		reset(_pumpport, _pump, _alarmport, _alarm, _lampokport, _lampokpin, _lamperrorport, _lamperrorpin, _resetport, _reset);
	}
}

// Toggle by time function declaration
void toggleDigitalByTime(uint8_t _port, uint8_t _pin, uint8_t _time){
	
	// Set pin high
	setPinHigh(_port, _pin);
	
	// Wait _time millisekundes
	_delay_ms(_time);
	
	// Set pin low
	setPinLow(_port, _pin);
}

// Check level
void checkLevel(uint8_t _minport, uint8_t _minpin, uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin){
	
	// Check if min ist high
	if (checkPin(_minport, _minpin) == 1)
	{
		// Set lamps to ok
		lampsOk(_lampokport, _lampokpin, _lamperrorport, _lamperrorpin);
	}
	else {
		// Set lamps to error 
		lampsError(_lampokport, _lampokpin, _lamperrorport, _lamperrorpin);	
	}
}
