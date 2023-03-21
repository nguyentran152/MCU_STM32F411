/*
 * main.c
 *
 *  Created on: Jul 11, 2022
 *      Author: Nguyen Tran
 */


#include "main.h"
#include <string.h>

#define TRUE 	1
#define FALSE	0

UART_HandleTypeDef huart2;

void UART2_Init(void);
void Error_Handler(void);


uint8_t Reception_complete = FALSE;

uint8_t data_buffer[100];
uint8_t data_receive;
uint32_t count = 0;
char *some_data = "The application code is running\r\n";

int main()
{
	HAL_Init();
	UART2_Init();

	HAL_UART_Transmit(&huart2, (uint8_t*)some_data, strlen(some_data), HAL_MAX_DELAY);

	while(Reception_complete != TRUE)
	{
		HAL_UART_Receive_IT(&huart2, &data_receive, 1);
	}

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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(data_receive == '\r')
	{
		Reception_complete = TRUE;
		data_buffer[count++] = '\r';
		HAL_UART_Transmit(&huart2, data_buffer, count, HAL_MAX_DELAY);
	}else
	{
		data_buffer[count++] = data_receive;
	}
}

void Error_Handler(void)
{
	while(1);
}


