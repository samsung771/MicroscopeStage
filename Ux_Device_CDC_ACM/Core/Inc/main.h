/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32c0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void MX_USART2_UART_Init(void);
void MX_USB_PCD_Init(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MCUbtn_Pin GPIO_PIN_13
#define MCUbtn_GPIO_Port GPIOC
#define GreenLED_Pin GPIO_PIN_5
#define GreenLED_GPIO_Port GPIOA
#define Y_IN4_Pin GPIO_PIN_1
#define Y_IN4_GPIO_Port GPIOB
#define Y_Sleep_Pin GPIO_PIN_10
#define Y_Sleep_GPIO_Port GPIOB
#define Y_IN1_Pin GPIO_PIN_13
#define Y_IN1_GPIO_Port GPIOB
#define Y_IN2_Pin GPIO_PIN_14
#define Y_IN2_GPIO_Port GPIOB
#define Y_IN3_Pin GPIO_PIN_15
#define Y_IN3_GPIO_Port GPIOB
#define X_IN3_Pin GPIO_PIN_8
#define X_IN3_GPIO_Port GPIOA
#define Y_nEnable_Pin GPIO_PIN_8
#define Y_nEnable_GPIO_Port GPIOD
#define Y_nFault_Pin GPIO_PIN_9
#define Y_nFault_GPIO_Port GPIOD
#define Y_SleepA10_Pin GPIO_PIN_10
#define Y_SleepA10_GPIO_Port GPIOA
#define X_IN4_Pin GPIO_PIN_8
#define X_IN4_GPIO_Port GPIOC
#define BlueLED_Pin GPIO_PIN_9
#define BlueLED_GPIO_Port GPIOC
#define X_IN1_Pin GPIO_PIN_4
#define X_IN1_GPIO_Port GPIOB
#define X_IN2_Pin GPIO_PIN_5
#define X_IN2_GPIO_Port GPIOB
#define Y_nEnableB6_Pin GPIO_PIN_6
#define Y_nEnableB6_GPIO_Port GPIOB
#define X_nFault_Pin GPIO_PIN_7
#define X_nFault_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
