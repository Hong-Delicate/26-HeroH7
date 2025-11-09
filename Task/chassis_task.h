#ifndef __CHASSIS_TASK_H
#define __CHASSIS_TASK_H
#include "main.h"
#include "bsp_rc.h"

#define CHASSIS_TASK_INIT_TIME 200
#define CHASSIS_CONTROL_TIME_MS 10

#define WHEEL_DIAMETER  116.0f
#define CHASSIS_DECELE_RATIO  3591/187.0f
#define LENGTH_A  203.0f
#define LENGTH_B  227.5f

#define fp32 float

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{
  fp32 vx;                      //相对于云台设定速度 前进方向 前为正，单位 cm/s
  fp32 vy;                      //相对于云台设定速度 左右方向 左为正，单位 cm/s
  fp32 wz;                      //底盘设定旋转角速度，逆时针为正 圈/s
} chassis_speed_t;

typedef struct
{
  fp32 vx_set;                      //相对于云台设定速度 前进方向 前为正，单位 cm/s
  fp32 vy_set;                      //相对于云台设定速度 左右方向 左为正，单位 cm/s
  fp32 wz_set;                      //底盘设定旋转角速度，逆时针为正 单位 圈/s
  fp32 chassis_relative_angle;      //底盘与云台的相对角度，单位 rad
  uint16_t chassis_init_angle_set;  //设置相对云台初始前方角度             
  fp32 setSpeed[4];                 //舵轮设定速度
  fp32 setAngle[4];                 //舵轮设定方向

} chassis_move_t;

typedef enum
{
    CHASSIS_FOLLOW_GIMBAL = 0, //底盘跟随云盘行走
    CHASSIS_GYROSCOPE = 1,	   //小陀螺模式
    CHASSIS_NORMAL   = 2,      //底盘不跟随云台行走
} eChassisAction;

extern void chassis_task(void const * argument);
void chassis_rc_ctrl(void);
void chassis_control_loop(void);
void steer_calc(chassis_speed_t *speed,chassis_move_t *out);
fp32 Find_MIN_ANGLE_Enconder(float set,float feed);
void wheel_orientation_init(uint16_t angle1,uint16_t angle2,uint16_t angle3,uint16_t angle4);


#ifdef __cplusplus
 }
#endif
#endif


