/*
 * ultrasonic.c
 *
 *  Created on: Sep 11, 2024
 *      Author: mokhtar
 */

#include "ultrasonic.h"





void HCSR04_Read (ultra_pins_t *ultra_pins)
{
    HAL_GPIO_WritePin(ultra_pins->trigger_port, ultra_pins->trigger_pin, GPIO_PIN_SET);  // pull the TRIG pin HIGH
    HAL_Delay(1);  // wait for 10 us
    HAL_GPIO_WritePin(ultra_pins->trigger_port, ultra_pins->trigger_pin, GPIO_PIN_RESET);  // pull the TRIG pin low

    __HAL_TIM_ENABLE_IT(ultra_pins->htim, ultra_pins->cc_select);
}







void usDelay(uint32_t uSec)
{
	if(uSec < 2) uSec = 2;
	TIM4->ARR = uSec - 1; 	//sets the value in the auto-reload register/
	TIM4->EGR = 1; 			//Re-initialises the timer/
	TIM4->SR &= ~1; 		//Resets the flag
	TIM4->CR1 |= 1; 		//Enables the counter
	while((TIM4->SR&0x0001) != 1);
	TIM4->SR &= ~(0x0001);
}


