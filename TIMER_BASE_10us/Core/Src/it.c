/*
 * it.c
 *
 *  Created on: Jul 14, 2022
 *      Author: Nguyen Tran
 */
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htimer10;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM1_UP_TIM10_IRQHandler()
{
	HAL_TIM_IRQHandler(&htimer10);
}
