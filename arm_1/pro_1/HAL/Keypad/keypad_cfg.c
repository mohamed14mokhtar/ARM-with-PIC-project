/*
 * keypad_cfg.c
 *
 *  Created on: Aug 6, 2024
 *      Author: mokhtar
 */

#include"keypad_cfg.h"

keypad_row_type keypad_row_1 = {
		.keypad_port_row[0] = GPIOB,
		.keypad_port_row[1] = GPIOB,
		.keypad_port_row[2] = GPIOB,
		.keypad_port_row[3] = GPIOB,
		.keypad_pin_row[0] = GPIO_PIN_0,
		.keypad_pin_row[1] = GPIO_PIN_1,
		.keypad_pin_row[2] = GPIO_PIN_2,
		.keypad_pin_row[3] = GPIO_PIN_3
};

keypad_colum_type keypad_colum_1 = {
		 .keypad_port_colum[0] = GPIOB,
		 .keypad_port_colum[1] = GPIOB,
		 .keypad_port_colum[2] = GPIOB,
		 .keypad_port_colum[3] = GPIOB,
		 .keypad_pin_colum[0] = GPIO_PIN_4,
		 .keypad_pin_colum[1] = GPIO_PIN_5,
		 .keypad_pin_colum[2] = GPIO_PIN_6,
		 .keypad_pin_colum[3] = GPIO_PIN_7
};
