#include "chassis_task.h"
#include "cmsis_os2.h"
#include "main.h"
#include "bsp_fdcan.h"

uint8_t data[8]={20,20,0,0,0,0,0,0};

void chassis_task(void const * argument)
{
    uint32_t previousWakeTime = osKernelGetTickCount();
    osDelay(CHASSIS_TASK_INIT_TIME);
    while (1)
    {
      fdcanx_send_data(&hfdcan3,0x200,data,8);
      osDelayUntil(previousWakeTime + CHASSIS_CONTROL_TIME_MS);
    }
}