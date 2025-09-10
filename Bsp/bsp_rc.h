#ifndef __BSP_RC_H__
#define __BSP_RC_H__

#include "main.h"

#define UART_RX_DMA_SIZE (1024)
#define DBUS_MAX_LEN     (50)
#define DBUS_BUFLEN      (18)
#define DBUS_HUART      huart5

#pragma pack(1)  // 按1字节对齐（即取消对齐）
typedef struct
{
    /* rocker channel information */
    int16_t ch0;
    int16_t ch1;
    int16_t ch2;
    int16_t ch3;
    int16_t ch4;	
    /* left and right lever information */
	uint8_t sw1;
	uint8_t sw2;
	int16_t mouse_x;
	int16_t mouse_y;
	int16_t mouse_z; 
	
	uint8_t mouse_press_l;
	uint8_t mouse_press_r;
	
	uint8_t key[16];
} rc_info_t;
#pragma pack()   // 恢复默认对齐

extern rc_info_t rc;


extern void rc_callback_handler(rc_info_t *rc, uint8_t *buff);
void dbus_uart_init(void);
#endif

