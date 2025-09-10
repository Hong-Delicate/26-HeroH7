/**
 ***************************************(C) COPYRIGHT 2021 DIODE***************************************
 * @file       bsp_rc.c
 * @brief      this file contains rc data receive and processing function
 * @note       USART1 + DMA2 stream2
 * @Version    V1.0.0
 * @Date       2021.5
 ***************************************(C) COPYRIGHT 2021 DIODE***************************************
 */
#include "bsp_rc.h"
#include "usart.h"
#include <string.h>
#include  <stdlib.h>

uint8_t   dbus_buf[DBUS_BUFLEN];
rc_info_t rc,rc_last;

void rc_callback_handler(rc_info_t *rc, uint8_t *buff)
{
	rc->ch0 = (buff[0] | buff[1] << 8) & 0x07FF;
	rc->ch0 -= 1024;
	rc->ch1 = (buff[1] >> 3 | buff[2] << 5) & 0x07FF;
	rc->ch1 -= 1024;
	rc->ch2 = (buff[2] >> 6 | buff[3] << 2 | buff[4] << 10) & 0x07FF;
	rc->ch2 -= 1024;
	rc->ch3 = (buff[4] >> 1 | buff[5] << 7) & 0x07FF;
	rc->ch3 -= 1024;
	rc->ch4 = (buff[16] | buff[17] << 8) & 0x07FF;
	rc->ch4 -= 1024;

	rc->sw1 = ((buff[5] >> 4) & 0x000C) >> 2;
	rc->sw2 = (buff[5] >> 4) & 0x0003;

	rc->mouse_x = ((int16_t)buff[6]) | ((int16_t)buff[7] << 8);
	rc->mouse_y = ((int16_t)buff[8]) | ((int16_t)buff[9] << 8);
	rc->mouse_z = ((int16_t)buff[10]) | ((int16_t)buff[11] << 8); 

	rc->mouse_press_l = buff[12];
	rc->mouse_press_r = buff[13];

	rc->key[15]=(buff[15]&0x80)>>7; 
	rc->key[14]=(buff[15]&0x40)>>6; 
	rc->key[13]=(buff[15]&0x20)>>5;
	rc->key[12]=(buff[15]&0x10)>>4;
	rc->key[11]=(buff[15]&0x08)>>3;
	rc->key[10]=(buff[15]&0x04)>>2;
	rc->key[9]=(buff[15]&0x02)>>1;
	rc->key[8]=	buff[15]&0x01;
	rc->key[7]=(buff[14]&0x80)>>7;
	rc->key[6]=(buff[14]&0x40)>>6;
	rc->key[5]=(buff[14]&0x20)>>5;
	rc->key[4]=(buff[14]&0x10)>>4;
	rc->key[3]=(buff[14]&0x08)>>3;
	rc->key[2]=(buff[14]&0x04)>>2;
	rc->key[1]=(buff[14]&0x02)>>1;
	rc->key[0]=	buff[14]&0x01;


	if ((abs(rc->ch0) > 660) || (abs(rc->ch1) > 660) || (abs(rc->ch2) > 660) || (abs(rc->ch3) > 660))
	{
		memset(rc, 0, sizeof(rc_info_t));
	}
		
}

void dbus_uart_init(void)
{
	HAL_UART_Receive_DMA(&huart5,dbus_buf,DBUS_BUFLEN);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    rc_callback_handler(&rc,dbus_buf);
	HAL_UART_Receive_DMA(&huart5,dbus_buf,DBUS_BUFLEN);
}




