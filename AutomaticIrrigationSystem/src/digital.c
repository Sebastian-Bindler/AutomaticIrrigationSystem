/*
 * digital.c
 *
 * Created: 23.01.2021 01:35:29
 *  Author: Bindler, Sebastian
 */ 

#include <avr/io.h>
#include "../inc/digital.h"

// Set function to set pin high
void setPinHigh(uint8_t _port, uint8_t _pin)
{
	_port |= (1 << _pin);	//Set Pin High
}

// Set function to set pin low
void setPinLow(uint8_t _port, uint8_t _pin)
{
	_port &= ~(1 << _pin);	// Set Pin Low
}

// Check pin state function
uint8_t checkPin(uint8_t _port, uint8_t _pin){
	
	if (!(_port & ( 1 << _pin))) // Query whether the pin is high or low || Abfrage ob der Pin High ist
	{
		return 1; // Give 1 back for high || Es wird 1 zurückgegeben wenn der Pin High ist
	}
	
	else
	{
		return 0; // Give 0 back for low || Es wird 0 zurückgegeben wenn der Pin Low ist
	}
}

