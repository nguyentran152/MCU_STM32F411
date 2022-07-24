/*
 * it.c
 *
 *  Created on: Jul 12, 2022
 *      Author: Nguyen Tran
 */
#include "main.h"


void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}



