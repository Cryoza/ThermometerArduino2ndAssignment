/*
 * ThermometerArduino.c
 *
 * Created: 20/03/2022 15:57:05
 * Author : mmate
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "leds/led_driver.h"
#include "tmp_sensor/tmp36_driver.h"

void set_led_bar(float temp) {
	//Substract the original starting temperature to make it easier, 
	//to pass the parameter for set_bar() function. 
	//18-25 / - 8 LEDS. 
	uint8_t bars_to_set = (uint8_t) temp - 18;
	set_bar(bars_to_set);
}

int main(void)
{
	init_leds();
	init_tmp();
	set_callback(set_led_bar);

	sei(); 
	
    while (1) 
    {
    }
}

