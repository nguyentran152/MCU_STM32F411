 /*
 * main.c
 *
 *  Created on: Mar 19, 2023
 *      Author: Nguyen Tran
 */


#include "main.h"
#include <string.h>



void Error_Handler(void);
void GPIO_Init(void);
void UART2_Init(void);
void GPIO_Analog_Config(void);

extern uint8_t somedata[];
UART_HandleTypeDef huart2;

int main()
{
	HAL_Init();
	GPIO_Init();
	UART2_Init();

	/* Keep unused pins in the analog mode to reduce the power consumption */
	GPIO_Analog_Config();

	while(1)
	{
		//going to sleep
		__WFI();
		//MCU resume here when it wake up
		/* User presses button -> MCU wake up and uart transmit data */
	}
	return 0;
}



void GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef buttonpin;
	buttonpin.Pin = GPIO_PIN_0;
	buttonpin.Mode = GPIO_MODE_IT_FALLING;
	buttonpin.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&buttonpin);

	HAL_NVIC_SetPriority(EXTI0_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void GPIO_Analog_Config(void)
{
	GPIO_InitTypeDef gpioA;
	uint32_t gpio_pins = 	GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | \
							GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | \
							GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;

	gpioA.Pin = gpio_pins;
	gpioA.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOA, &gpioA);
}

void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 230400; //increase uart baudrate to reduce the power consumption
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



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
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

