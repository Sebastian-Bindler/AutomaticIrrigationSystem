/*
 * AutomaticIrrigationSystem.c
 *
 * Created: 22.01.2021 21:46:11
 *  Author: Bindler, Sebastian
 */ 

//##################################################################################################################################################################################
	
#define PUMP PB0				// Digital output for pump											|| Digitaler Pumpen ausgang
#define PUMPPORT DDRB			// Port for pump 
#define PUMPPULLUP 1			// Internal pull-up resistors activate with 1 and disable with 0
#define PUMPTIME 100			// Pump runtime in milliseconds
#define PUMPDELAY 100			// Pump delay between attempts in milliseconds
#define PUMPATTEMPTS 2			// Maximum pump attempts
#define SOIL PB1				// Analog input for soil moisture									|| Analogeingang für Bodenfeuchtigkeit
#define SOILPORT DDRB			// Port for soil
#define SOILMINMOISTURE 523		// Limit for soil moisture 
#define DRN PD2					// Digital input for dry run protection as interrupt				|| Digitalereingang für Trockenlaufschutz (TGS)
#define DRNPORT DDRD			// Port for dry run protection
#define DRNPULLUP 1				// Internal pull-up resistors activate with 1 and disable with 0
#define MIN PB2					// Digital input for min float switch
#define MINPORT DDRB			// Port for min float switch
#define	MINPULLUP 1				// Internal pull-up resistors activate with 1 and disable with 0
#define MAX PB3					// Digital input for max float switch
#define MAXPORT DDRB			// Port for max float switch
#define MAXMAX PD3				// Digital input for maxmax float switch as interrupt
#define MAXMAXPORT DDRD			// Port for maxmax float switch
#define MAXMAXPULLUP 1			// Internal pull-up resistors activate with 1 and disable with 0
#define RESET PB4				// Digital input for reset button
#define RESETPORT DDRB			// Port for reset button
#define RESETPULLUP 1			// Internal pull-up resistors activate with 1 and disable with 0
#define FILLING PB5				// Digital output automatic filling									|| Digitalerausgang für Automatisches befüllen
#define FILLINGPORT DDRB		// Port for filling output
#define FILLINGPULLUP 1			// Internal pull-up resistors activate with 1 and disable with 0		
#define FILLINGTIME 100			// Filling time in milliseconds 
#define EMPTYLAMP PB6			// Digital output Lamp for empty canister							|| Digitalerausgang für die Lampe bei leeren Kanister 
#define EMPTYLAMPPORT DDRB		// Port for emptylamp output
#define EMPTYLAMPPULLUP 1		// Internal pull-up resistors activate with 1 and disable with 0
#define FILLEDLAMP PB7			// Digital output Lamp for filled canister							|| Digitalerausgang für die Lampe bei gefüllten Kanister
#define FILLEDLAMPPORT DDRC		// Port for filled lamp output
#define FILLEDLAMPPULLUP 1		// Internal pull-up resistors activate with 1 and disable with 0
#define ALARM PC0				// Digital output alarm												|| Digitalerausgang für den Alarm
#define ALARMPORT DDRC			// Port for alarm buzzer output
#define ALARMPULLUP 1			// Internal pull-up resistors activate with 1 and disable with 0

#define F_CPU 3686400UL // Set CPU clock for delay.h

//##################################################################################################################################################################################

// Iclude local librarys
#include "inc/analog.h" 
#include "inc/digital.h"
#include "inc/init.h"
#include "inc/functions.h"

// Include Standard librarys 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//##################################################################################################################################################################################

// Global variables
volatile uint8_t DRNflag; // Interrupt variable for dry run protection
volatile uint8_t MAXMAXflag; // Interrupt variable for maxmax float switch

//##################################################################################################################################################################################

