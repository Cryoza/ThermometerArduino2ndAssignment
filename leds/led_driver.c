/*
 * led_driver.c
 *
 * Created: 25/02/2022 08:39:41
 *  Author: Matey
 */
#include <avr/io.h>
#include "led_driver.h"

void init_leds() {
	DDRA = 0xff; //Set data register A to output
	PORTA = 0xff; //set all bits in Port A to 255
}

int set_led(uint8_t led_no, uint8_t state) {
	if (state < 0 || state > 1 || led_no < 1 || led_no > 8) {
		return -1;
	}
	else {
		uint8_t val = led_no - 1;
		if (state == 0) { //To turn off LED's
			PORTA |= (_BV(val));
		}
		else {
			PORTA &= ~(_BV(val)); //To turn on LED's
		}
		return 0;
	}
}