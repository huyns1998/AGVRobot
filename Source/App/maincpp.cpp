#include "dc-Driver.h"
#include "typedefs.h"
#include "helper_3dmath.h"
#include "MPU6050-App.h"
#include "maincpp.h"

YPRAngle_t y;
extern float g_current_angle;
void MPU6050_dmpDataReady(void)
{
	MPU_dmpDataReady();
}

uint8_t MPU6050_Init(void)
{
	//MPU_SUCCESS	0
	//MPU_FAIL		1
	return MPU_Init(&MPU6050_I2C);
}

uint8_t MPU6050_GetYawValue(void)
{
	//READ_MPU_SUCCESS		0
	//READ_MPU_SUCCESS		1
	//READ_MPU_I2C_LOST		2
	u8_t stt =  MPU_GetYawPitchRoll(y);
	g_current_angle = y.yaw;
	return stt;
}
