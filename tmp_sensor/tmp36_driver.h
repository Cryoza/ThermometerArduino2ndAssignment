/*
 * tmp36_driver.h
 *
 * Created: 20/03/2022 18:14:54
 *  Author: mmate
 */ 


#ifndef TMP36_DRIVER_H_
#define TMP36_DRIVER_H_

void init_tmp();
void set_callback(void (*cb)(float));





#endif /* TMP36_DRIVER_H_ */