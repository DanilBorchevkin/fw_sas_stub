/*
 * app_ui.c
 *
 *  Created on: Feb 12, 2020
 *      Author: user
 */
#include "app_ui.h"

#include "cmsis_os.h"

void APP_UI_Task(const void * argument)
{
	for (;;)
	{
		osDelay(1000);
	}
}
