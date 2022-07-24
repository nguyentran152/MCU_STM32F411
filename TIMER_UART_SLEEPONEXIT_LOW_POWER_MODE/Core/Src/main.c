 /*
 * main.c
 *
 *  Created on: Jul 19, 2022
 *      Author: Nguyen Tran
 */


#include "main.h"
#include <string.h>



void Error_Handler(void);
void TIMER10_Init(void);
void GPIO_Init(void);
void UART2_Init(void);


TIM_HandleTypeDef htimer10;
UART_HandleTypeDef huart2;
extern uint8_t somedata[];


int main()
{
	HAL_Init();
	GPIO_Init();
	UART2_Init();
	TIMER10_Init();


	//enable sleep on exit
	SCB->SCR |= (1 << 1);

	TIM10->SR = 0; //clc
	HAL_TIM_Base_Start_IT(&htimer10);


	while(1);
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

void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if(HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(HAL_UART_Transmit(&huart2, (uint8_t*)somedata, (uint16_t)strlen((char*)somedata), HAL_MAX_DELAY) != HAL_OK)
	{
		Error_Handler();
	}
}

void Error_Handler(void)
{
	while(1);
}