// Main
int main(void)
{
	// Allow interrupts || Interrupts zulassen
	sei(); 
	// Initialize interrupt
	initInterrupt(DRNPORT, DRN, DRNPULLUP, MAXMAXPORT, MAXMAX, MAXMAXPULLUP); 
	// Initialize digital inputs
	initDigitalInput(DRNPORT, DRN, DRNPULLUP, MINPORT, MIN, MINPULLUP, MAXPORT, MAX, MAXPULLUP, MAXMAXPORT, MAXMAX, MAXMAXPULLUP, RESETPORT, RESET, RESETPULLUP);
	// Initialize digital outputs
	initDititalOuput(PUMPPORT,  PUMP,  PUMPPULLUP,  FILLINGPORT,  FILLING,  FILLINGPULLUP,  EMPTYLAMPPORT,  EMPTYLAMP,  EMPTYLAMPPULLUP,  FILLEDLAMPPORT,  FILLEDLAMP,  FILLEDLAMPPULLUP,  ALARMPORT,  ALARM,  ALARMPULLUP);
	// Initialize analog to digital converter
	initADC(SOIL);
	
	// initial check for level lamps
	checkLevel(MINPORT, MIN, EMPTYLAMPPORT,  EMPTYLAMP, FILLEDLAMPPORT,  FILLEDLAMP);
    while(1)
    {

// Interrupt function for dry run protection

		if (DRNflag == 1) // Interrupt function for dry run protection
		{
			// Forcing pump shutdown, turn alarm on and wait for reset
			reset(PUMPPORT, PUMP, ALARMPORT, ALARM, FILLEDLAMPPORT, FILLEDLAMP, EMPTYLAMPPORT, EMPTYLAMP, RESETPORT, RESET); 
			// Filling empty canister
			filling(PUMPPORT, PUMP, ALARMPORT, ALARM, FILLEDLAMPPORT, FILLEDLAMP, EMPTYLAMPPORT, EMPTYLAMP, RESETPORT, RESET, FILLINGPORT, FILLING, FILLINGTIME, MAXPORT, MAX, MAXMAXPORT, MAXMAX); 
			// Set interrupt variable back to 0
			DRNflag = 0; 
		}
		
// Interrupt function for maxmax alarm
		
		if (MAXflag == 1) // Interrupt function for max alarm
		{
			// Start maxmax alarm function
			maxAlarm(PUMPPORT, PUMP, ALARMPORT, ALARM, FILLEDLAMPPORT, FILLEDLAMP, EMPTYLAMPPORT, EMPTYLAMPPORT, RESETPORT, RESET, MAXMAXPORT, MAXMAX); 
			// Set interrupt variable to 0
			MAXMAXflag = 0; 
		}
		
// 	Verify there's no interruption active
	if (DRNflag == 0 && MAXflag == 0) // It's a interrupt is active?
		{
		
// Check empty canister and start filling

			if (checkPin(MINPORT, MIN) == 0) // Checking the water level in canister 
			{
				// Filling empty canister
				filling(PUMPPORT, PUMP, ALARMPORT, ALARM, FILLEDLAMPPORT, FILLEDLAMP, EMPTYLAMPPORT, EMPTYLAMP, RESETPORT, RESET, FILLINGPORT, FILLING, FILLINGTIME, MAXPORT, MAX, MAXMAXPORT, MAXMAX); 
			}
			

// Automatic Irrigation		
			if (readADC(SOIL) < SOILMINMOISTURE) // Check soil moisture
			{
				uint8_t attempts = 0; // Variable for attempt counter
				
				while (readADC(SOIL) > SOILMINMOISTURE) // Start pump for irrigation
				{
					// Toggle pump for PUMPTIME milliseconds
					toggleDigitalByTime(PUMPPORT, PUMP, PUMPTIME); 
					attempts++; // Add 1 for successfully execution
					_delay_ms(PUMPDELAY); // Wait PUMPDELAY milliseconds
					
					if (attempts >= PUMPATTEMPTS) // Check if attempts over or even PUMPATTEMPTS
					{
						// Forcing pump shutdown, turn alarm on and wait for reset
						reset(PUMPPORT, PUMP, ALARMPORT, ALARM, FILLEDLAMPPORT, FILLEDLAMP, EMPTYLAMPPORT, EMPTYLAMP, RESETPORT, RESET);
					}
				}
			}
				}	
}
	}

//##################################################################################################################################################################################

// External Interrupt Request 0 for dry run protection
ISR(INT0_vect){
	
	PUMPPORT &= ~(1 << PUMP); // Forcing pump shutdown
	DRNflag = 1; // Set interrupt variable to 1 for interrupt function at main
}

// External Interrupt Request 1 for maxmax alarm
ISR(INT1_vect){
	
	PUMPPORT &= ~(1 << PUMP); // Forcing pump shutdown
	MAXMAXflag = 1; // Set interrupt variable to 1 for interrupt function at main
}

//##################################################################################################################################################################################










