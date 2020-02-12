/*
 * app_uart.h
 *
 *  Created on: Feb 12, 2020
 *      Author: user
 */

#ifndef APP_INC_APP_UART_H_
#define APP_INC_APP_UART_H_

void APP_UART_RxTask(const void * argument);
void APP_UART_TxTask(const void * argument);

#endif /* APP_INC_APP_UART_H_ */
