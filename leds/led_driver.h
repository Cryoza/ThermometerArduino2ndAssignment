/*
 * led_driver.h
 *
 * Created: 25/02/2022 08:39:27
 *  Author: mmate
 */


#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

void init_leds();
int set_led(uint8_t led_no, uint8_t state); //led_no 1-8, state 0--1




#endif /* LED_DRIVER_H_ */