/*
 * ThermometerArduino.c
 *
 * Created: 20/03/2022 15:57:05
 * Author : mmate
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	init_tmp();
    /* Replace with your application code */
	DDRA = 0xff;
	PORTA = 0b11111111;
    while (1) 
    {
		PORTA = 0b00000000;
		_delay_ms(300);
		PORTA = 0b11111111;
		_delay_ms(300);
    }
}

