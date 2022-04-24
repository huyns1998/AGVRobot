/*******************************************************************************
 *				 _ _                                             _ _
				|   |                                           (_ _)
				|   |        _ _     _ _   _ _ _ _ _ _ _ _ _ _   _ _
				|   |       |   |   |   | |    _ _     _ _    | |   |
				|   |       |   |   |   | |   |   |   |   |   | |   |
				|   |       |   |   |   | |   |   |   |   |   | |   |
				|   |_ _ _  |   |_ _|   | |   |   |   |   |   | |   |
				|_ _ _ _ _| |_ _ _ _ _ _| |_ _|   |_ _|   |_ _| |_ _|
								(C)2021 Lumi
 * Copyright (c) 2021
 * Lumi, JSC.
 * All Rights Reserved
 *
 * File name: DcControl.c
 *
 * Description: This code is used for tranning Lumi IOT member. It is the code form statandard.
 *
 * Author: HuyNS
 *
 * Last Changed By:  $Author: huyns $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $April 14, 2022
 *
 * Code sample:
 ******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <math.h>
#include <stdlib.h>
#include "stm32f4xx_hal_tim.h"
#include "dc-Driver.h"
#include "DcControl.h"
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
i32_t g_iwErrDc1, g_iwPreErrDc1, g_iwRpmDc1;
u8_t g_byKp = 20, g_byKd = 5, g_byKi = 0;
i32_t g_iwpPartDc1 = 0, g_iwdPartDc1 = 0, g_iwiPartDc1 = 0, g_iwOutputDc1, g_iwPulseDc1;

i32_t g_iwdesPulseDc2, g_iwErrDc2, g_iwPreErrDc2, g_iwRpmDc2;
i32_t g_iwpPartDc2 = 0, g_iwdPartDc2 = 0, g_iwiPartDc2 = 0, g_iwOutputDc2, g_iwPulseDc2;

dcState g_DirectionDc1 = DC_STOP;
dcState g_DirectionDc2 = DC_STOP;

u8_t g_run_distance;
u32_t g_dc1_pulse;
u32_t g_dc2_pulse;

u32_t g_dc1_pulse_count, g_dc2_pulse_count;


/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
static void_t checkDcStatus(void_t);
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/

/**
  * @brief 	supply pulse for DC
  *
  * @param 	[wDespulse]		:		pulse want to obtain
  *
  * @return		-	NonewDespulse
  */
void_t dc1_speed_PID(u32_t wDespulse)
{
	g_iwErrDc1 = wDespulse - abs(g_iwPulseDc1);

	g_iwpPartDc1 = g_byKp*g_iwErrDc1;
	g_iwdPartDc1 = g_byKd*(g_iwErrDc1 - g_iwPreErrDc1)*INV_SAMPLING_TIME;
	g_iwiPartDc1 += g_byKi*SAMPLING_TIME*g_iwErrDc1/1000;
	g_iwOutputDc1 += g_iwpPartDc1 + g_iwdPartDc1 + g_iwiPartDc1;

	if(g_iwOutputDc1 >= TIM_PERIOD) g_iwOutputDc1 = TIM_PERIOD - 1;
	if(g_iwOutputDc1 <= 0) g_iwOutputDc1 = 1;

	dcControl(g_iwOutputDc1, DC1_TIM_PWM, DC1_TIM_PWM_CHANNEL);

	g_iwPreErrDc1 = g_iwErrDc1;


}

/**
  * @brief 	supply pulse for DC
  *
  * @param 	[wDespulse]		:		pulse want to obtain
  *
  * @return		-	NonewDespulse
  */
void_t dc2_speed_PID(u32_t wDespulse)
{
	g_iwErrDc2 = wDespulse - abs(g_iwPulseDc2);

	g_iwpPartDc2 = g_byKp*g_iwErrDc2;
	g_iwdPartDc2 = g_byKd*(g_iwErrDc2 - g_iwPreErrDc2)*INV_SAMPLING_TIME;
	g_iwiPartDc2 += g_byKi*SAMPLING_TIME*g_iwErrDc2/1000;
	g_iwOutputDc2 += g_iwpPartDc2 + g_iwdPartDc2 + g_iwiPartDc2;

	if(g_iwOutputDc2 >= TIM_PERIOD) g_iwOutputDc2 = TIM_PERIOD - 1;
	if(g_iwOutputDc2 <= 0) g_iwOutputDc2 = 1;

	dcControl(g_iwOutputDc2, DC2_TIM_PWM, DC2_TIM_PWM_CHANNEL);

	g_iwPreErrDc2 = g_iwErrDc2;
}

