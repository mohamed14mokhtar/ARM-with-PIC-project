/*
 * keypad.c
 *
 *  Created on: Aug 6, 2024
 *      Author: mokhtar
 */


#include "keypad.h"
static const uint8_t value_ret[KEYMAP_MATRIX_ROWS][KEYMAP_MATRIX_COLUMNS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};



uint8_t keypad_get_value (const keypad_row_type *keypad_row,const keypad_colum_type *keypad_colum ,uint8_t *value){
	uint8_t ret = E_OK;
	GPIO_PinState colum_logic=0;
	uint8_t l_row_counter =0 ,l_colum_counter=0 ,l_counter =0;
	   if ((NULL == keypad_row) || (NULL == value) || (NULL == keypad_colum)){
		   ret =E_NOT_OK;
	   }
	   else{
		   for(l_row_counter = 0; l_row_counter < KEYMAP_MATRIX_ROWS ;l_row_counter++){
			   for(l_counter = 0; l_counter < KEYMAP_MATRIX_ROWS ;l_counter++){
				   HAL_GPIO_WritePin(keypad_row->keypad_port_row[l_counter],keypad_row->keypad_pin_row[l_counter],GPIO_PIN_RESET);
			   }
			   HAL_GPIO_WritePin(keypad_row->keypad_port_row[l_row_counter],keypad_row->keypad_pin_row[l_row_counter],GPIO_PIN_SET);
			   HAL_Delay(10);
			   for(l_colum_counter = 0; l_colum_counter < KEYMAP_MATRIX_COLUMNS ;l_colum_counter++){
				   colum_logic = HAL_GPIO_ReadPin (keypad_colum->keypad_port_colum[l_colum_counter],keypad_colum->keypad_pin_colum[l_colum_counter]);
				               if(GPIO_PIN_SET == colum_logic){
				                   *value=value_ret[l_row_counter][l_colum_counter];
				                   //HAL_Delay(100);

				               }
			   }
		   }
	   }
	   return ret;
}

