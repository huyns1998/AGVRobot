#include <math.h>
#include "dc-Driver.h"
#include "DcControl.h"
#include "RobotControl.h"
#include "queue.h"
#include "dead-reckoning1.h"
#include "maincpp.h"

#define RX_BUFFER_SIZE     16
#define SIZE_QUEUE_DATA_RX 256

u8_t PollRxBuff(void_t);
void_t checkRobotStopCondition(void_t);
void_t updateDeltaphi(void_t);
u8_t pbyDataReceived[3];

typedef enum {
	RX_STATE_START_BYTE, RX_STATE_DATA_BYTES, RX_STATE_CXOR_BYTE
} RX_STATE;

/*
 * Sử dụng kiểu liệt kê Enum liệt kê các trạng thái phản hồi khi nhận dữ liệu.
 */
typedef enum {
	UART_STATE_IDLE,
	UART_STATE_DATA_RECEIVED,
	UART_STATE_ACK_RECEIVED,
	UART_STATE_NACK_RECEIVED,
	UART_STATE_ERROR,
	UART_STATE_RX_TIMEOUT,

} UART_STATE;

static u8_t byRxBufState;
static u8_t byIndexRxBuf;
static u8_t byCheckXorRxBuf;
static buffqueue_t serialQueueRx;
static u8_t pBuffDataRx[SIZE_QUEUE_DATA_RX];
u8_t byRxBuffer[RX_BUFFER_SIZE] = { 0 };
static buffqueue_t serialQueueRx;
u8_t byReceiveData = 0x00;
MPUData_t g_mpudata;

extern i64_t g_left_pulse_count, g_right_pulse_count, g_left_pulse_count_prev, g_right_pulse_count_prev;
extern float g_delta_phi_left, g_delta_phi_right;
extern u8_t g_byrun_coordinate;
extern Robot_pose_t g_despose;
extern u8_t g_by_run_to_des;


float di;
int main(void)
{
	Robot_pose_t pose;

	pose.coordinate.x = 100;
	pose.coordinate.y = -100;

	DcControlSetup();
//	bufInit(&serialQueueRx);
//	if(!MPU6050_Init())
//	{
//		return 0;
//	}
	HAL_UART_Receive_IT(&huart1, pbyDataReceived, 1);

	robot_forward_to_position(pose);

	while (1)
	{
		checkRobotStopCondition();
	}

}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_IT(&huart1, pbyDataReceived, 1);

	//push data into FIFO buffer
	bufEnDat(&serialQueueRx, (u8_p) pbyDataReceived, 1);
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

	robot_stop();

	Point_t start_pos = get_robot_pose().coordinate;
	Point_t des_pos = get_robot_despose().coordinate;
	float direction = cal_direction(start_pos, des_pos);


	if(get_robot_pose().theta > direction + 2)
	{
		robot_rotateright();
	}
	else if (get_robot_pose().theta > direction - 2)
	{
		robot_rotateleft();
	}

	float dis = cal_distance(start_pos, des_pos);
	if(dis > 5)
	{
		robot_forward(30);
	}

}

void_t updateDeltaphi(void_t)
{
	g_delta_phi_left = cal_delta_phi_angle(g_left_pulse_count, g_left_pulse_count_prev);
	g_delta_phi_right = cal_delta_phi_angle(g_right_pulse_count, g_right_pulse_count_prev);
	g_left_pulse_count_prev = g_left_pulse_count;
	g_right_pulse_count_prev = g_right_pulse_count;
	cal_robot_pose();
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

  updateDeltaphi();
//
//  checkRobotStopCondition();
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

//Handle data from PC to device
u8_t PollRxBuff(void_t)
{
	//Data get from buffer
	uint8_t byRxData;
	uint8_t byUartState = (uint8_t) UART_STATE_IDLE;

	while ((bufNumItems(&serialQueueRx) != 0)
			&& (byUartState == UART_STATE_IDLE))
	{
		bufDeDat(&serialQueueRx, &byRxData, 1);
		if(byRxData == 0x0A)
		{
			int a = 0;
			a++;
		}
	}
	return byUartState;
}


