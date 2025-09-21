#ifndef __BSP_FDCAN_H__
#define __BSP_FDCAN_H__
#include "main.h"
#include "fdcan.h"
#ifdef  __cplusplus
extern "C"
{
#endif
#define hcan_t FDCAN_HandleTypeDef

void bsp_can_init(void);
void FDCAN1_Config(void);
void FDCAN2_Config(void);
void FDCAN3_Config(void);
uint8_t fdcanx_send_data(hcan_t *hfdcan, uint16_t id, uint8_t *data, uint32_t len);
uint8_t fdcanx_receive(hcan_t *hfdcan, uint16_t *rec_id, uint8_t *buf);

#ifdef  __cplusplus
}
#endif
#endif /* __BSP_FDCAN_H_ */

