/*
 * bluetooth.c
 *
 *  Created on: Aug 17, 2024
 *      Author: mokhtar
 */


#include "bluetooth.h"

/**
  * @brief  Sends an amount of data in blocking mode.
  * @note   When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         the sent data is handled as a set of u16. In this case, Size must indicate the number
  *         of u16 provided through pData.
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (u8 or u16 data elements).
  * @param  Size  Amount of data elements (u8 or u16) to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAl_Bluetooth_Transimit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout){
	HAL_StatusTypeDef status = HAL_OK;
	if((NULL == huart) || (NULL == pData)){
		status = HAL_ERROR;
	}else{
		status = HAL_UART_Transmit(huart, pData ,Size,Timeout);
	}
	return status;
}
/**
  * @brief  Sends an amount of data in non blocking mode.
  * @note   When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M1-M0 = 01),
  *         the sent data is handled as a set of u16. In this case, Size must indicate the number
  *         of u16 provided through pData.
  * @param  huart Pointer to a UART_HandleTypeDef structure that contains
  *               the configuration information for the specified UART module.
  * @param  pData Pointer to data buffer (u8 or u16 data elements).
  * @param  Size  Amount of data elements (u8 or u16) to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef HAl_Bluetooth_Transimit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size){
		HAL_StatusTypeDef status = HAL_OK;
		if((NULL == huart) || (NULL == pData)){
			status = HAL_ERROR;
		}else{
			status = HAL_UART_Transmit_IT(huart, pData ,Size);
		}
		return status;
}

/**
  * @brief Receive an amount of data in blocking mode till either the expected number of data is received or an IDLE event occurs.
  * @note   HAL_OK is returned if reception is completed (expected number of data has been received)
  *         or if reception is stopped after IDLE event (less than the expected number of data has been received)
  *         In this case, RxLen output parameter indicates number of data available in reception buffer.
  * @note   When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M = 01),
  *         the received data is handled as a set of uint16_t. In this case, Size must indicate the number
  *         of uint16_t available through pData.
  * @param huart   UART handle.
  * @param pData   Pointer to data buffer (uint8_t or uint16_t data elements).
  * @param Size    Amount of data elements (uint8_t or uint16_t) to be received.
  * @param RxLen   Number of data elements finally received (could be lower than Size, in case reception ends on IDLE event)
  * @param Timeout Timeout duration expressed in ms (covers the whole reception sequence).
  * @retval HAL status
  */
HAL_StatusTypeDef HAl_Bluetooth_Recieve(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint16_t *RxLen,
                                           uint32_t Timeout){
			HAL_StatusTypeDef status = HAL_OK;
			if((NULL == huart) || (NULL == pData) || (NULL == RxLen)){
				status = HAL_ERROR;
			}else{
				status = HAL_UARTEx_ReceiveToIdle(huart, pData ,Size,RxLen,Timeout);
			}
			return status;
}

/**
  * @brief Receive an amount of data in interrupt mode till either the expected number of data is received or an IDLE event occurs.
  * @note   Reception is initiated by this function call. Further progress of reception is achieved thanks
  *         to UART interrupts raised by RXNE and IDLE events. Callback is called at end of reception indicating
  *         number of received data elements.
  * @note   When UART parity is not enabled (PCE = 0), and Word Length is configured to 9 bits (M = 01),
  *         the received data is handled as a set of uint16_t. In this case, Size must indicate the number
  *         of uint16_t available through pData.
  * @param huart UART handle.
  * @param pData Pointer to data buffer (uint8_t or uint16_t data elements).
  * @param Size  Amount of data elements (uint8_t or uint16_t) to be received.
  * @retval HAL status
  */
HAL_StatusTypeDef HAl_Bluetooth_Recieve_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size){
	HAL_StatusTypeDef status = HAL_OK;
				if((NULL == huart) || (NULL == pData) ){
					status = HAL_ERROR;
				}else{
					status = HAL_UARTEx_ReceiveToIdle_IT(huart, pData ,Size);
				}
				return status;
}
