#ifndef __OUTCTL_TASK_H
#define __OUTCTL_TASK_H
#include "main.h"
#include "cmsis_os2.h"

#define OUTCTL_TASK_INIT_TIME   500
#define OUTCTL_TASK_TIME_MS     20

void outctl_task(void const *pvParameters);

extern uint8_t rc_flag;
extern uint8_t rc_out_time; 
extern uint8_t  vision_flag;
extern uint8_t vision_out_time; 

#endif


