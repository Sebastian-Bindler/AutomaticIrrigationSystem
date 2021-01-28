/*
 * Digital.h
 *
 * Created: 22.01.2021 21:48:27
 *  Author: Bindler, Sebastian
 */ 
#include <avr/io.h>

#ifndef DIGITAL_H_
#define DIGITAL_H_

// Set function to set pin high
void setPinHigh(uint8_t _port, uint8_t _pin);

// Set function to set pin low
void setPinLow(uint8_t _port, uint8_t _pin);

// Check pin state function
uint8_t checkPin(uint8_t _port, uint8_t _pin);

#endif /* DIGITAL_H_ */