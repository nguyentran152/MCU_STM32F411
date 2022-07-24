/*
 * main.c
 *
 *  Created on: Jul 12, 2022
 *      Author: Nguyen Tran
 */


/*
 * This program generate HSE systems clock source
 */

#include "main.h"
#include <string.h>
#include <stdio.h>


UART_HandleTypeDef huart2;


void UART2_Init(void);
void Error_Handler(void);



int main()
{
	RCC_OscInitTypeDef osc_inits;
	RCC_ClkInitTypeDef clk_inits;
	HAL_Init();
	UART2_Init();

	char msg[100];

	memset(&osc_inits, 0, sizeof(osc_inits));
	osc_inits.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_inits.HSEState = RCC_HSE_ON;
	if(HAL_RCC_OscConfig(&osc_inits) != HAL_OK)
	{
		Error_Handler();
	}

	clk_inits.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
							RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_inits.SYSCLKSource = RCC_SYSCLKSOURCE_HSE; //8MHz HSE
	clk_inits.AHBCLKDivider = RCC_SYSCLK_DIV2; // 4MHz AHB
	clk_inits.APB1CLKDivider = RCC_HCLK_DIV2; // 2MHz APB1
	clk_inits.APB2CLKDivider = RCC_HCLK_DIV2;// 2MHz APB2
	if(HAL_RCC_ClockConfig(&clk_inits, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}

	__HAL_RCC_HSI_DISABLE(); //disable HSI clock, change to HSE clock source

	//configure systick

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000); //hz
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	UART2_Init();

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "SYSCLK: %ldHz\r\n", HAL_RCC_GetSysClockFreq());
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "AHB: %ldHz\r\n", HAL_RCC_GetHCLKFreq());
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "APB1: %ldHz\r\n", HAL_RCC_GetPCLK1Freq());
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "APB2: %ldHz\r\n", HAL_RCC_GetPCLK2Freq());
	HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

	while(1);
	return 0;
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


void Error_Handler(void)
{
	while(1);
}


