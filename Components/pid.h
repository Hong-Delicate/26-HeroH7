#ifndef _PID_H
#define _PID_H
#include "main.h"

#define fp32 float
enum {
    LLAST	= 0,
    LAST 	= 1,
    NOW 	= 2,

    POSITION_PID,
    DELTA_PID,
};
typedef struct _PID_Typedef
{
	uint8_t mode;
    float Kp;
    float Ki;
    float Kd;
    fp32 max_out;
    fp32 max_iout;

    fp32 set; 
    fp32 fdb;  

    fp32 out;
    fp32 Pout;
    fp32 Iout;
    fp32 Dout;
    fp32 Dbuf[3];  
    fp32 error[3]; 
    float I_Separation; 
    float gama;		
    float lastdout;	
} PID_TypeDef;

extern PID_TypeDef PID_GM6020[2];	
extern PID_TypeDef PID_GM6020_speed[2];
extern PID_TypeDef PID_M2006[2];		
extern PID_TypeDef PID_M2006_speed[2];
extern PID_TypeDef PID_M3508[7];	
extern PID_TypeDef PID_M3508_speed[7]; 
extern PID_TypeDef PID_M3508_Follow;
extern PID_TypeDef PID_DM4310;
extern PID_TypeDef PID_DM4310_speed;


void PID_Init(
    PID_TypeDef*	    pid,
    uint32_t 			mode,
    uint32_t 			maxout,
    uint32_t 			intergral_limit,
    float 				kp,
    float 				ki,
    float 				kd,
	float I_Separation,float gama
);
void PID_Reset(PID_TypeDef	*pid, float kp, float ki, float kd);
float PID_Calculate(PID_TypeDef *pid, float target, float feedback);

	
#endif


