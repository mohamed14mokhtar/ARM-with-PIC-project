/*
 * keypad.h
 *
 *  Created on: Aug 6, 2024
 *      Author: mokhtar
 */

#ifndef KEYPAD_KEYPAD_H_
#define KEYPAD_KEYPAD_H_

#include "stander_file.h"


#define KEYMAP_MATRIX_ROWS    4
#define KEYMAP_MATRIX_COLUMNS  4





typedef struct {
	GPIO_TypeDef *keypad_port_row[KEYMAP_MATRIX_ROWS];
    uint16_t     keypad_pin_row[KEYMAP_MATRIX_ROWS];
}keypad_row_type;

typedef struct {
	GPIO_TypeDef *keypad_port_colum[KEYMAP_MATRIX_COLUMNS];
    uint16_t     keypad_pin_colum[KEYMAP_MATRIX_COLUMNS];
}keypad_colum_type;


uint8_t keypad_get_value (const keypad_row_type *keypad_row,
		const keypad_colum_type *keypad_colum ,uint8_t *value);

#endif /* KEYPAD_KEYPAD_H_ */
