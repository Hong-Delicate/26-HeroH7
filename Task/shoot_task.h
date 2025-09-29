#ifndef __SHOOT_TASK_H
#define __SHOOT_TASK_H
#include "main.h"
#include "outctl_task.h"
#include "cmsis_os2.h"
#include "dm_motor_drv.h"
#include "bsp_rc.h"
#include "pid.h"

void shoot_task(void const *pvParameters);

#define SHOOT_CONTROL_INIT_TIME  700
#define SHOOT_CONTROL_TIME_MS   10
#endif

