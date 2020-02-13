/*
 * app.h
 *
 *  Created on: Feb 12, 2020
 *      Author: user
 */

#ifndef APP_INC_APP_H_
#define APP_INC_APP_H_

#include <stdint.h>

#include "cmsis_os.h"

typedef struct __app_context
{
	// hardware handles
	void * uartHandle;

	// mutex IDs
	osMutexId uartMutexId;

	// queue IDs
	osMailQId fromUartQueueId;
	osMailQId toUartQueueId;

	// thread IDs
	osThreadId mainThreadId;
	osThreadId uiThreadId;
	osThreadId uartRxThreadId;
	osThreadId uartTxThreadId;
} app_context_t;

typedef enum
{
	APP_ERR_OK,
	APP_ERR_PARAM,
	APP_ERR_NULL_REF,
	APP_ERR_OS
} app_err_t;

extern app_context_t globalAppContext;

#define APP_MAIN_THREAD_STACK_SIZE		128
#define APP_UI_THREAD_STACK_SIZE		128
#define APP_UART_RX_THREAD_STACK_SIZE	128
#define APP_UART_TX_THREAD_STACK_SIZE	128

#define APP_MAIN_THREAD_PRIO			osPriorityNormal
#define APP_UI_THREAD_PRIO				osPriorityNormal
#define APP_UART_RX_THREAD_PRIO			osPriorityNormal
#define APP_UART_TX_THREAD_PRIO			osPriorityNormal

#define APP_UART_QUEUE_TYPE				uint16_t
#define APP_FROM_UART_QUEUE_SIZE		(64)
#define APP_TO_UART_QUEUE_SIZE			(64)

#define APP_IF_RETURN(expr, ret)		if (expr) return ret

app_err_t APP_Init(void * uartHandle);
const app_context_t * APP_ContextGet(void);
app_context_t * APP_ContextGetForUpdate(void);
void APP_MainTask(const void * argument);

#endif /* APP_INC_APP_H_ */
