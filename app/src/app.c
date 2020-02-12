/*
 * app.c
 *
 *  Created on: Feb 12, 2020
 *      Author: user
 */

#include "app.h"

#include "cmsis_os.h"
#include "task.h"

#include "app_ui.h"
#include "app_uart.h"

// We need
// Task for UI
// Task UART receive
// Task for UART transmit
// Queue for UART receive
// Queue for UART transmit
// Mutex for UART

static app_context_t __appContext;

app_err_t APP_Init(void * uartHandle)
{

	app_context_t * appContext = APP_ContextGetForUpdate();
	APP_IF_RETURN(appContext == NULL, APP_ERR_NULL_REF);

	// Mutexes
	osMutexDef(uart_mutex);
	appContext->uartMutexId = osMutexCreate(osMutex(uart_mutex));

	// Queues
	osMailQDef(from_uart_pool_q, APP_FROM_UART_QUEUE_SIZE, APP_UART_QUEUE_TYPE);
	appContext->fromUartQueueId = osMailCreate(osMailQ(from_uart_pool_q), NULL);

	osMailQDef(to_uart_pool_q, APP_FROM_UART_QUEUE_SIZE, APP_UART_QUEUE_TYPE);
	appContext->toUartQueueId = osMailCreate(osMailQ(to_uart_pool_q), NULL);

	// Tasks
	osThreadDef(mainTask, APP_MainTask, APP_MAIN_THREAD_PRIO, 1, APP_MAIN_THREAD_STACK_SIZE);
	appContext->mainThreadId = osThreadCreate(osThread(mainTask), NULL);

	osThreadDef(uiTask, APP_UI_Task, APP_UI_THREAD_PRIO, 1, APP_UI_THREAD_STACK_SIZE);
	appContext->uiThreadId = osThreadCreate(osThread(uiTask), NULL);

	osThreadDef(uartRxTask, APP_UART_RxTask, APP_UART_RX_THREAD_PRIO, 1, APP_UART_RX_THREAD_STACK_SIZE);
	appContext->uartRxThreadId = osThreadCreate(osThread(uartRxTask), NULL);

	osThreadDef(uartTxTask, APP_UART_TxTask, APP_UART_TX_THREAD_PRIO, 1, APP_UART_TX_THREAD_STACK_SIZE);
	appContext->uartTxThreadId = osThreadCreate(osThread(uartTxTask), NULL);

}

const app_context_t * APP_ContextGet(void)
{
	return (const app_context_t *) &__appContext;
}

app_context_t * APP_ContextGetForUpdate(void)
{
	return &__appContext;
}

void APP_MainTask(const void * argument)
{
	for (;;)
	{
		osDelay(1000);
	}
}
