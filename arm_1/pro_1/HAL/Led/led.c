/*
 * led.c
 *
 *  Created on: Aug 6, 2024
 *      Author: mokhtar
 */

#include "led.h"

void led_turn_on(const led_type *led){
	if(NULL == led){

	}else{
		HAL_GPIO_WritePin((led->led_port), (led->led_pin), GPIO_PIN_SET);
	}
}
void led_turn_off(const led_type *led){
	if(NULL == led){

		}else{
			HAL_GPIO_WritePin((led->led_port), (led->led_pin), GPIO_PIN_RESET);
		}
}


void led_toggle(const led_type *led){
	if(NULL == led){

		}else{
			HAL_GPIO_TogglePin((led->led_port), (led->led_pin));
		}
}

