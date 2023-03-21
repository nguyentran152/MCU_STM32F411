/*
 * it.c
 *
 *  Created on: Jul 15, 2022
 *      Author: Nguyen Tran
 */
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htimer10;
extern TIM_HandleTypeDef htimer2;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM1_UP_TIM10_IRQHandler()
{
	HAL_TIM_IRQHandler(&htimer10);
}


void TIM2_IRQHandler()
{
	HAL_TIM_IRQHandler(&htimer2);
}


