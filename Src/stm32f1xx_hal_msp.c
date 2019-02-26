/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : stm32f1xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization
  *                      and de-Initialization codes.
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
extern DMA_HandleTypeDef hdma_adc1;

extern DMA_HandleTypeDef hdma_usart1_rx;

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
	/* USER CODE BEGIN MspInit 0 */

	/* USER CODE END MspInit 0 */

	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();

	/* System interrupt init*/
	/* PendSV_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);

	/**ENABLE: Full SWJ (JTAG-DP + SW-DP): Reset State 
	*/
	__HAL_AFIO_REMAP_SWJ_ENABLE();

	/* USER CODE BEGIN MspInit 1 */

	/* USER CODE END MspInit 1 */
}

/**
* @brief ADC MSP Initialization
* This function configures the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (hadc->Instance == ADC1)
	{
		/* USER CODE BEGIN ADC1_MspInit 0 */

		/* USER CODE END ADC1_MspInit 0 */
		  /* Peripheral clock enable */
		__HAL_RCC_ADC1_CLK_ENABLE();
  
		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**ADC1 GPIO Configuration    
		PA0-WKUP     ------> ADC1_IN0 
		*/
		GPIO_InitStruct.Pin = Isense_LOAD_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		HAL_GPIO_Init(Isense_LOAD_GPIO_Port, &GPIO_InitStruct);

		/* ADC1 DMA Init */
		/* ADC1 Init */
		hdma_adc1.Instance = DMA1_Channel1;
		hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
		hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
		hdma_adc1.Init.MemDataAlignment = DMA_PDATAALIGN_HALFWORD;
		hdma_adc1.Init.Mode = DMA_NORMAL;
		hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
		if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(hadc, DMA_Handle, hdma_adc1);

		/* ADC1 interrupt Init */
		HAL_NVIC_SetPriority(ADC1_2_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(ADC1_2_IRQn);
		/* USER CODE BEGIN ADC1_MspInit 1 */

		/* USER CODE END ADC1_MspInit 1 */
	}
	else if (hadc->Instance == ADC3)
	{
		/* USER CODE BEGIN ADC3_MspInit 0 */

		/* USER CODE END ADC3_MspInit 0 */
		  /* Peripheral clock enable */
		__HAL_RCC_ADC3_CLK_ENABLE();
  
		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**ADC3 GPIO Configuration    
		PA1     ------> ADC3_IN1 
		*/
		GPIO_InitStruct.Pin = Vsense_PSU_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		HAL_GPIO_Init(Vsense_PSU_GPIO_Port, &GPIO_InitStruct);

		/* ADC3 interrupt Init */
		HAL_NVIC_SetPriority(ADC3_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(ADC3_IRQn);
		/* USER CODE BEGIN ADC3_MspInit 1 */

		/* USER CODE END ADC3_MspInit 1 */
	}

}

/**
* @brief ADC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{

	if (hadc->Instance == ADC1)
	{
		/* USER CODE BEGIN ADC1_MspDeInit 0 */

		/* USER CODE END ADC1_MspDeInit 0 */
		  /* Peripheral clock disable */
		__HAL_RCC_ADC1_CLK_DISABLE();
  
		/**ADC1 GPIO Configuration    
		PA0-WKUP     ------> ADC1_IN0 
		*/
		HAL_GPIO_DeInit(Isense_LOAD_GPIO_Port, Isense_LOAD_Pin);

		/* ADC1 DMA DeInit */
		HAL_DMA_DeInit(hadc->DMA_Handle);

		/* ADC1 interrupt DeInit */
		HAL_NVIC_DisableIRQ(ADC1_2_IRQn);
		/* USER CODE BEGIN ADC1_MspDeInit 1 */

		/* USER CODE END ADC1_MspDeInit 1 */
	}
	else if (hadc->Instance == ADC3)
	{
		/* USER CODE BEGIN ADC3_MspDeInit 0 */

		/* USER CODE END ADC3_MspDeInit 0 */
		  /* Peripheral clock disable */
		__HAL_RCC_ADC3_CLK_DISABLE();
  
		/**ADC3 GPIO Configuration    
		PA1     ------> ADC3_IN1 
		*/
		HAL_GPIO_DeInit(Vsense_PSU_GPIO_Port, Vsense_PSU_Pin);

		/* ADC3 interrupt DeInit */
		HAL_NVIC_DisableIRQ(ADC3_IRQn);
		/* USER CODE BEGIN ADC3_MspDeInit 1 */

		/* USER CODE END ADC3_MspDeInit 1 */
	}

}

/**
* @brief CRC MSP Initialization
* This function configures the hardware resources used in this example
* @param hcrc: CRC handle pointer
* @retval None
*/
void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc)
{

	if (hcrc->Instance == CRC)
	{
		/* USER CODE BEGIN CRC_MspInit 0 */

		/* USER CODE END CRC_MspInit 0 */
		  /* Peripheral clock enable */
		__HAL_RCC_CRC_CLK_ENABLE();
		/* USER CODE BEGIN CRC_MspInit 1 */

		/* USER CODE END CRC_MspInit 1 */
	}

}

