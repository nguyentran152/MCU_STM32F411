/*
 * msp.c
 *
 *  Created on: Jul 14, 2022
 *      Author: Nguyen Tran
 */

#include "stm32f4xx_hal.h"


void HAL_MspInit(void)
{
	//Low level processor specific inits
	//1. Set up the priority grouping of the arm cortex Mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Enable the require system exceptions of the arm cortex Mx processor
	//system control block -> System handler control and state register
	SCB->SHCSR |= 0x7 << 16; //usage, bus, memory fault system exceptions

	//3. Configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	//1. Enable the clock for timer 10 peripheral
	__HAL_RCC_TIM10_CLK_ENABLE();

	//2. Enable the IRQ of timer 10
	HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

	//3. set up priority
	HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 15, 0);
}
