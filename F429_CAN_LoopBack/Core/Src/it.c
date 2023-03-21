/*
 * it.c
 *
 *  Created on: Mar 21, 2023
 *      Author: Nguyen Tran
 */

#include "main.h"


void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

