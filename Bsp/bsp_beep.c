#include "bsp_beep.h"
extern TIM_HandleTypeDef htim12;

void Beep(uint16_t ms)
{
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
	__HAL_TIM_SetAutoreload(&htim12,7800-1);
	__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,1785-1);
	HAL_Delay(ms);
	HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2);
}


