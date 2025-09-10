/**
 ***************************************(C) COPYRIGHT 2026 DIODE***************************************
 * @file       bsp_beep.c
 * @brief      
 * @note       TIM12 CH2
 * @Version    V1.0.0
 * @Date       2025.8    
 ***************************************(C) COPYRIGHT 20256 DIODE***************************************
 */
#include "bsp_beep.h"
extern TIM_HandleTypeDef htim12;

/* ·äÃùÆ÷Ãù½ÐÒ»¶ÎÊ±¼ä ms */
void Beep(uint16_t ms)
{
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
	__HAL_TIM_SetAutoreload(&htim12,7800-1);
	__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,1785-1);
	HAL_Delay(ms);
	HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2);
}


