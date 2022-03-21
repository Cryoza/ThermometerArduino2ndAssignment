/*
 * tmp36_driver.c
 *
 * Created: 20/03/2022 18:15:29
 *  Author: mmate
 */ 
#include <avr/io.h>
#include "tmp36_driver.h"


//Think about using global variable
volatile float temp_reading;

ISR(ADC_vect) {

  temp_reading = ADCH * (5000/1024); //instead of 10 bit , you're using 8 bit
  //check the value.
}

void init_tmp() {
	//Disabling the power reduction ADC bit, PRADC
	//So that it is possible to use the ADC input MUX
	//Disabling Power Reduction of Timer/Counter1, bit PRTIM1
	PRR0 &= ~(_BV(PRADC) | _BV(PRTIM1)) ;
	//Setting the voltage reference (5V)
	ADMUX |= _BV(REFS0);
	//Adjust result to left - that will take the 8 MSB
	//to ADCH rather than to ADCL. As such precision is not needed.
	ADMUX |= _BV(ADLAR);
	//Disable digital input as it is enabled by default
	//it will not be used as input.
	DDRK &= ~(_BV(PK7));
	DIDR0 |= _BV(ADC0D);
	//Input Channel Selection ADC15 - 
	//Can read from multiple channels, in that case is just one
	ADMUX |= _BV(MUX1) | _BV(MUX2) | _BV(MUX0);
	ADMUX &= ~(_BV(MUX3) | _BV(MUX4));
	ADCSRB |= _BV(MUX5);
	//MUX5..0 -> 100111
	//Selecting ADC prescaler - Set out the frequency ADC clock
	ADCSRA |= _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
	//ADATE - Enable Auto Trigger
	//ADIE - Interrupt Enable
	ADCSRA |= _BV(ADATE) | _BV(ADIE);
	//Timer/Counter1 Compare Match B //Autro Trigger source selection (ADATE bit)
	ADCSRB |= _BV(ADTS2) | _BV(ADTS0);
	//ADEN - Turn on Analog Digital Converter
	ADCSRA |= _BV(ADEN);
	//ADSC - Starts the conversion of the input from ADC
	ADCSRA |= _BV(ADSC);
	//.Facial recognition setup
	OCR1B = 15625;
	//Selecting a clock source prescaler, in 
	//that case it is clk/1024, because 1 
	//second is tiny enough to use with 
	//this prescaler
	TCCR1A |= (_BV(COM1B1) | _BV(COM1B0));
	//Clock mode (CTC)
	TCCR1A |= _BV(WGM12);
	//Enable Timer Interrupt Mask
	TIMSK1 |= _BV(OCIE1B);
}





