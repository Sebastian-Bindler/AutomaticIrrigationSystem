/*
 * init.c
 *
 * Created: 22.01.2021 21:51:48
 *  Author: Bindler, Sebastian
 */ 

#include <avr/io.h>
#include "../inc/init.h"

// Initialize digital output function || Pin als Ausgang definieren
void initPortPinOutput(uint8_t _port, uint8_t _pin, uint8_t _pullup){
	
	// Set pin as output || Pin als Ausgang
	_port |= (1 << _pin);		
	
	if (_pullup  == 1) // Query whether pullup resistor should be activated || Abfrage ob der Pullup Widerstand aktiviert werden soll
	{
		// Start pullup resistor init function
		initPullUpR(_port, _pin); 
	}
}

// Pin als Eingang definieren
void initPortPinInput(uint8_t _port, uint8_t _pin, uint8_t _pullup){
	
	// Set pin as input || Pin als Eingang
	_port = ~(1 << _pin);
	
	if (_pullup  == 1) // Query whether pullup resistor should be activated || Abfrage ob der Pullup Widerstand aktiviert werden soll
	{
		// Start pullup resistor init function
		initPullUpR(_port, _pin);
	}
}

// Initialize pullup resistor function || Pin Pullup Widerstand aktivieren
void initPullUpR(uint8_t _port, uint8_t _pin){
	
	// Activate pullup resistor || Pullup Widerstand für Pin aktivieren
	_port |= (1 << _pin);
}

// Initialize digital inputs function
void initDigitalInput(uint8_t _portDRN, uint8_t _pinDRN, uint8_t _pullupDRN, uint8_t _portMIN, uint8_t _pinMIN, uint8_t _pullupMIN, uint8_t _portMAX, uint8_t _pinMAX, uint8_t _pullupMAX, uint8_t _portMAXMAX, uint8_t _pinMAXMAX, uint8_t _pullupMAXMAX uint8_t _portRESET, uint8_t _pinRESET, uint8_t _pullupRESET)
{
	// Start pin input init functions
	initPortPinInput(_portDRN,_pinDRN, _pullupDRN);
	initPortPinInput(_portMIN,_pinMIN, _pullupMIN);
	initPortPinInput(_portMAX,_pinMAX, _pullupMAX);
	initPortPinInput(_portMAXMAX,_pinMAXMAX, _pullupMAXMAX);
	initPortPinInput(_portRESET,_pinRESET, _pulluuRESET);
}

// Initialize digital outputs function
void initDititalOuput(uint8_t _portPUMP, uint8_t _pinPUMP, uint8_t _pullupPUMP, uint8_t _portFILLING, uint8_t _pinFILLING, uint8_t _pullupFILLING, uint8_t _portEMPTYLAMP, uint8_t _pinEMPTYLAMP, uint8_t _pullupEMPTYLAMP, uint8_t _portFILLEDLAMP, uint8_t _pinFILLEDLAMP, uint8_t _pullupFILLEDLAMP, uint8_t _portALARM, uint8_t _pinALARM, uint8_t _pullupALARM)
{
	// Start pin output init functions
	initPortPinOutput(_portPUMP, _pinPUMP, _pullupPUMP);
	initPortPinOutput(_portFILLING, _pinFILLING, _pullupFILLING);
	initPortPinOutput(_portEMPTYLAMP, _pinEMPTYLAMP, _pullupEMPTYLAMP);
	initPortPinOutput(_portFILLEDLAMP, _pinFILLEDLAMP, _pullupFILLEDLAMP);
	initPortPinOutput(_portALARM, _pinALARM, _pullupALARM);
}

// Initialize analog to digital converter function 
void initADC(uint8_t _pin){
	
	// Activate ADC
	ADCSRA |= (1 << ADEN); 
	
	// Set Reference voltage: internal reference voltage
	ADMUX |= ((1 << REFS1) | (1 << REFS0)); 
	
	// Set Prescaler: 3,686Mhz / 32 = 115kHz => ADPS2 = 1, ADPS1 = 0, ADPS0 = 1
	ADCSRA |= (1 << ADPS2) | (0 << ADPS1) | (1 << ADPS0); 
	
	// Switch Case for set ADMUX
	switch(_pin){ 
		case 0:
		ADMUX |= 0x00;
		break;
		case 1:
		ADMUX |= 0x01;
		break;
		case 2:
		ADMUX |= 0x02; 
		break;
		case 3:
		ADMUX |= 0x03;
		break;
		case 4:
		ADMUX |= 0x04;
		break;
		case 5:
		ADMUX |= 0x05;
		break;
		default:
		break;
	}
	
// Config ADC as freerunning mode
	ADCSRA |= (1 << ADFR); 
	
// First execution for initializing the ADC	
	ADCSRA |= (1 << ADSC); 
}

// Initialize interrupt function declaration
void initInterrupt(uint8_t _port, uint8_t _pin, uint8_t _pullup, uint8_t _port2, uint8_t _pin2, uint8_t _pullup2)
{
	// Start pin input init functions for INT0
	initDigitalInput(_port, _pin, _pullup);
	
	// Start pin input init functions for INT1
	initDigitalInput(_port2, _pin2, _pullup2);

	// Activated Interrupt on INT0 || Interrupt an INT0
	GICR |= (1 << INT0);
	
	// Activated Interrupt on INT1 || Interrupt an INT1
	GICR |= (1 << INT1); 
	
	// Activated INT0 as falling edge Interrupt
	MCUCR |= (1 << ISC01); 
	
	// Activated INT1 as falling edge Interrupt
	MCUCR |= (1 << ISC11); 
}