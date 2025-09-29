#include "outctl_task.h"

uint8_t rc_flag=0,rc_out_time=20;  //num��¼����ʱ��
uint8_t vision_flag=0,vision_out_time=20;  //num��¼����ʱ��

void outctl_task(void const *pvParameters)
{
    //����һ��ʱ��
    osDelay(OUTCTL_TASK_INIT_TIME);
    uint32_t previousWakeTime = osKernelGetTickCount();

    while (1)
    {
        rc_out_time++;
			  vision_out_time++;
			  if(rc_out_time>20) rc_out_time=20;
				if(rc_out_time>10) rc_flag=0;
			  else rc_flag=1;

				if(vision_out_time>20) vision_out_time=20;
				if(vision_out_time>10) vision_flag=0;
			  else vision_flag=1;
			  
        //ϵͳ�����ʱ
        osDelayUntil(previousWakeTime + OUTCTL_TASK_TIME_MS);
    }
}



