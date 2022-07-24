/*
 * main.c
 *
 *  Created on: Jul 11, 2022
 *      Author: Nguyen Tran
 */


#include "main.h"
#include <string.h>

UART_HandleTypeDef huart2;

void SystemClockConfig(void);
void UART2_Init(void);
void Error_Handler(void);
uint8_t Data_conver_to_caps(uint8_t data);

char *some_data = "The application code is running\r\n";

int main()
{
	HAL_Init();
	UART2_Init();

	HAL_UART_Transmit(&huart2, (uint8_t*)some_data, strlen(some_data), HAL_MAX_DELAY);

	uint8_t data_receive;
	uint8_t data_buffer[100];
	uint32_t count = 0;

	while(1)
	{
		HAL_UART_Receive(&huart2, &data_receive, 1, HAL_MAX_DELAY);
		if(data_receive == '\r')
		{
			break;
		}else
		{
			data_buffer[count++] = Data_conver_to_caps(data_receive);
		}
	}

	data_buffer[count++] = '\r';
	HAL_UART_Transmit(&huart2, data_buffer, count, HAL_MAX_DELAY);

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

uint8_t Data_conver_to_caps(uint8_t data)
{
	if(data >= 'a' && data <= 'z')
	{
		data = data - ('a' - 'A');
	}
	return data;
}
