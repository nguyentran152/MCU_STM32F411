/*
 * main.c
 *
 *  Created on: Jul 16, 2022
 *      Author: Nguyen Tran
 */



#include "main.h"
#include <string.h>
#include <stdio.h>

#define TRUE 	1
#define FALSE	0


void Error_Handler(void);
void GPIO_Init(void);
void TIMER2_Init(void);
void SystemClockConfig_HSE(uint8_t clock_freq);



TIM_HandleTypeDef htimer2;
UART_HandleTypeDef huart2;



int main()
{
	HAL_Init();
	SystemClockConfig_HSE(SYSCLK_CONF_FREQ_50MHz);
	GPIO_Init();

	TIMER2_Init();


	if ( HAL_TIM_PWM_Start(&htimer2,TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}

	if ( HAL_TIM_PWM_Start(&htimer2,TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}

	if ( HAL_TIM_PWM_Start(&htimer2,TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}

	if ( HAL_TIM_PWM_Start(&htimer2,TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}

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



void SystemClockConfig_HSE(uint8_t clock_freq)
{
	RCC_OscInitTypeDef osc_inits;
	RCC_ClkInitTypeDef clk_inits;

	uint32_t FLatency  = 0;
	osc_inits.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_inits.HSEState = RCC_HSE_ON;
	osc_inits.PLL.PLLState = RCC_PLL_ON;
	osc_inits.PLL.PLLSource = RCC_PLLSOURCE_HSE;


	switch(clock_freq)
	{
		case SYSCLK_CONF_FREQ_50MHz:
		{
			osc_inits.PLL.PLLM = 8;
			osc_inits.PLL.PLLN = 100;
			osc_inits.PLL.PLLP = 2;
			osc_inits.PLL.PLLQ = 8;

			clk_inits.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
									RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_inits.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; //50MHz
			clk_inits.AHBCLKDivider = RCC_SYSCLK_DIV1; // 50MHz AHB
			clk_inits.APB1CLKDivider = RCC_HCLK_DIV2; // 25MHz APB1
			clk_inits.APB2CLKDivider = RCC_HCLK_DIV2;// 25MHz APB2

			FLatency  = FLASH_LATENCY_1;

			break;
		}
		case SYSCLK_CONF_FREQ_80MHz:
		{
			osc_inits.PLL.PLLM = 8;
			osc_inits.PLL.PLLN = 160;
			osc_inits.PLL.PLLP = 2;
			osc_inits.PLL.PLLQ = 8;

			clk_inits.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
									RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_inits.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; //80MHz
			clk_inits.AHBCLKDivider = RCC_SYSCLK_DIV1; // 80MHz AHB
			clk_inits.APB1CLKDivider = RCC_HCLK_DIV2; // 40MHz APB1
			clk_inits.APB2CLKDivider = RCC_HCLK_DIV2;// 40MHz APB2

			FLatency  = FLASH_LATENCY_2;

			break;
		}
		case SYSCLK_CONF_FREQ_100MHz:
		{
			osc_inits.PLL.PLLM = 8;
			osc_inits.PLL.PLLN = 200;
			osc_inits.PLL.PLLP = 2;
			osc_inits.PLL.PLLQ = 8;

			clk_inits.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | \
									RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
			clk_inits.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; //100MHz
			clk_inits.AHBCLKDivider = RCC_SYSCLK_DIV1; // 100MHz AHB
			clk_inits.APB1CLKDivider = RCC_HCLK_DIV2; // 50MHz APB1
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

	if(HAL_RCC_ClockConfig(&clk_inits, FLatency ) != HAL_OK)
	{
		Error_Handler();
	}

	//configure systick

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

}

/*
 * Fpwm = Ftimer/((Prescaler + 1)(Period + 1)
 *-> This program will generate Fpwm = 1KHz with duty cycle CH1 = 25%, CH2 = 45%, CH3 = 75%, CH4 = 95%
 */

void TIMER2_Init(void)
{
	 TIM_OC_InitTypeDef tim2PWM_Config;
	 htimer2.Instance = TIM2;
	 htimer2.Init.Period = 9;
	 htimer2.Init.Prescaler = 4999;
	 if ( HAL_TIM_PWM_Init(&htimer2) != HAL_OK)
	 {
		 Error_Handler();
	 }

	 memset(&tim2PWM_Config,0,sizeof(tim2PWM_Config));

	 tim2PWM_Config.OCMode = TIM_OCMODE_PWM1;
	 tim2PWM_Config.OCPolarity = TIM_OCPOLARITY_HIGH;


	 tim2PWM_Config.Pulse =  (htimer2.Init.Period * 25 ) /100;

	 if( HAL_TIM_PWM_ConfigChannel(&htimer2,&tim2PWM_Config,TIM_CHANNEL_1) != HAL_OK)
	 {
		 Error_Handler();
	 }

	 tim2PWM_Config.Pulse =  (htimer2.Init.Period * 45 ) /100;
	 if( HAL_TIM_PWM_ConfigChannel(&htimer2,&tim2PWM_Config,TIM_CHANNEL_2) != HAL_OK)
	 {
		 Error_Handler();
	 }

	 tim2PWM_Config.Pulse =  (htimer2.Init.Period * 75 ) /100;
	 if( HAL_TIM_PWM_ConfigChannel(&htimer2,&tim2PWM_Config,TIM_CHANNEL_3) != HAL_OK)
	 {
		 Error_Handler();
	 }

	 tim2PWM_Config.Pulse =  (htimer2.Init.Period * 95 ) /100;
	 if( HAL_TIM_PWM_ConfigChannel(&htimer2,&tim2PWM_Config,TIM_CHANNEL_4) != HAL_OK)
	 {
		 Error_Handler();
	 }
}


void Error_Handler(void)
{
	while(1);
}

