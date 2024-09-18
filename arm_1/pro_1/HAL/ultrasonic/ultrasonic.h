/*
 * ultrasonic.h
 *
 *  Created on: Sep 11, 2024
 *      Author: mokhtar
 */

#ifndef ULTRASONIC_ULTRASONIC_H_
#define ULTRASONIC_ULTRASONIC_H_

#include "tim.h"
#include "usart.h"
#include "stander_file.h"



//defgroup TIM_Interrupt_definition TIM interrupt Definition
typedef enum {
	cc1 = TIM_IT_CC1,
	cc2 = TIM_IT_CC2,
	cc3 = TIM_IT_CC3,
	cc4 = TIM_IT_CC4
}TIM_IT_CC2_Select;

//ECHO pin >>> input pin (input capture pin)
typedef struct {
	GPIO_TypeDef *trigger_port;
	uint16_t trigger_pin;        //output pin

	TIM_HandleTypeDef *htim;     //timer use
	TIM_IT_CC2_Select cc_select ;
}ultra_pins_t;


void usDelay(uint32_t uSec);
void HCSR04_Read (ultra_pins_t *ultra_pins);

//void usDelay(uint32_t uSec);

#endif /* ULTRASONIC_ULTRASONIC_H_ */


/* call bacj function that calculate the distance */
/*

uint32_t IC_Val1 ;
uint32_t IC_Val2 ;
uint32_t Difference ;
uint8_t Is_First_Captured ;  // is the first value captured ?
uint8_t Distance ;


 void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)  // if the interrupt source is channel1
    {
        if (Is_First_Captured == 0) // if the first value is not captured
        {
            IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2); // read the first value
            Is_First_Captured = 1;  // set the first captured as true
            // Now change the polarity to falling edge
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);
        }

        else if (Is_First_Captured==1)   // if the first is already captured
        {
            IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);  // read second value
            __HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter

            if (IC_Val2 > IC_Val1)
            {
                Difference = IC_Val2-IC_Val1;
            }

            else if (IC_Val1 > IC_Val2)
            {
                Difference = (0xffff - IC_Val1) + IC_Val2;
            }

            Distance = Difference * (0.034/2);
            Is_First_Captured = 0; // set it back to false

            // set polarity to rising edge
            __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
            __HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC2);
        }
    }
}

 */


// execute
/*
 * at main
 * HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);
 *
 *  at while
     HCSR04_Read(&ultra_1);

	  sprintf(MSG,"Distance : %d cm\n\r",Distance);
	  HAL_UART_Transmit(&huart1,(uint8_t*)MSG, strlen(MSG),100);
	  HAL_Delay(500);*/
