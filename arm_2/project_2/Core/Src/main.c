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
#include "string.h"
#include "lcd_cfg.h"
#include "keypad_cfg.h"
#include "led_cfg.h"
#include "servo_cfg.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t keypad_value = 0 ;                 //reed value from keypad
StdReturnType ret = E_OK;                  //return status
uint32_t adc_value;                        //for debug
char mes[50];                              //convert uint to string
uint8_t password_value[4] = {0,0,0,0};     //password from keypad
uint8_t spi_receive[2] ;                   //spi data receive
uint8_t conter_spi = 1 ;                   //spi counter helper
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
  /* Prevent unused argument(s) compilation warning */
	HAL_SPI_Receive_IT(&hspi1,&spi_receive[0],1);
	//conter_spi++;
	//if(conter_spi == 2){
	//	conter_spi = 0;
	//}
  UNUSED(hspi);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_SPI_RxCpltCallback should be implemented in the user file
   */
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  uint8_t counter = 0 ; //counter for password
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  HAL_SPI_Receive_IT(&hspi1,&spi_receive[0],1);

   ret = lcd_4bit_intialize(&lcd1);
   lcd_4bit_send_string_pos(&lcd1,1,2,"welcome");
   lcd_4bit_send_string_pos(&lcd1,2,2,"password :");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  /*motor close door*/
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	  servo_Motor_Start_angle_0(&servo);
	  /* take value from keypad*/
	  ret =  keypad_get_value(&keypad_row_1,&keypad_colum_1,&keypad_value);
	  /* chick for four password number*/
	  if(keypad_value){
		  lcd_4bit_send_string_pos(&lcd1,2,(12 + counter),"*");
		  password_value[counter] = keypad_value;
		  counter++;
		  keypad_value = 0;
	  }
	  if(password_value[3] != 0){
		  if((password_value[0] == '1') && (password_value[1] == '1') &&
		     (password_value[2] == '1') && (password_value[3] == '1') ){
			  lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
			  lcd_4bit_send_string_pos(&lcd1,1,1,"password correct");
			  HAL_Delay(20);
			  /* Application */
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
			  servo_Motor_Start_angle_90(&servo);  //door open
			  while (1){
				  ret =  keypad_get_value(&keypad_row_1,&keypad_colum_1,&keypad_value);
				  if(keypad_value == 'A'){
					  lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
					  lcd_4bit_send_string_pos(&lcd1,1,2,"Bye-Bye!");
					  HAL_Delay(30);
					  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
					  servo_Motor_Start_angle_0(&servo);  //door closed
					  break;
				  }

				  	  while(spi_receive[0] >= 40){
				  		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
				  		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
				  		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
				  		  HAL_Delay(60);
				  	  }
			  }

		  }else{
			  lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
			  lcd_4bit_send_string_pos(&lcd1,1,2,"password wrong:");
		  }
		  for (uint8_t i =0 ; i< sizeof(password_value) ; i++){
			  password_value[i] = 0 ;
		  }
		  lcd_4bit_send_command(&lcd1, _LCD_CLEAR);
		  lcd_4bit_send_string_pos(&lcd1,1,2,"welcome");
		  lcd_4bit_send_string_pos(&lcd1,2,2,"password :");
		  counter = 0;
	  }

	  while(spi_receive[0] >= 40){
		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
		  HAL_Delay(60);
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
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
