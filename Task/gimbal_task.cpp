#include "gimbal_task.h"

/******************************************************************************
* @功能     	: Gimbal任务函数, 负责云台的控制
*/
void gimbal_task(void const *pvParameters)
{
    osDelay(GIMBAL_TASK_INIT_TIME);
    uint32_t previousWakeTime = osKernelGetTickCount();

    RobStrite00.Enable_Motor();
    while (1)
    {
        
        RobStrite00.RobStrite_Motor_move_control(0.5, 0, 0, 0, 0);

        osDelayUntil(previousWakeTime + GIMBAL_CONTROL_TIME_MS);
    }
}

