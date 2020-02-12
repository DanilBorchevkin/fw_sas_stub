/*
 * app_uart.c
 *
 *  Created on: Feb 12, 2020
 *      Author: user
 */
#include "app_uart.h"

#include "cmsis_os.h"

void APP_UART_RxTask(const void * argument)
{
	for (;;)
	{
		osDelay(1000);
	}
}

void APP_UART_TxTask(const void * argument)
{
	for (;;)
	{
		osDelay(1000);
	}
}
