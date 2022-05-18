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
 * File name: dead-reckoning1.h
 *
 *
 * Author: HuyNS
 *
 * Last Changed By:  $Author: huyns $
 * Revision:         $Revision: $
 * Last Changed:     $Date: $May 16, 2022
 *
 * Code sample:
 ******************************************************************************/
// Enclosing macro to prevent multiple inclusion
#ifndef MID_DEAD_RECKONING1_H_
#define MID_DEAD_RECKONING1_H_



/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include "typedefs.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
typedef struct
{
	float x;
	float y;
} Point_t;

typedef struct
{
	Point_t coordinate;
	float theta;
} Robot_pose_t;



typedef enum
{
	FORWARD,
	BACKWARD,
	ROTATE
}robot_move;

//typedef Robot_pose_t (*pfnc)(void_t);

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/
float cal_phi_angle(i64_t w_pulse);
float cal_delta_phi_angle(float w_pulse, float w_pulse_prev);
float cal_theta_angle(void_t);
void_t cal_robot_pose(void_t);
Robot_pose_t get_robot_pose(void_t);
Robot_pose_t get_robot_despose(void_t);
void_t robot_forward_to_position(Robot_pose_t des_pose);
float cal_distance(Point_t start_pos, Point_t des_pos);
float cal_direction(Point_t start_pos, Point_t des_pos);
/******************************************************************************/



#endif /* MID_DEAD_RECKONING1_H_ */
