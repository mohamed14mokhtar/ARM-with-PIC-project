/*
 * lcd_cfg.c
 *
 *  Created on: Aug 6, 2024
 *      Author: mokhtar
 */


#include"lcd_cfg.h"

chr_lcd_4bit_type lcd_1 = {
		.lcd_en_port = GPIOC,
		.lcd_en_pin = GPIO_PIN_1,
		.lcd_rs_port = GPIOC,
		.lcd_rs_pin  = GPIO_PIN_0,
		.lcd_data_port[0] = GPIOC,
		.lcd_data_port[1] = GPIOC,
		.lcd_data_port[2] = GPIOC,
		.lcd_data_port[3] = GPIOC,
		.lcd_data_pin[0] = GPIO_PIN_2,
		.lcd_data_pin[1] = GPIO_PIN_3,
		.lcd_data_pin[2] = GPIO_PIN_4,
		.lcd_data_pin[3] = GPIO_PIN_5,

};
