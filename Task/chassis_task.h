#ifndef __CHASSIS_TASK_H
#define __CHASSIS_TASK_H
#include "main.h"
#include "bsp_rc.h"

#define CHASSIS_TASK_INIT_TIME 200
#define CHASSIS_CONTROL_TIME_MS 10

#ifdef __cplusplus
 extern "C" {
#endif
extern void chassis_task(void const * argument);

#ifdef __cplusplus
 }
#endif
#endif


