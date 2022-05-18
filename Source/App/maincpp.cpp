#include "dc-Driver.h"
#include "typedefs.h"
#include "helper_3dmath.h"
#include "MPU6050-App.h"
#include "maincpp.h"

YPRAngle_t y;
DMP_data_t d;
extern float g_current_angle;
MPUData_t g_data;
void_t MPU6050_dmpDataReady(void_t)
{
	MPU_dmpDataReady();
}

u8_t MPU6050_Init(void_t)
{
	//MPU_SUCCESS	0
	//MPU_FAIL		1
	return MPU_Init(&MPU6050_I2C);
}

u8_t MPU6050_GetYawValue(void_t)
{
	//READ_MPU_SUCCESS		0
	//READ_MPU_SUCCESS		1
	//READ_MPU_I2C_LOST		2
	u8_t stt =  MPU_GetYawPitchRoll(y);
	g_current_angle = y.yaw;
	return stt;
}

u8_t MPU6050_GetValue(void_t)
{
	u8_t stt =  MPU_GetDMPValue(d);
	g_data.qx = d.qx;
	g_data.qy = d.qy;
	g_data.qz = d.qz;
	g_data.qw = d.qw;
	g_data.accelX = d.accelX;
	g_data.accelY = d.accelY;
	g_data.accelZ = d.accelZ;
	g_data.gyroX = d.gyroX;
	g_data.gyroY = d.gyroY;
	g_data.gyroZ = d.gyroZ;
	return stt;
}

MPUData_t MPU6050_GetDMPValue(void_t)
{
	return g_data;
}
