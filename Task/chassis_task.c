#include "chassis_task.h"
#include "cmsis_os2.h"
#include "main.h"
#include "bsp_fdcan.h"
#include "usbd_cdc_if.h"
#include "outctl_task.h"
#include "pid.h"

/*     速度比例系数         */
#define vx_ratio 3.0f
#define vy_ratio 3.0f
#define wz_rztio 600.0f

/*      底盘控制模式        */
eChassisAction actChassis=CHASSIS_FOLLOW_GIMBAL;
chassis_move_t chassis_move;
chassis_speed_t absolute_chassis;

/*      舵轮角度映射系数     */
#define pi 3.141592653589793f
#define angle_map(angle)  angle > 0 ? angle : angle + 2 * pi

 
/**
 * @brief 底盘控制任务
 * @param argument 任务参数指针
 */
void chassis_task(void const * argument)
{
    osDelay(CHASSIS_TASK_INIT_TIME);
    uint32_t previousWakeTime = osKernelGetTickCount();
    wheel_orientation_init(0, 0, 0, 0);//舵向电机正前方初始编码值设置
     for(int i=0; i<4; i++)	
    {
        PID_Init(&PID_M3508[i],POSITION_PID,16000,5000,5,0,1,0,0);  //四个轮毂电机的PID初始化
        PID_Init(&PID_GM6020[i], POSITION_PID, 16384, 1000,10, 0, 6, 500, 0); //四个舵向电机PID初始化
		PID_Init(&PID_GM6020_speed[i], POSITION_PID,4000, 1000,10,0, 10, 500, 0); //四个舵向电机PID初始化
    }
	PID_Init(&PID_M3508_Follow,POSITION_PID,1000,1000,7.5,0,1,0,0);
    while (1)
    {
        if(rc_flag)
        {
            switch(rc.sw2)
            {
                case 1:
                    actChassis = CHASSIS_FOLLOW_GIMBAL;//底盘跟随云台模式
                    break;
                case 3:
                    actChassis = CHASSIS_NORMAL;//底盘不跟随云台
                    break;
                case 2:
                    actChassis = CHASSIS_GYROSCOPE;//小陀螺模式
                    break;
                default:
                    break;
            }
            chassis_rc_ctrl();
            chassis_control_loop();
        }
        osDelayUntil(previousWakeTime + CHASSIS_CONTROL_TIME_MS);
    }
}

void chassis_rc_ctrl(void)
{
    switch(actChassis)
    {
        case CHASSIS_FOLLOW_GIMBAL:
            chassis_move.vx_set =(fp32)rc.ch3/vx_ratio; //前后计算
            chassis_move.vy_set =(fp32)rc.ch2/vy_ratio; //左右计算
            chassis_move.wz_set=rc.ch0/wz_rztio-PID_Calculate(&PID_M3508_Follow,
            Find_MIN_ANGLE_Enconder(chassis_move.chassis_init_angle_set,CAN_GM6020[0].angle),0)/1500.0f;///PID使底盘跟随云台速度
            break;
        case CHASSIS_NORMAL:
            chassis_move.vx_set =(fp32)rc.ch3/vx_ratio; //前后计算
            chassis_move.vy_set =(fp32)rc.ch2/vy_ratio; //左右计算
            chassis_move.wz_set=rc.ch0/wz_rztio;
            break;
        case CHASSIS_GYROSCOPE:
            chassis_move.vx_set =(fp32)rc.ch3/vx_ratio; //前后计算
            chassis_move.vy_set =(fp32)rc.ch2/vy_ratio; //左右计算
            chassis_move.wz_set=-2;
            break;
        default:
            break;
    }
}

void chassis_control_loop(void){
	steer_calc(&absolute_chassis,&chassis_move);
	for(int i=0; i<4; i++) 
    {
        CAN_M3508[i].set_current =  PID_Calculate(&PID_M3508[i], chassis_move.setSpeed[i], CAN_M3508[i].speed);
        CAN_GM6020[i].set_speed = PID_Calculate(&PID_GM6020[i],Find_MIN_ANGLE_Enconder(chassis_move.setAngle[i]+CAN_GM6020[i].init_angle,CAN_GM6020[i].angle),0);
        CAN_GM6020[i].set_voltage = PID_Calculate(&PID_GM6020_speed[i],CAN_GM6020[i].set_speed,CAN_GM6020[i].speed);
    }
		
}

void steer_calc(chassis_speed_t *speed,chassis_move_t *out) //舵轮解算
{
    float wheel_rpm_ratio;
    float angle_ratio;
    wheel_rpm_ratio = 1/ (WHEEL_DIAMETER * pi) * CHASSIS_DECELE_RATIO*60; //  单位转换系数(m/s -> rpm)
    angle_ratio = (180 / pi) * (8192 / 360);  //单位转换系数(rad -> encoder_num)
	
    out->setSpeed[0] = ( sqrtf(powf(speed->vx - speed->wz * LENGTH_A,2) + powf(speed->vy + speed->wz * LENGTH_B,2)) ) * wheel_rpm_ratio;
    out->setAngle[0] = angle_map(atan2f(speed->vy + speed->wz * LENGTH_B, speed->vx - speed->wz * LENGTH_A)) * angle_ratio ;

    out->setSpeed[1] = ( sqrtf(powf(speed->vx - speed->wz * LENGTH_A,2) + powf(speed->vy - speed->wz * LENGTH_B,2)) ) * wheel_rpm_ratio;
    out->setAngle[1] = angle_map(atan2f(speed->vy - speed->wz * LENGTH_B, speed->vx - speed->wz * LENGTH_A)) * angle_ratio;

    out->setSpeed[2] = ( sqrtf(powf(speed->vx + speed->wz * LENGTH_A,2) + powf(speed->vy - speed->wz * LENGTH_B,2)) ) * wheel_rpm_ratio;
    out->setAngle[2] = angle_map(atan2f(speed->vy - speed->wz * LENGTH_B, speed->vx + speed->wz * LENGTH_A)) * angle_ratio;

    out->setSpeed[3] = ( sqrtf(powf(speed->vx + speed->wz * LENGTH_A,2) + powf(speed->vy + speed->wz * LENGTH_B,2)) ) * wheel_rpm_ratio;
    out->setAngle[3] = angle_map(atan2f(speed->vy + speed->wz * LENGTH_B, speed->vx + speed->wz * LENGTH_A)) * angle_ratio;
}

fp32 Find_MIN_ANGLE_Enconder(float set,float feed)
{
    fp32 temp = set - feed;

    if(temp >=4096)
        temp -= 8192;
    else if(temp < -4096)
        temp += 8192;
    if(temp>2048)  temp-=4096;
    else if(temp<-2048)  temp+=4096;
	
    return temp;
}

void wheel_orientation_init(uint16_t angle1,uint16_t angle2,uint16_t angle3,uint16_t angle4)
{
    CAN_GM6020[0].init_angle = angle1;
    CAN_GM6020[1].init_angle = angle2;
    CAN_GM6020[2].init_angle = angle3;
    CAN_GM6020[3].init_angle = angle4;
}