/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "stander_file.h"
#include "keypad_cfg.h"
#include "lcd_cfg.h"
#include "led_cfg.h"
#include "bluetooth_cfg.h"
#include "servo_cfg.h"
#include "ultrasonic_cfg.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

#define TRIG_PIN GPIO_PIN_10
#define TRIG_PORT GPIOA

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
HAL_StatusTypeDef ret;                // return status
uint32_t IC_Val1 ;                    // for ultasonic read
uint32_t IC_Val2 ;                    // for ultasonic read
uint32_t Difference ;                 // different between val1 and val2
uint8_t Is_First_Captured ;           // is the first value captured ?
uint8_t Distance ;                    // distance from ultrasonic
uint8_t data_receive_uart2[2];        // receive data from pic
uint8_t data_receive_uart2_buffer[2]; // receive data from pic
volatile uint8_t data_receive_uart1;  // receive data from pic
uint8_t counter_recieve = 1;          //helper at data receive

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* callback for ultrasonic */
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

/* UART receive interrupt */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart1){
		HAL_UART_Receive_IT(&huart1,&data_receive_uart1,1);
	}else if(huart == &huart2){
		HAL_UART_Receive_IT(&huart2,&data_receive_uart2[counter_recieve],1);
		counter_recieve++;
		if(counter_recieve == 2){
			counter_recieve = 0;
		}
	}

}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	char MSG[40];
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();
  MX_TIM2_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);                  //start timer for ultasonic
  HAL_UART_Receive_IT(&huart1,&data_receive_uart1,1);          //receive data Bluetooth
  HAL_UART_Receive_IT(&huart2,&data_receive_uart2[0],1);       //receive data from pic

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /* send data with SPI */
	  HAL_SPI_Transmit(&hspi1,&data_receive_uart2[1],1,HAL_MAX_DELAY);
	  /* read ultrasonic data*/
	  HCSR04_Read(&ultra_1);
	  if(Distance >= 35){
		  servo_Motor_Start_angle_90(&servo);
	  }else if((Distance >= 31) && Distance < 35){
		  servo_Motor_Start_angle_45(&servo);
	  }else if((Distance >= 28) && Distance < 31){
		  servo_Motor_Start_angle_0(&servo);
	  }else if((Distance >= 24) && Distance < 28){
		  servo_Motor_Start_angle_N45(&servo);
	  }else if((Distance >= 20) && Distance < 24){
		  servo_Motor_Start_angle_N90(&servo);
	  }else{
		  servo_Motor_Start_angle_90(&servo);
	  }


	  /* for debug */
	  sprintf(MSG, "data1 = %d \r\n",data_receive_uart2[0]);
	  HAL_UART_Transmit(&huart6, MSG,strlen(MSG), 1000);
	  sprintf(MSG, "data2 = %d \r\n",data_receive_uart2[1]);
	  HAL_UART_Transmit(&huart6, MSG,strlen(MSG), 1000);

	  /* sun value */
	  if(data_receive_uart2[0] > 38 ){
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13,GPIO_PIN_RESET);
	      }else{
	    	  /* bluetooth receive data and operation */
	    	  switch(data_receive_uart1){
	    	  	  	  case 'a':
	    	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	    	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	    	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	    	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	    	  	  		  break;
	    	  	  	  case 's':
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	    	  	  	  		  break;
	    	  	  	  case 'd':
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	    	  	  	  		  break;
	    	  	  	  case 'f':
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	    	  	  	  		  break;
	    	  	  	  case 'g':
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
	    	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	    	  	  	  		  break;
	    	  	  	  case 'h':
	    	  	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	    	  	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	    	  	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	    	  	  	  	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	    	  	  	  	  		  break;
	    	  	  	  default :
	    	  	  		  break;
	    	  	  	  }
	    	  /* ultrasonic distance */
	    	  if(Distance >= 35){
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	    	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	    	  	  }else if((Distance >= 31) && Distance < 35){
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	    	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	    	  	  }else if((Distance >= 28) && Distance < 31){
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	    	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	    	  	  }else if((Distance >= 24) && Distance < 28){
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
	    	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	    	  	  }else if((Distance >= 20) && Distance < 24){
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	    	  	  }else{
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
	    	  		  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	    	  	  }
	      }

	  while(data_receive_uart2[1] >= 40){
		  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_0);
		  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
		  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_2);
		  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
		  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
		  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_1);
		  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
		  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_3);
		  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		  HAL_Delay(60);
		  /* send data with SPI */
		  HAL_SPI_Transmit(&hspi1,&data_receive_uart2[1],1,HAL_MAX_DELAY);
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
