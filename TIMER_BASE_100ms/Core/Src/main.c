/*
 * main.c
 *
 *  Created on: Jul 14, 2022
 *      Author: Nguyen Tran
 */


#include "main.h"
#include <string.h>



void Error_Handler(void);
void TIMER10_Init(void);
void GPIO_Init(void);

TIM_HandleTypeDef htimer10;



int main()
{
	HAL_Init();
	GPIO_Init();
	TIMER10_Init();

	HAL_TIM_Base_Start(&htimer10);

	while(1)
	{
		/* Loop until the update event flag is set */
		while( ! (TIM10->SR & TIM_SR_UIF) );
		/* The required time delay has been elapsed */
		/* User code can be executed */
		TIM10->SR = 0; //clc
		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
	}

	return 0;
}



void GPIO_Init(void)
{
    __HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_12;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD,&ledgpio);
}

void TIMER10_Init(void)
{
	htimer10.Instance = TIM10;
	htimer10.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimer10.Init.Prescaler = 24;
	htimer10.Init.Period = 64000-1;

	if(HAL_TIM_Base_Init(&htimer10) != HAL_OK)
	{
		Error_Handler();
	}
}

void Error_Handler(void)
{
	while(1);
}

