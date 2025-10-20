#include "chassis_task.h"
#include "cmsis_os2.h"
#include "main.h"
#include "bsp_fdcan.h"
#include "usbd_cdc_if.h"

uint8_t data[8]={0,0,0,0,0,0,0,0};

void chassis_task(void const * argument)
{
    osDelay(CHASSIS_TASK_INIT_TIME);
    uint32_t previousWakeTime = osKernelGetTickCount();
    while (1)
    {
        CDC_Transmit_HS((uint8_t *)"Hello!\n",7);
//      fdcanx_send_data(&hfdcan1,0x200,data,8);
        osDelayUntil(previousWakeTime + CHASSIS_CONTROL_TIME_MS);
    }
}