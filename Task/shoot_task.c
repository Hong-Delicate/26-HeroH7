#include "shoot_task.h"

// uint8_t text[8]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC};
uint8_t text[8]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFD};

void shoot_task(void const *pvParameters)
{
    osDelay(SHOOT_CONTROL_INIT_TIME);
    uint32_t previousWakeTime = osKernelGetTickCount();
    
    PID_Init(&PID_DM4310, POSITION_PID, 30, 10, 1, 0, 0.01, 0, 0);			 
	PID_Init(&PID_DM4310_speed,POSITION_PID, 5, 1, 0.08, 0, 0.007, 0, 0); 
    
    dm_motor_init(&DM4310,1,mit_mode);
    // dm_motor_enable(&hfdcan1,&DM4310);
    // dm_motor_disable(&hfdcan1,&DM4310);
    while (1)
    {
        dm_motor_enable(&hfdcan1,&DM4310);
        //fdcanx_send_data(&hfdcan1,0x01,text,8);
        // if(rc_flag)
        // {
        //     switch(rc.sw2)
        //     {
        //         case 1:

        //             break;
        //         case 3:

        //             break;
        //         case 2:

        //             break;
        //     }
        // }
        // else
        // {
        //     DM4310.set.tor = DM4310.set.vel = 0;
        // }
         DM4310.para.tor = DM4310.para.vel = 1;
         dm_motor_ctrl_send(&hfdcan1,&DM4310);

        osDelayUntil(previousWakeTime + SHOOT_CONTROL_TIME_MS);
    }
}