/**
* @brief CRC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hcrc: CRC handle pointer
* @retval None
*/

void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc)
{

	if (hcrc->Instance == CRC)
	{
		/* USER CODE BEGIN CRC_MspDeInit 0 */

		/* USER CODE END CRC_MspDeInit 0 */
		  /* Peripheral clock disable */
		__HAL_RCC_CRC_CLK_DISABLE();
		/* USER CODE BEGIN CRC_MspDeInit 1 */

		/* USER CODE END CRC_MspDeInit 1 */
	}

}

/**
* @brief RTC MSP Initialization
* This function configures the hardware resources used in this example
* @param hrtc: RTC handle pointer
* @retval None
*/
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{

	if (hrtc->Instance == RTC)
	{
		/* USER CODE BEGIN RTC_MspInit 0 */

		/* USER CODE END RTC_MspInit 0 */
		HAL_PWR_EnableBkUpAccess();
		/* Enable BKP CLK enable for backup registers */
		__HAL_RCC_BKP_CLK_ENABLE();
		/* Peripheral clock enable */
		__HAL_RCC_RTC_ENABLE();
		/* RTC interrupt Init */
		HAL_NVIC_SetPriority(RTC_IRQn, 15, 0);
		HAL_NVIC_EnableIRQ(RTC_IRQn);
		/* USER CODE BEGIN RTC_MspInit 1 */

		/* USER CODE END RTC_MspInit 1 */
	}

}

/**
* @brief RTC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hrtc: RTC handle pointer
* @retval None
*/

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{

	if (hrtc->Instance == RTC)
	{
		/* USER CODE BEGIN RTC_MspDeInit 0 */

		/* USER CODE END RTC_MspDeInit 0 */
		  /* Peripheral clock disable */
		__HAL_RCC_RTC_DISABLE();

		/* RTC interrupt DeInit */
		HAL_NVIC_DisableIRQ(RTC_IRQn);
		/* USER CODE BEGIN RTC_MspDeInit 1 */

		/* USER CODE END RTC_MspDeInit 1 */
	}

}

/**
* @brief SPI MSP Initialization
* This function configures the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (hspi->Instance == SPI1)
	{
		/* USER CODE BEGIN SPI1_MspInit 0 */

		/* USER CODE END SPI1_MspInit 0 */
		  /* Peripheral clock enable */
		__HAL_RCC_SPI1_CLK_ENABLE();
  
		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**SPI1 GPIO Configuration    
		PA5     ------> SPI1_SCK
		PA6     ------> SPI1_MISO
		PA7     ------> SPI1_MOSI 
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN SPI1_MspInit 1 */

		/* USER CODE END SPI1_MspInit 1 */
	}

}

/**
* @brief SPI MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hspi: SPI handle pointer
* @retval None
*/

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{

	if (hspi->Instance == SPI1)
	{
		/* USER CODE BEGIN SPI1_MspDeInit 0 */

		/* USER CODE END SPI1_MspDeInit 0 */
		  /* Peripheral clock disable */
		__HAL_RCC_SPI1_CLK_DISABLE();
  
		/**SPI1 GPIO Configuration    
		PA5     ------> SPI1_SCK
		PA6     ------> SPI1_MISO
		PA7     ------> SPI1_MOSI 
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

		/* USER CODE BEGIN SPI1_MspDeInit 1 */

		/* USER CODE END SPI1_MspDeInit 1 */
	}

}

/**
* @brief TIM_Base MSP Initialization
* This function configures the hardware resources used in this example
* @param htim_base: TIM_Base handle pointer
* @retval None
*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

	if (htim_base->Instance == TIM7)
	{
		/* USER CODE BEGIN TIM7_MspInit 0 */

		/* USER CODE END TIM7_MspInit 0 */
		  /* Peripheral clock enable */
		__HAL_RCC_TIM7_CLK_ENABLE();
		/* TIM7 interrupt Init */
		HAL_NVIC_SetPriority(TIM7_IRQn, 15, 0);
		HAL_NVIC_EnableIRQ(TIM7_IRQn);
		/* USER CODE BEGIN TIM7_MspInit 1 */

		/* USER CODE END TIM7_MspInit 1 */
	}

}

/**
* @brief TIM_Base MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param htim_base: TIM_Base handle pointer
* @retval None
*/

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

	if (htim_base->Instance == TIM7)
	{
		/* USER CODE BEGIN TIM7_MspDeInit 0 */

		/* USER CODE END TIM7_MspDeInit 0 */
		  /* Peripheral clock disable */
		__HAL_RCC_TIM7_CLK_DISABLE();

		/* TIM7 interrupt DeInit */
		HAL_NVIC_DisableIRQ(TIM7_IRQn);
		/* USER CODE BEGIN TIM7_MspDeInit 1 */

		/* USER CODE END TIM7_MspDeInit 1 */
	}

}

