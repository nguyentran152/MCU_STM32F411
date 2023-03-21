/*
 * main.c
 *
 *  Created on: Jul 13, 2022
 *      Author: Nguyen Tran
 */


/*
 * This program generate PPL systems clock source using OscillatorType HSI
 */

#include "main.h"
#include <string.h>
#include <stdio.h>


UART_HandleTypeDef huart2;


void UART2_Init(void);
void Error_Handler(void);
void SystemClockConfig(uint8_t clock_freq);


int main()
{
	char msg[100];
	HAL_Init();

	SystemClockConfig(SYSCLK_CONF_FREQ_50MHz);
//	SystemClockConfig(SYSCLK_CONF_FREQ_80MHz);
//	SystemClockConfig(SYSCLK_CONF_FREQ_100MHz);

	UART2_Init();

	memset(msg, 0, sizeof(msg));
	sprintf(msg, "PLL_SYSCLK: %ldHz\r\n", HAL_RCC_GetSysClockFreq());
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



void SystemClockConfig(uint8_t clock_freq)
{
	RCC_OscInitTypeDef osc_inits;
	RCC_ClkInitTypeDef clk_inits;

	uint32_t FLatency = 0;

	osc_inits.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_inits.HSIState = RCC_HSI_ON;
	osc_inits.HSICalibrationValue = 16; //default
	osc_inits.PLL.PLLState = RCC_PLL_ON;
	osc_inits.PLL.PLLSource = RCC_PLLSOURCE_HSI;


	switch(clock_freq)
	{
		case SYSCLK_CONF_FREQ_50MHz:
		{
			osc_inits.PLL.PLLM = 16;
			osc_inits.PLL.PLLN = 100;
			osc_inits.PLL.PLLP = 2;
			osc_inits.PLL.PLLQ = 8;

			clk_inits.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
									RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_inits.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; //50MHz
			clk_inits.AHBCLKDivider = RCC_SYSCLK_DIV1; // 50MHz AHB
			clk_inits.APB1CLKDivider = RCC_HCLK_DIV2; // 25MHz APB1
			clk_inits.APB2CLKDivider = RCC_HCLK_DIV2;// 25MHz APB2

			FLatency = FLASH_LATENCY_1;

			break;
		}
		case SYSCLK_CONF_FREQ_80MHz:
		{
			osc_inits.PLL.PLLM = 16;
			osc_inits.PLL.PLLN = 160;
			osc_inits.PLL.PLLP = 2;
			osc_inits.PLL.PLLQ = 8;

			clk_inits.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
									RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_inits.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; //80MHz
			clk_inits.AHBCLKDivider = RCC_SYSCLK_DIV1; // 80MHz AHB
			clk_inits.APB1CLKDivider = RCC_HCLK_DIV2; // 40MHz APB1
			clk_inits.APB2CLKDivider = RCC_HCLK_DIV2;// 40MHz APB2

			FLatency = FLASH_LATENCY_2;

			break;
		}
		case SYSCLK_CONF_FREQ_100MHz:
		{
			osc_inits.PLL.PLLM = 16;
			osc_inits.PLL.PLLN = 200;
			osc_inits.PLL.PLLP = 2;
			osc_inits.PLL.PLLQ = 8;

			clk_inits.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
									RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_inits.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; //100MHz
			clk_inits.AHBCLKDivider = RCC_SYSCLK_DIV1; // 100MHz AHB
			clk_inits.APB1CLKDivider = RCC_HCLK_DIV4; // 25MHz APB1
			clk_inits.APB2CLKDivider = RCC_HCLK_DIV2;// 50MHz APB2

			FLatency = FLASH_LATENCY_3;

			break;
		}
		default:
			return;
	}

	if(HAL_RCC_OscConfig(&osc_inits) != HAL_OK)
	{
		Error_Handler();
	}

	if(HAL_RCC_ClockConfig(&clk_inits, FLatency) != HAL_OK)
	{
		Error_Handler();
	}

	//configure systick

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}


void Error_Handler(void)
{
	while(1);
}
