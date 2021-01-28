/*
 * init.h
 *
 * Created: 22.01.2021 21:50:17
 *  Author: Bindler, Sebastian
 */ 
#include <avr/io.h>

#ifndef INIT_H_
#define INIT_H_

// Initialize digital output function declaration || Pin als Ausgang definieren
void initPortPinOutput(uint8_t _port, uint8_t _pin, uint8_t _pullup);

// Initialize digital input function declaration || Pin als Eingang definieren
void initPortPinInput(uint8_t _port, uint8_t _pin, uint8_t _pullup);

// Initialize pullup resistor function declaration || Pin Pullup Widerstand aktivieren
void initPullUpR(uint8_t _port, uint8_t _pin);

// Initialize digital inputs function declaration
void initDigitalInput(uint8_t _portDRN, uint8_t _pinDRN, uint8_t _pullupDRN, uint8_t _portMIN, uint8_t _pinMIN, uint8_t _pullupMIN, uint8_t _portMAX, uint8_t _pinMAX, uint8_t _pullupMAX, uint8_t _portMAXMAX, uint8_t _pinMAXMAX, uint8_t _pullupMAXMAX uint8_t _portRESET, uint8_t _pinRESET, uint8_t _pullupRESET);

// Initialize digital outputs function declaration
void initDititalOuput(uint8_t _portPUMP, uint8_t _pinPUMP, uint8_t _pullupPUMP, uint8_t _portFILLING, uint8_t _pinFILLING, uint8_t _pullupFILLING, uint8_t _portEMPTYLAMP, uint8_t _pinEMPTYLAMP, uint8_t _pullupEMPTYLAMP, uint8_t _portFILLEDLAMP, uint8_t _pinFILLEDLAMP, uint8_t _pullupFILLEDLAMP, uint8_t _portALARM, uint8_t _pinALARM, uint8_t _pullupALARM);

// Initialize analog to digital converter function declaration
void initADC(uint8_t _pin);

// Initialize interrupt function declaration
void initInterrupt(uint8_t _port, uint8_t _pin, uint8_t _pullup, uint8_t _port2, uint8_t _pin2, uint8_t _pullup2);

#endif /* INIT_H_ */ 