/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (huart->Instance == USART1)
	{
		/* USER CODE BEGIN USART1_MspInit 0 */

		/* USER CODE END USART1_MspInit 0 */
		  /* Peripheral clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();
  
		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART1 GPIO Configuration    
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX 
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USART1 DMA Init */
		/* USART1_RX Init */
		hdma_usart1_rx.Instance = DMA1_Channel5;
		hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
		hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
		hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
		hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
		hdma_usart1_rx.Init.Mode = DMA_NORMAL;
		hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
		if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
		{
			Error_Handler();
		}

		__HAL_LINKDMA(huart, hdmarx, hdma_usart1_rx);

		/* USART1 interrupt Init */
		HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspInit 1 */

		/* USER CODE END USART1_MspInit 1 */
	}

}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

	if (huart->Instance == USART1)
	{
		/* USER CODE BEGIN USART1_MspDeInit 0 */

		/* USER CODE END USART1_MspDeInit 0 */
		  /* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();
  
		/**USART1 GPIO Configuration    
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX 
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);

		/* USART1 DMA DeInit */
		HAL_DMA_DeInit(huart->hdmarx);

		/* USART1 interrupt DeInit */
		HAL_NVIC_DisableIRQ(USART1_IRQn);
		/* USER CODE BEGIN USART1_MspDeInit 1 */

		/* USER CODE END USART1_MspDeInit 1 */
	}

}

static uint32_t FSMC_Initialized = 0;

static void HAL_FSMC_MspInit(void) {
	/* USER CODE BEGIN FSMC_MspInit 0 */

	/* USER CODE END FSMC_MspInit 0 */
	GPIO_InitTypeDef GPIO_InitStruct;
	if (FSMC_Initialized) {
		return;
	}
	FSMC_Initialized = 1;
	/* Peripheral clock enable */
	__HAL_RCC_FSMC_CLK_ENABLE();
  
	/** FSMC GPIO Configuration  
	PE7   ------> FSMC_D4
	PE8   ------> FSMC_D5
	PE9   ------> FSMC_D6
	PE10   ------> FSMC_D7
	PE11   ------> FSMC_D8
	PE12   ------> FSMC_D9
	PE13   ------> FSMC_D10
	PE14   ------> FSMC_D11
	PE15   ------> FSMC_D12
	PD8   ------> FSMC_D13
	PD9   ------> FSMC_D14
	PD10   ------> FSMC_D15
	PD11   ------> FSMC_A16
	PD14   ------> FSMC_D0
	PD15   ------> FSMC_D1
	PD0   ------> FSMC_D2
	PD1   ------> FSMC_D3
	PD4   ------> FSMC_NOE
	PD5   ------> FSMC_NWE
	PD7   ------> FSMC_NE1
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 
	                        | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 
	                        | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 
	                        | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1 
	                        | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* USER CODE BEGIN FSMC_MspInit 1 */

	/* USER CODE END FSMC_MspInit 1 */
}

void HAL_SRAM_MspInit(SRAM_HandleTypeDef* hsram) {
	/* USER CODE BEGIN SRAM_MspInit 0 */

	/* USER CODE END SRAM_MspInit 0 */
	HAL_FSMC_MspInit();
	/* USER CODE BEGIN SRAM_MspInit 1 */

	/* USER CODE END SRAM_MspInit 1 */
}

static uint32_t FSMC_DeInitialized = 0;

static void HAL_FSMC_MspDeInit(void) {
	/* USER CODE BEGIN FSMC_MspDeInit 0 */

	/* USER CODE END FSMC_MspDeInit 0 */
	if (FSMC_DeInitialized) {
		return;
	}
	FSMC_DeInitialized = 1;
	/* Peripheral clock enable */
	__HAL_RCC_FSMC_CLK_DISABLE();
  
	/** FSMC GPIO Configuration  
	PE7   ------> FSMC_D4
	PE8   ------> FSMC_D5
	PE9   ------> FSMC_D6
	PE10   ------> FSMC_D7
	PE11   ------> FSMC_D8
	PE12   ------> FSMC_D9
	PE13   ------> FSMC_D10
	PE14   ------> FSMC_D11
	PE15   ------> FSMC_D12
	PD8   ------> FSMC_D13
	PD9   ------> FSMC_D14
	PD10   ------> FSMC_D15
	PD11   ------> FSMC_A16
	PD14   ------> FSMC_D0
	PD15   ------> FSMC_D1
	PD0   ------> FSMC_D2
	PD1   ------> FSMC_D3
	PD4   ------> FSMC_NOE
	PD5   ------> FSMC_NWE
	PD7   ------> FSMC_NE1
	*/
	HAL_GPIO_DeInit(GPIOE,
		GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
	                        |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
	                        |GPIO_PIN_15);

	HAL_GPIO_DeInit(GPIOD,
		GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
	                        |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1 
	                        |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7);

	/* USER CODE BEGIN FSMC_MspDeInit 1 */

	/* USER CODE END FSMC_MspDeInit 1 */
}

void HAL_SRAM_MspDeInit(SRAM_HandleTypeDef* hsram) {
	/* USER CODE BEGIN SRAM_MspDeInit 0 */

	/* USER CODE END SRAM_MspDeInit 0 */
	HAL_FSMC_MspDeInit();
	/* USER CODE BEGIN SRAM_MspDeInit 1 */

	/* USER CODE END SRAM_MspDeInit 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
