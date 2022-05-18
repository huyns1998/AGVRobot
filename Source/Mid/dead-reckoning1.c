/*******************************************************************************
 *				 _ _                                             _ _
				|   |                                           (_ _)
				|   |        _ _     _ _   _ _ _ _ _ _ _ _ _ _   _ _
				|   |       |   |   |   | |    _ _     _ _    | |   |
				|   |       |   |   |   | |   |   |   |   |   | |   |
				|   |       |   |   |   | |   |   |   |   |   | |   |
				|   |_ _ _  |   |_ _|   | |   |   |   |   |   | |   |
				|_ _ _ _ _| |_ _ _ _ _ _| |_ _|   |_ _|   |_ _| |_ _|
								(C)2022 Lumi
 * Copyright (c) 2022
 * Lumi, JSC.
 * All Rights Reserved
 *
 * File name: dead-reckoning.c
 *
 * Description: This code is used for tranning Lumi IOT member. It is the code form statandard.
 *
 * Author: HuyNS
 *
 * Last Changed By:  $Author: huyns $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $May 16, 2022
 *
 * Code sample:
 ******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <math.h>
#include "dc-Driver.h"
#include "DcControl.h"
#include "RobotControl.h"
#include "dead-reckoning1.h"
/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
Robot_pose_t g_robotPose_estimate;
Robot_pose_t g_robotPose_previous;
float g_delta_phi_left, g_delta_phi_right, g_phi_left, g_phi_right;
extern i64_t g_left_pulse_count;
extern i64_t g_right_pulse_count;

u8_t g_byrun_coordinate;
Robot_pose_t g_despose;
u8_t g_by_run_to_des;

robot_move g_robotMove;

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/*****************************************************************************/

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/******************************************************************************/

/**
  * @brief 	calculate phi angle
  *
  * @param 	[w_pulse]		:		how many pulse count
  *
  * @return	[result]		:		angle obtained
  */
float cal_phi_angle(i64_t w_pulse)
{
	float result = 360.0*w_pulse/ENCODER_NUM/DC_RATIO;
	return result;
}

/**
  * @brief 	calculate delta phi angle
  *
  * @param 	[w_pulse]		:		how many pulse count
  * @param 	[w_pulse_prev]		:		how many pulse count previous
  *
  * @return	[result]		:		angle obtained
  */
float cal_delta_phi_angle(float w_pulse, float w_pulse_prev)
{
	return (cal_phi_angle(w_pulse) - cal_phi_angle(w_pulse_prev));
}


/**
  * @brief 	calculate theta angle
  *
  * @param 		-		None
  *
  * @return	[theta]		:		theta angle
  */
float cal_theta_angle(void_t)
{
	float angle;
	g_phi_right = cal_phi_angle(g_right_pulse_count);
	g_phi_left  = cal_phi_angle(g_left_pulse_count);
	angle = (WHEEL_DIAMETER/2)*(g_phi_right-g_phi_left)/(WHEEL_BASE);
	int k =  (int)angle / 180;
	float du = fabs(angle) - 180*fabs(k) ;
	if(k % 2 != 0)
	{
		if(angle > 0)
		{
			angle = -180 + du;
		}
		else
		{
			angle = 180 - du;
		}
	}
	else
	{
		if(angle > 0)
		{
			angle = du;
		}
		else
		{
			angle = -du;
		}
	}

	return angle;
}

/**
  * @brief 	calculate robot pose
  *
  * @param 		-		None
  *
  * @return		-		None
  */
void_t cal_robot_pose(void_t)
{
	float temp_x, temp_y;

	temp_x = (WHEEL_DIAMETER/40.0)*(g_delta_phi_left*M_PI/180 + g_delta_phi_right*M_PI/180)*cos(g_robotPose_previous.theta*M_PI/180);
	temp_y = (WHEEL_DIAMETER/40.0)*(g_delta_phi_left*M_PI/180 + g_delta_phi_right*M_PI/180)*sin(g_robotPose_previous.theta*M_PI/180);

	g_robotPose_estimate.coordinate.x 		= (g_robotPose_previous.coordinate.x + temp_x);//cm
	g_robotPose_estimate.coordinate.y 		= (g_robotPose_previous.coordinate.y + temp_y);
	g_robotPose_estimate.theta 				= cal_theta_angle();

	g_robotPose_previous.coordinate.x 		= g_robotPose_estimate.coordinate.x;
	g_robotPose_previous.coordinate.y 		= g_robotPose_estimate.coordinate.y;
	g_robotPose_previous.theta 				= g_robotPose_estimate.theta;
}

/**
  * @brief 	get robot pose
  *
  * @param 		-		None
  *
  * @return		-		Robot pose
  */
Robot_pose_t get_robot_pose(void_t)
{
	return g_robotPose_estimate;
}

/**
  * @brief 	run to specifed position
  *
  * @param 	[des_pose]	: 	destination
  *
  * @return		-		None
  */
void_t robot_forward_to_position(Robot_pose_t des_pose)
{
	g_robotMove = FORWARD;
	g_despose.coordinate.x = des_pose.coordinate.x;
	g_despose.coordinate.y = des_pose.coordinate.y;
	g_despose.theta = des_pose.theta;
}

/**
  * @brief 	calculate distance between 2 point
  *
  * @param 	[start_pos]	: 	start point
  * @param 	[des_pos]	: 	destination point
  *
  * @return		-		distance beetween 2 points
  */
float cal_distance(Point_t start_pos, Point_t des_pos)
{
	float x = des_pos.x - start_pos.x;
	float y = des_pos.y - start_pos.y;
	float res = sqrtf(powf(x, 2) + powf(y, 2));
	return res;
}

/**
  * @brief 	calculate angle between 2 point and Ox
  *
  * @param 	[start_pos]	: 	start point
  * @param 	[des_pos]	: 	destination point
  *
  * @return		-		distance beetween 2 points
  */
float cal_direction(Point_t start_pos, Point_t des_pos)
{
	float x = des_pos.x - start_pos.x;
	float y = des_pos.y - start_pos.y;

	float denominator = sqrtf(powf(x, 2) + powf(y, 2));
	float cos_phi = x/denominator;
	float phi = acosf(cos_phi)*180/M_PI;

	if(des_pos.y < start_pos.y)
	{
		phi = -phi;
	}
	return phi;
}

/**
  * @brief 	get destination
  *
  * @param 	-	None
  *
  * @return		-		destination position
  */
Robot_pose_t get_robot_despose(void_t)
{
	return g_despose;
}

