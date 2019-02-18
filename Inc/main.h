/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

  /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "touch.h"
#include "sram.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
	SemaphoreHandle_t xSemaphoreLine0;
	SemaphoreHandle_t xSemaphoreLine1;
	SemaphoreHandle_t xSemaphoreLine2;
	SemaphoreHandle_t xSemaphoreLine3;

	/* USER CODE END ET */

	/* Exported constants --------------------------------------------------------*/
	/* USER CODE BEGIN EC */

	/* USER CODE END EC */

	/* Exported macro ------------------------------------------------------------*/
	/* USER CODE BEGIN EM */

	/* USER CODE END EM */

	/* Exported functions prototypes ---------------------------------------------*/
	void Error_Handler(void);

	/* USER CODE BEGIN EFP */

	/* USER CODE END EFP */

	/* Private defines -----------------------------------------------------------*/
#define LINE0_NEG_OUTPUT_Pin GPIO_PIN_2
#define LINE0_NEG_OUTPUT_GPIO_Port GPIOE
#define LINE1_NEG_OUTPUT_Pin GPIO_PIN_3
#define LINE1_NEG_OUTPUT_GPIO_Port GPIOE
#define LINE2_NEG_OUTPUT_Pin GPIO_PIN_4
#define LINE2_NEG_OUTPUT_GPIO_Port GPIOE
#define LINE3_NEG_OUTPUT_Pin GPIO_PIN_5
#define LINE3_NEG_OUTPUT_GPIO_Port GPIOE
#define OUTPUT_LINE1_Pin GPIO_PIN_0
#define OUTPUT_LINE1_GPIO_Port GPIOC
#define OUTPUT_LINE2_Pin GPIO_PIN_1
#define OUTPUT_LINE2_GPIO_Port GPIOC
#define OUTPUT_LINE3_Pin GPIO_PIN_2
#define OUTPUT_LINE3_GPIO_Port GPIOC
#define OUTPUT_LINE4_Pin GPIO_PIN_3
#define OUTPUT_LINE4_GPIO_Port GPIOC
#define Isense_Pin GPIO_PIN_0
#define Isense_GPIO_Port GPIOA
#define DTMF_SIGNAL_IN_Pin GPIO_PIN_1
#define DTMF_SIGNAL_IN_GPIO_Port GPIOA
#define PS_Monitor_Pin GPIO_PIN_2
#define PS_Monitor_GPIO_Port GPIOA
#define SRAM_CS_Pin GPIO_PIN_4
#define SRAM_CS_GPIO_Port GPIOA
#define LINE3_POS_OUTPUT_Pin GPIO_PIN_13
#define LINE3_POS_OUTPUT_GPIO_Port GPIOD
#define LINE0_POS_OUTPUT_Pin GPIO_PIN_6
#define LINE0_POS_OUTPUT_GPIO_Port GPIOC
#define LINE1_POS_OUTPUT_Pin GPIO_PIN_7
#define LINE1_POS_OUTPUT_GPIO_Port GPIOC
#define LINE2_POS_OUTPUT_Pin GPIO_PIN_6
#define LINE2_POS_OUTPUT_GPIO_Port GPIOD
#define NOT_PEN_Pin GPIO_PIN_6
#define NOT_PEN_GPIO_Port GPIOB
#define TOUCH_CS_Pin GPIO_PIN_7
#define TOUCH_CS_GPIO_Port GPIOB
#define LCD_RESET_Pin GPIO_PIN_1
#define LCD_RESET_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */
#define LINE_STATUS_OFF  0
#define LINE_STATUS_RUN  1
#define LINE_STATUS_STOP 2

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
