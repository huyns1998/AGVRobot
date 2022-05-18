/*
 * maincpp.h
 *
 *  Created on: Apr 20, 2022
 *      Author: hi
 */

#ifndef APP_MAINCPP_H_
#define APP_MAINCPP_H_

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{
	float_t qw;
	float_t qx;
	float_t qy;
	float_t qz;

	float_t gyroX;
	float_t gyroY;
	float_t gyroZ;
	float_t accelX;
	float_t accelY;
	float_t accelZ;
} MPUData_t;

void_t MPU6050_dmpDataReady(void_t);
u8_t MPU6050_Init(void_t);
u8_t MPU6050_GetYawValue(void_t);
u8_t MPU6050_GetValue(void_t);
MPUData_t MPU6050_GetDMPValue(void_t);
#ifdef __cplusplus
}
#endif
#endif /* APP_MAINCPP_H_ */
