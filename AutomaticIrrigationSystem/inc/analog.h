/*
 * Analog.h
 *
 * Created: 22.01.2021 21:48:53
 *  Author: Bindler, Sebastian
 */ 

#include <avr/io.h>

#ifndef ANALOG_H_
#define ANALOG_H_

// Reading out analog pin function
uint16_t readADC(uint8_t _pin);


#endif /* ANALOG_H_ */