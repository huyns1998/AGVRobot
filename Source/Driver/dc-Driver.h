/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "typedefs.h"

#define TIM_PERIOD						8400
#define ENCODER_NUM						11
#define DC_RATIO						30
//DC1(left)
#define DC1_C2_PORT						GPIOA
#define DC1_C2_PIN						GPIO_PIN_2
#define DC1_TIM_PWM						htim1
#define DC1_TIM_PWM_CHANNEL				TIM_CHANNEL_4

#define DC1_TIM_PULSE_COUNT				htim2
#define DC1_TIM_PULSE_COUNT_CHANNEL		TIM_CHANNEL_2
#define DC1_TIM_PULSE_COUNT_CHANNEL_ACTIVE		HAL_TIM_ACTIVE_CHANNEL_2

#define DC1_TIM_UPDATE					htim3

#define INT1_PORT						GPIOA
#define INT1_PIN 						GPIO_PIN_0
#define INT2_PORT						GPIOA
#define INT2_PIN						GPIO_PIN_1

//DC2(right)
#define DC2_C2_PORT						GPIOA
#define DC2_C2_PIN						GPIO_PIN_3
#define DC2_TIM_PWM						htim1
#define DC2_TIM_PWM_CHANNEL				TIM_CHANNEL_1

#define DC2_TIM_PULSE_COUNT				htim2
#define DC2_TIM_PULSE_COUNT_CHANNEL		TIM_CHANNEL_3
#define DC2_TIM_PULSE_COUNT_CHANNEL_ACTIVE		HAL_TIM_ACTIVE_CHANNEL_3

#define DC2_TIM_UPDATE					DC1_TIM_UPDATE

#define INT3_PORT						GPIOA
#define INT3_PIN 						GPIO_PIN_4
#define INT4_PORT						GPIOA
#define INT4_PIN						GPIO_PIN_5

#define TIM_CHECK_ROBOT_STOP_UPDATE		htim4
#define MPU6050_I2C						hi2c1

#define WHEEL_DIAMETER	64//mm
#define WHEEL_BASE					279//mm
#define SAMPLING_TIME				5
#define INV_SAMPLING_TIME			200



/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void DcControlSetup(void);
void MX_I2C1_Init(void);
void_t dcControl(i32_t wPulse, TIM_HandleTypeDef htim, u8_t tim_Channel);
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define INT1_Pin GPIO_PIN_0
#define INT1_GPIO_Port GPIOA
#define INT2_Pin GPIO_PIN_1
#define INT2_GPIO_Port GPIOA
#define DC1_C2_Pin GPIO_PIN_2
#define DC1_C2_GPIO_Port GPIOA
#define DC2_C2_Pin GPIO_PIN_3
#define DC2_C2_GPIO_Port GPIOA
#define INT3_Pin GPIO_PIN_4
#define INT3_GPIO_Port GPIOA
#define INT4_Pin GPIO_PIN_5
#define INT4_GPIO_Port GPIOA
#define DC2_TIM_PWM_Pin GPIO_PIN_9
#define DC2_TIM_PWM_GPIO_Port GPIOE
#define DC1_TIM_PWM_Pin GPIO_PIN_14
#define DC1_TIM_PWM_GPIO_Port GPIOE
#define DC2_TIM_IC_Pin GPIO_PIN_10
#define DC2_TIM_IC_GPIO_Port GPIOB
#define DC1_TIM_IC_Pin GPIO_PIN_3
#define DC1_TIM_IC_GPIO_Port GPIOB
#define MPU_INT_Pin GPIO_PIN_5
#define MPU_INT_GPIO_Port GPIOB
#define MPU_INT_EXTI_IRQn EXTI9_5_IRQn
#define MPU_SCL_Pin GPIO_PIN_6
#define MPU_SCL_GPIO_Port GPIOB
#define MPU_SDA_Pin GPIO_PIN_7
#define MPU_SDA_GPIO_Port GPIOB
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
