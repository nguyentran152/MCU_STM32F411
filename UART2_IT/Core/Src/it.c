/*
 * it.c
 *
 *  Created on: Jul 11, 2022
 *      Author: Nguyen Tran
 */
#include "main.h"

extern UART_HandleTypeDef huart2;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void USART2_IRQHandler()
{
	HAL_UART_IRQHandler(&huart2);
}


