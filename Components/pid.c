/**
 ***************************************(C) COPYRIGHT 2021 DIODE***************************************
 * @file       pid.c
 * @brief     
 * @note
 * @Version    V1.0.0
 * @Date       2021.5
 ***************************************(C) COPYRIGHT 2021 DIODE***************************************
 */
#include "pid.h"
#include "math.h"
#include "bsp_fdcan.h"
#include "user_lib.h"

PID_TypeDef PID_GM6020[2];
PID_TypeDef PID_GM6020_speed[2];
PID_TypeDef PID_GM6020_PC[2];
PID_TypeDef PID_GM6020_speed_PC[2]; 
PID_TypeDef PID_GM6020_Vision[2];
PID_TypeDef PID_GM6020_speed_Vision[2];
PID_TypeDef PID_M2006[2];		
PID_TypeDef PID_M2006_speed[2];
PID_TypeDef PID_M3508[7];	
PID_TypeDef PID_M3508_speed[7];
PID_TypeDef PID_M3508_Follow;
PID_TypeDef PID_HEAT_PWM;
PID_TypeDef PID_DM4310[1];
PID_TypeDef PID_DM4310_speed[1];


void PID_Reset(PID_TypeDef	*pid, float kp, float ki, float kd)
{
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
}

void PID_Init(
    PID_TypeDef*	pid,
    uint32_t 			mode,
    uint32_t 			maxout,
    uint32_t 			intergral_limit,
    float 				kp,
    float 				ki,
    float 				kd,
	float I_Separation,float gama )
{
    pid->max_iout = intergral_limit;
    pid->max_out = maxout;
    pid->mode = mode;

    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    pid->gama = gama;
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    pid->error[0] = pid->error[1] = pid->error[2] = pid->Pout = pid->Iout = pid->Dout = pid->out = 0.0f;
    pid->I_Separation=I_Separation;
}

float PID_Calculate(PID_TypeDef *pid, float set, float ref)
{
	  uint8_t index;
	    if (pid == NULL)
    {
        return 0.0f;
    }

    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    pid->set = set;
    pid->fdb = ref;
    pid->error[0] = set - ref;
	if(fabs(pid->error[0]) > pid->I_Separation || (pid->error[0]*pid->error[1]) < 0) 
    {
        index = 0;
		pid->Iout = 0;
    }
    else
    {
        index = 1;
    }
    if (pid->mode == POSITION_PID)
    {
        pid->Pout = pid->Kp * pid->error[0];
        pid->Iout += pid->Ki * pid->error[0];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
			
		pid->Dout = pid->Kd * ((1 - pid-> gama) * (pid->Dbuf[0]) + pid-> gama * pid-> lastdout); 
        pid->Iout = abs_limit(pid->Iout, pid->max_iout);
        pid->out = pid->Pout + index*pid->Iout + pid->Dout;
        pid->out = abs_limit(pid->out, pid->max_out);
    }
    else if (pid->mode ==DELTA_PID)	
    {
        pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
        pid->Iout = pid->Ki * pid->error[0];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
        pid->Dout = pid->Kd * pid->Dbuf[0];
        pid->out += pid->Pout + pid->Iout + pid->Dout;
        pid->out = abs_limit(pid->out, pid->max_out);
    }
    return pid->out;
}


