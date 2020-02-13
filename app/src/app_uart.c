/*
 * app_uart.c
 *
 *  Created on: Feb 12, 2020
 *      Author: user
 */
#include "app_uart.h"

#include "cmsis_os.h"

#include "app.h"
#include "main.h"

static uint16_t __uartReceiveVal = 0;

void APP_UART_RxTask(const void * argument)
{
	// TODO check error
	HAL_UART_Receive_IT(globalAppContext.uartHandle, &__uartReceiveVal, (uint16_t) 1);

	osEvent rtosEvent;
	uint16_t * received = NULL;
	for (;;)
	{
		// TODO check error
		rtosEvent = osMailGet(globalAppContext.fromUartQueueId, osWaitForever);

		received = (uint16_t *) rtosEvent.value.p;
		if (received != NULL)
		{
			// TODO action with data
			// TODO at this time we just send data in loopback mode
			// TODO check error
			HAL_UART_Transmit_IT(globalAppContext.uartHandle, received, 1);

			// Free queue
			osMailFree(globalAppContext.fromUartQueueId, received);
		}
	}
}

void APP_UART_TxTask(const void * argument)
{
	for (;;)
	{
		osDelay(1000);
	}
}

/**
  * @brief Tx Transfer completed callback.
  * @param huart UART handle.
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_TxCpltCallback can be implemented in the user file.
   */
}

/**
  * @brief  Tx Half Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart)
{
  UNUSED(huart);
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart == globalAppContext.uartHandle)
	{
		// TODO check error
		osMailPut(globalAppContext.fromUartQueueId, &__uartReceiveVal);
		// TODO check error
		HAL_UART_Receive_IT(globalAppContext.uartHandle, &__uartReceiveVal, (uint16_t) 1);
	}
}

/**
  * @brief  Rx Half Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
  UNUSED(huart);
}

/**
  * @brief  UART error callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  UNUSED(huart);
}

/**
  * @brief  UART Abort Complete callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart)
{
  UNUSED(huart);
}

/**
  * @brief  UART Abort Complete callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_AbortTransmitCpltCallback(UART_HandleTypeDef *huart)
{
  UNUSED(huart);
}

/**
  * @brief  UART Abort Receive Complete callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart)
{
  UNUSED(huart);
}
