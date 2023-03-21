/*
 * msp.c
 *
 *  Created on: Jul 15, 2022
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


void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
	 GPIO_InitTypeDef tim2ch1_gpio;
	 //1. enable the peripheral clock for the timer2 peripheral
	 __HAL_RCC_TIM2_CLK_ENABLE();
	 __HAL_RCC_GPIOA_CLK_ENABLE();

	 //2. Configure a gpio to behave as timer2 channel 1
	 tim2ch1_gpio.Pin = GPIO_PIN_0;
	 tim2ch1_gpio.Mode = GPIO_MODE_AF_PP;
	 tim2ch1_gpio.Alternate = GPIO_AF1_TIM2;
	 HAL_GPIO_Init(GPIOA,&tim2ch1_gpio);

	 //3. nvic settings
	 HAL_NVIC_SetPriority(TIM2_IRQn,15,0);
	 HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart2)
{
	GPIO_InitTypeDef gpio_uart;

	//Low level inits for UART2 Peripheral
	//1. Enable the clock for the UART2 and GPIO peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	//2. The pin muxing configurations
	gpio_uart.Pin = GPIO_PIN_2; //UART2_TX
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FAST;
	gpio_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	gpio_uart.Pin = GPIO_PIN_3; //UART2_RX
	HAL_GPIO_Init(GPIOA, &gpio_uart);
	//3. Enable the IRQ and set up the priority (NVIC Settings)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}