/* USER CODE BEGIN 4 */
/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&DC1_TIM_PULSE_COUNT);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}
/* USER CODE END 4 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	UNUSED(htim);
	if(htim->Instance == DC1_TIM_PULSE_COUNT.Instance && htim->Channel == DC1_TIM_PULSE_COUNT_CHANNEL_ACTIVE)
	{
		u8_t byDirection = HAL_GPIO_ReadPin(DC1_C2_PORT, DC1_C2_PIN);

		if(byDirection == 1)
		{
//			g_DirectionDc1 = DC_CLOCWISE;
			g_iwPulseDc1++;
		}
		else
		{
//			g_DirectionDc1 = DC_ANTICLOCKWISE;
			g_iwPulseDc1--;
		}

		if(g_run_distance == 1)
		{
			g_dc1_pulse_count++;
//			if(g_dc1_pulse_count >= g_dc1_pulse)
//			{
//				g_dc1_pulse = 0;
//				g_dc1_pulse_count = 0;
//			}
		}
	}
	else
	{
		if(htim->Instance == DC2_TIM_PULSE_COUNT.Instance && htim->Channel == DC2_TIM_PULSE_COUNT_CHANNEL_ACTIVE)
		{
			u8_t byDirection = HAL_GPIO_ReadPin(DC2_C2_PORT, DC2_C2_PIN);

			if(byDirection == 1)
			{
//					g_DirectionDc2 = DC_CLOCWISE;
				g_iwPulseDc2++;
			}
			else
			{
//					g_DirectionDc2 = DC_ANTICLOCKWISE;
				g_iwPulseDc2--;
			}

			if(g_run_distance == 1)
			{
				g_dc2_pulse_count++;
//				if(g_dc2_pulse_count >= g_dc2_pulse)
//				{
//					g_dc2_pulse = 0;
//					g_dc2_pulse_count = 0;
//				}
			}
		}
	}
}


/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&DC1_TIM_UPDATE);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	UNUSED(htim);
	if(htim->Instance == DC1_TIM_UPDATE.Instance)
	{
		dc1_speed_PID(g_wDespulse);
		dc2_speed_PID(g_wDespulse);
		checkDcStatus();
	}
}

/**
  * @brief 	Update DC speed
  *
  * @param 	-	None
  *
  * @return		-	None
  */
static void_t checkDcStatus(void_t)
{
	g_iwRpmDc1 = g_iwPulseDc1*INV_SAMPLING_TIME*60/(11*30);
	g_iwRpmDc2 = g_iwPulseDc2*INV_SAMPLING_TIME*60/(11*30);
	g_iwPulseDc1 = 0;
	g_iwPulseDc2 = 0;
}

/**
  * @brief 	Rotate Dc1 clock wise
  *
  * @param 	[rpm]:	round per minute
  *
  * @return		-	None
  */
void_t dc1_RotateClockWise(u16_t wRpm)
{
	HAL_GPIO_WritePin(INT1_PORT, INT1_PIN, SET);
	HAL_GPIO_WritePin(INT2_PORT, INT2_PIN, RESET);

	float temp = (float)(wRpm);

	temp = (float)(temp/INV_SAMPLING_TIME/60)*11*30;

	g_wDespulse = roundf(temp);

	dc1_speed_PID(g_wDespulse);
	g_DirectionDc1 = DC_CLOCKWISE;
}

/**
  * @brief 	Rotate Dc1 anti-clockwise
  *
  * @param 	[rpm]:	round per minute
  *
  * @return		-	None
  */
void_t dc1_RotateAntiClockWise(u16_t wRpm)
{
	HAL_GPIO_WritePin(INT1_PORT, INT1_PIN, RESET);
	HAL_GPIO_WritePin(INT2_PORT, INT2_PIN, SET);

	float temp = (float)(wRpm);

	temp = (float)(temp/INV_SAMPLING_TIME/60)*11*30;

	g_wDespulse = roundf(temp);

	dc1_speed_PID(g_wDespulse);


	g_DirectionDc1 = DC_ANTICLOCKWISE;
}

/**
  * @brief 	Stop Dc1
  *
  * @param 	[rpm]:	round per minute
  *
  * @return		-	None
  */
void_t dc1_Stop(void_t)
{
	HAL_GPIO_WritePin(INT1_PORT, INT1_PIN, RESET);
	HAL_GPIO_WritePin(INT2_PORT, INT2_PIN, RESET);

	g_DirectionDc1 = DC_STOP;
}


/**
  * @brief 	Rotate Dc2 clock wise
  *
  * @param 	[rpm]:	round per minute
  *
  * @return		-	None
  */
void_t dc2_RotateClockWise(u16_t wRpm)
{
	HAL_GPIO_WritePin(INT3_PORT, INT3_PIN, RESET);
	HAL_GPIO_WritePin(INT4_PORT, INT4_PIN, SET);

	float temp = (float)(wRpm);

	temp = (float)(temp/INV_SAMPLING_TIME/60)*11*30;

	g_wDespulse = roundf(temp);

	dc2_speed_PID(g_wDespulse);
	g_DirectionDc2 = DC_CLOCKWISE;
}

/**
  * @brief 	Rotate Dc2 anti-clockwise
  *
  * @param 	[rpm]:	round per minute
  *
  * @return		-	None
  */
void_t dc2_RotateAntiClockWise(u16_t wRpm)
{
	HAL_GPIO_WritePin(INT3_PORT, INT3_PIN, SET);
	HAL_GPIO_WritePin(INT4_PORT, INT4_PIN, RESET);

	float temp = (float)(wRpm);

	temp = (float)(temp/INV_SAMPLING_TIME/60)*11*30;

	g_wDespulse = roundf(temp);

	dc2_speed_PID(g_wDespulse);


	g_DirectionDc2 = DC_ANTICLOCKWISE;
}

/**
  * @brief 	Stop Dc2
  *
  * @param 	[rpm]:	round per minute
  *
  * @return		-	None
  */
void_t dc2_Stop(void_t)
{
	HAL_GPIO_WritePin(INT3_PORT, INT3_PIN, RESET);
	HAL_GPIO_WritePin(INT4_PORT, INT4_PIN, RESET);

	g_DirectionDc2 = DC_STOP;
}


