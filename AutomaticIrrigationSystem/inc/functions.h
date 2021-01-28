/*
 * functions.h
 *
 * Created: 23.01.2021 01:34:47
 *  Author: Bindler, Sebastian
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

// Error function declaration 
void error(uint8_t _pumpport, uint8_t _pump, uint8_t _alarmport, uint8_t _alarm, uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin);

// Filling function declaration 
void filling(uint8_t _pumpport, uint8_t _pump, uint8_t _alarmport, uint8_t _alarm, uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin, uint8_t _resetport, uint8_t _reset, uint8_t _fillingport, uint8_t _filling, uint8_t _fillingtime, uint8_t _maxport, uint8_t _maxpin, uint8_t _maxmaxport, uint8_t _pinmaxmax);

// Reset function declaration 
void reset(uint8_t _pumpport, uint8_t _pump, uint8_t _alarmport, uint8_t _alarm, uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin, uint8_t _resetport, uint8_t _reset);

// Alarm function declaration 
void alarm(uint8_t _port, uint8_t _pin);

// Lamperror function declaration 
void lampsError(uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin);

// Lampok function declaration 
void lampsOk(uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin);

// Max alarm function declaration 
void maxAlarm(uint8_t _pumpport, uint8_t _pump, uint8_t _alarmport, uint8_t _alarm, uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin, uint8_t _resetport, uint8_t _reset, uint8_t _maxmaxport, uint8_t _pinmaxmax);

// Toggle by time function declaration 
void toggleDigitalByTime(uint8_t _port, uint8_t _pin, uint8_t _time);

// Check level declaration 
void checkLevel(uint8_t _minport, uint8_t _minpin, uint8_t _lampokport, uint8_t _lampokpin, uint8_t _lamperrorport, uint8_t _lamperrorpin);

#endif /* FUNCTIONS_H_ */