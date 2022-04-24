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

float yaw;

void MPU6050_dmpDataReady(void);
uint8_t MPU6050_Init(void);
uint8_t MPU6050_GetYawValue(void);

#ifdef __cplusplus
}
#endif
#endif /* APP_MAINCPP_H_ */
