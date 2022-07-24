/*
 * it.c
 *
 *  Created on: Jul 14, 2022
 *      Author: Nguyen Tran
 */
#include "stm32f4xx_hal.h"

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


