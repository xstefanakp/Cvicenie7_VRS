/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);


/* Function processing DMA Rx data. Counts how many capital and small letters are in sentence.
 * Result is supposed to be stored in global variable of type "letter_count_" that is defined in "main.h"
 *
 * @param1 - received sign
 */
void proccesDmaData(uint8_t sign);


/* Space for your global variables. */

	// type your global variables here:
int DMA_position = 0;

void printInfoToSerial(){

	size_t needed = snprintf(NULL, 0,"Buffer capacity: %d bytes, occupied memory: %d bytes, load: %d percentage \n \n",DMA_USART2_BUFFER_SIZE, DMA_position, 100*DMA_position/DMA_USART2_BUFFER_SIZE);
	char* info_about_buffer = (char*)malloc(needed);
	snprintf(info_about_buffer, needed,"Buffer capacity: %d bytes, occupied memory: %d bytes, load: %d percentage \n \n", DMA_USART2_BUFFER_SIZE, DMA_position, 100*DMA_position/DMA_USART2_BUFFER_SIZE);
	USART2_PutBuffer(info_about_buffer, needed);

	free(info_about_buffer);

}

int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();

  /* Space for your local variables, callback registration ...*/
  	  char LedOn[6] = "ON ";
  	  char LedOff[7] = "OFF ";
  	  //type your code here:

  while (1)
  {
	 printInfoToSerial();

		LL_mDelay(200);
  }
  /* USER CODE END 3 */
}


void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
  Error_Handler();  
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  
  }
  LL_Init1msTick(8000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(8000000);
}

/*
 * Implementation of function processing data received via USART.
 */
void proccesDmaData(uint8_t sign)
{
	/* Process received data */
	/* Process received data */

	// type your algorithm here:

	int i=0;
	int size = sizeof bufferUSART2dma / sizeof bufferUSART2dma[0];
	for(int j=0;j<size;){

		if(bufferUSART2dma[j]=='#'){

			i=j;

			while (bufferUSART2dma[i] != '$') {
				if (bufferUSART2dma[i] >= 'A' && bufferUSART2dma[i] <= 'Z')
					upper++;
				if (bufferUSART2dma[i] >= 'a' && bufferUSART2dma[i] <= 'z')
					lower++;
				i++;

				if(i==35)
					break;

			}

		}


	}

		// type your algorithm here:
}


void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT

void assert_failed(char *file, uint32_t line)
{ 

}

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
