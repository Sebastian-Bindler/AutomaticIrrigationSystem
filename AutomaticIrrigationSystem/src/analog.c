/*
 * analog.c
 *
 * Created: 23.01.2021 01:35:15
 *  Author: Bindler, Sebastian
 */ 

#include <avr/io.h>
#include "../inc/analog.h"
#include "../inc/init.h"

// Reading out analog pin function
uint16_t readADC(uint8_t _pin){
	
	// Initialize analog to digital converter
	initADC(_pin);
	
	// Carry out the first ADC evaluation || Erste ADC Auswertung durchführen
	ADCSRA |= (1 << ADSC);
	
	// wait for complete reading adc ||  warten bis ADC Wert fertig eingelesen wurde ADIF wird 1 wenn ADC Lesung fertig ist -> invertieren damit while verlassen wird
	while(!(ADCSRA & (1 << ADIF)));

	uint16_t adc_result = 0;	// Variable for adc result
	adc_result = ADCL; 
	adc_result |= (ADCH << 8); 
	
	return adc_result; // Return adc result 
}