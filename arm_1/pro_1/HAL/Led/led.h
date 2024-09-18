/*
 * led.h
 *
 *  Created on: Aug 6, 2024
 *      Author: mokhtar
 */

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_

#include "stander_file.h"


typedef struct {
	GPIO_TypeDef *led_port;
	uint16_t led_pin;
}led_type;

extern void led_turn_on(const led_type *led);
extern void led_turn_off(const led_type *led);
extern void led_toggle(const led_type *led);

#endif /* HAL_LED_LED_H_ */
