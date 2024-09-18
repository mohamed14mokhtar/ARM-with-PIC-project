/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RS_Pin GPIO_PIN_0
#define RS_GPIO_Port GPIOC
#define EN_Pin GPIO_PIN_1
#define EN_GPIO_Port GPIOC
#define D0_Pin GPIO_PIN_2
#define D0_GPIO_Port GPIOC
#define D1_Pin GPIO_PIN_3
#define D1_GPIO_Port GPIOC
#define D2_Pin GPIO_PIN_4
#define D2_GPIO_Port GPIOC
#define D3_Pin GPIO_PIN_5
#define D3_GPIO_Port GPIOC
#define row1_Pin GPIO_PIN_0
#define row1_GPIO_Port GPIOB
#define row2_Pin GPIO_PIN_1
#define row2_GPIO_Port GPIOB
#define row3_Pin GPIO_PIN_2
#define row3_GPIO_Port GPIOB
#define D6_Pin GPIO_PIN_8
#define D6_GPIO_Port GPIOC
#define D7_Pin GPIO_PIN_9
#define D7_GPIO_Port GPIOC
#define row3B3_Pin GPIO_PIN_3
#define row3B3_GPIO_Port GPIOB
#define colum1_Pin GPIO_PIN_4
#define colum1_GPIO_Port GPIOB
#define colum2_Pin GPIO_PIN_5
#define colum2_GPIO_Port GPIOB
#define colum3_Pin GPIO_PIN_6
#define colum3_GPIO_Port GPIOB
#define colum4_Pin GPIO_PIN_7
#define colum4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
