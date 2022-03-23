/*
 * tmp36_driver.c
 *
 * Created: 20/03/2022 18:15:29
 *  Author: mmate
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "tmp36_driver.h"


static void (*call_back)(float);

void set_callback(void (*cb)(float)) {
	//Setting the callback.
	call_back = cb;
}


ISR(ADC_vect) {
  uint16_t t_read = ADCH;
  //t_read |= (ADCH << 8);
  //t_read >>= 6;
  //t_read <<= 2; //Shifting two symbols to the left, adding zeros. Getting 
  //10 bit value used to calculate actual degrees below.
  double voltage = t_read * (5.0 / 1023.0);
  double temp_in_c = (voltage - 0.5) * 100.0;
  call_back(temp_in_c);
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
	// ADCSRB |= _BV(ADSC);
	//.Facial recognition setup
	OCR1A = 15625;
	OCR1B = 10;
	//Selecting a clock source prescaler, in 
	//that case it is clk/1024, because 1 
	//second is tiny enough to use with 
	//this prescaler
	TCCR1B |= _BV(CS12) | _BV(CS10);
	TCCR1B |= _BV(WGM12); // CTC
	//Enable Timer Interrupt Mask
	TIMSK1 |= _BV(OCIE1B);
}

// clear the interrupt flag in the registry
EMPTY_INTERRUPT(TIMER1_COMPB_vect);