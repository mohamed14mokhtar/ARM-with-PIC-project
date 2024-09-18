/*
 * I2c_slave.c
 *
 *  Created on: Sep 1, 2024
 *      Author: mokhtar
 */

//#include "main.h"
//#include "I2c_slave.h"


/*at main function
 *  if(HAL_I2C_EnableListen_IT(&hi2c1) != HAL_OK){
	  Error_Handler();
  }
  */
//extern I2C_HandleTypeDef hi2c1;
//uint8_t data_receive ;
//uint8_t counter ;
//void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c){
//	HAL_I2C_EnableListen_IT(&hi2c1);
//}

//void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode){
//	if(TransferDirection == I2C_DIRECTION_TRANSMIT){
//		HAL_I2C_Slave_Seq_Receive_IT(&hi2c1,&data_receive,1,I2C_FIRST_AND_LAST_FRAME);
//	}else{
//		Error_Handler();
//	}
//}

//void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){
//	counter++;
//}

//void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c){
//	HAL_I2C_EnableListen_IT(&hi2c1);
//}
