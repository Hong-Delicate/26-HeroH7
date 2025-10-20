#ifndef __GIMBAL_TASK_H
#define __GIMBAL_TASK_H
#include "main.h"
#include "outctl_task.h"
#include "cmsis_os2.h"
#include "bsp_rc.h"
#include "RobStride.h"

#define GIMBAL_TASK_INIT_TIME 700
#define GIMBAL_CONTROL_TIME_MS 2

#ifdef __cplusplus
extern "C" {  // 确保C++函数能被C代码调用
#endif

void gimbal_task(void const *pvParameters);

#ifdef __cplusplus
}
#endif

#endif


