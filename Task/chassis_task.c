#include "chassis_task.h"
#include "cmsis_os2.h"
#include "main.h"

void chassis_task(void const * argument)
{
    osDelay(CHASSIS_TASK_INIT_TIME);
    while (1)
    {
		// Beep(200);
    	osDelay(CHASSIS_CONTROL_TIME_MS);
    }
}