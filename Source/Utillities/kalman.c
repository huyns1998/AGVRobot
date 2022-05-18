/******************************************************************************
 *
 * Copyright (c) 2022
 * Lumi, JSC.
 * All Rights Reserved
 *
 * Description: Ring buffer queue
 *
 * Author: HoangNH
 *
 * Bug Fixes: Fix buffer overflow. Thanks to Mr.Thien reported.
 *
 * Last Changed By:  $Author: hoangnh $
 * Revision:         $Revision: 1.2 $
 * Last Changed:     $Date: 7/6/2020 $
 *
 ******************************************************************************/

 /******************************************************************************/
 /*                              INCLUDE FILES                                 */
 /******************************************************************************/
#include <math.h>
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static float _err_measure;
static float _err_estimate;
static float _q;
static float _current_estimate;
static float _last_estimate;
static float _kalman_gain;
/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/
void KalmanFilterInit(float mea_e, float est_e, float q);
float KalmanFilter_updateEstimate(float mea);
void KalmanFilter_setMeasurementError(float mea_e);
void KalmanFilter_setEstimateError(float est_e);
void KalmanFilter_setProcessNoise(float q);
float KalmanFilter_getKalmanGain(void);
float KalmanFilter_getEstimateError(void);




void KalmanFilterInit(float mea_e, float est_e, float q)
{
  _err_measure=mea_e;
  _err_estimate=est_e;
  _q = q;
}

float KalmanFilter_updateEstimate(float mea)
{
  _kalman_gain = _err_estimate/(_err_estimate + _err_measure);
  _current_estimate = _last_estimate + _kalman_gain * (mea - _last_estimate);
  _err_estimate =  (1.0 - _kalman_gain)*_err_estimate + fabs(_last_estimate-_current_estimate)*_q;
  _last_estimate=_current_estimate;

  return _current_estimate;
}

void KalmanFilter_setMeasurementError(float mea_e)
{
  _err_measure=mea_e;
}

void KalmanFilter_setEstimateError(float est_e)
{
  _err_estimate=est_e;
}

void KalmanFilter_setProcessNoise(float q)
{
  _q=q;
}

float KalmanFilter_getKalmanGain(void) {
  return _kalman_gain;
}

float KalmanFilter_getEstimateError(void) {
  return _err_estimate;
}

/* END FILE */
