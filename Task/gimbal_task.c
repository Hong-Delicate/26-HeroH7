#include "gimbal_task.h"

void gimbal_task(void const *pvParameters)
{
    osDelay(GIMBAL_TASK_INIT_TIME);
    uint32_t previousWakeTime = osKernelGetTickCount();
    while (1)
    {
        
        osDelayUntil(previousWakeTime + GIMBAL_CONTROL_TIME_MS);
    }
}
