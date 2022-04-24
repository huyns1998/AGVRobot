#include <math.h>
#include "dc-Driver.h"
#include "DcControl.h"
#include "RobotControl.h"
#include "maincpp.h"

uint8_t pData[10];
int main(void)
{
	DcControlSetup();
//	if(!MPU6050_Init())
//	{
//		return 0;
//	}
	robot_rotateright_angle(185);

//	robot_backward(70);
	HAL_UART_Receive_IT(&huart1, pData, 1);
	while (1)
	{

	}

}
uint8_t data[4];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	static int count;

//	HAL_UART_Receive_IT(&huart1, pData, Size)
//    HAL_UART_Transmit(&huart1, UART1_rxBuffer, 12, 100);
	HAL_UART_Receive_IT(&huart1, pData, 1);
	data[count] = pData[0];
	count++;
	if(count == 3)
	{
		count = 0;
	}
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	MPU6050_dmpDataReady();
}

void_t checkRobotStopCondition(void_t)
{
	u8_t status = MPU6050_GetYawValue();
	if(status == 0)//read success
	{

	}
	else
	{
		if(status == 2)
		{
			MX_I2C1_Init();
		}
	}


	if(isRun_distance())
	{
	  if(getDc1PulseCount() >= getDc1Despulse() && getDc2PulseCount() >= getDc2Despulse())
	  {
		  resetPulse_distance();
		  robot_stop();
	  }
	}
	else if (isRobotRotate())
	{
		if(getRobotState() == ROBOT_ROTATE_LEFT)
		{
			if(fabs(robot_get_current_angle() - robot_get_des_angle()) < 1)
			{
				resetPulse_distance();
				robot_stop();
			}
		}
		else
		{
			if(getRobotState() == ROBOT_ROTATE_RIGHT)
			{
				if(fabs(robot_get_current_angle() - robot_get_des_angle()) < 1)
				{
					resetPulse_distance();
					robot_stop();
				}
			}
		}
	}
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */

  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */
  checkRobotStopCondition();
  /* USER CODE END TIM4_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}


