/*
 * it.c
 *
 *  Created on: Jul 19, 2022
 *      Author: Nguyen Tran
 */
#include "main.h"

extern TIM_HandleTypeDef htimer10;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void TIM1_UP_TIM10_IRQHandler()
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_TIM_IRQHandler(&htimer10);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
}

