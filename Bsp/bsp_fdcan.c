#include "bsp_fdcan.h"

/**
************************************************************************
* @brief:      	bsp_can_init(void)
* @param:       void
* @retval:     	void
* @details:    	CAN ʹ��
************************************************************************
**/
void bsp_can_init(void)
{
	FDCAN1_Config();
	FDCAN2_Config();
	FDCAN3_Config();
}

void FDCAN1_Config(void)
{
	FDCAN_FilterTypeDef sFilterConfig;
	/* Configure Rx filter */	
	sFilterConfig.IdType = FDCAN_STANDARD_ID;//��չID������
	sFilterConfig.FilterIndex = 0;
	sFilterConfig.FilterType = FDCAN_FILTER_MASK;
	sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	sFilterConfig.FilterID1 = 0x00000000; // 
	sFilterConfig.FilterID2 = 0x00000000; // 
	if(HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan1, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
	{
		Error_Handler();
	}

	/* ����RX FIFO0���������ж� */
	if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
	{
		Error_Handler();
	}

	/* Start the FDCAN module */
	if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK)
	{
		Error_Handler();
	}
}

void FDCAN2_Config(void)
{
	FDCAN_FilterTypeDef sFilterConfig;
	/* Configure Rx filter */	
	sFilterConfig.IdType = FDCAN_STANDARD_ID;//��չID������
	sFilterConfig.FilterIndex = 1;
	sFilterConfig.FilterType = FDCAN_FILTER_MASK;
	sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	sFilterConfig.FilterID1 = 0x00000000; // 
	sFilterConfig.FilterID2 = 0x00000000; // 
	if(HAL_FDCAN_ConfigFilter(&hfdcan2, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan2, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
	{
		Error_Handler();
	}
	/* ����RX FIFO0���������ж� */
	if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
	{
		Error_Handler();
	}
	/* Start the FDCAN module */
	if (HAL_FDCAN_Start(&hfdcan2) != HAL_OK)
	{
		Error_Handler();
	}
}

void FDCAN3_Config(void)
{
	FDCAN_FilterTypeDef sFilterConfig;
	/* Configure Rx filter */	
	sFilterConfig.IdType = FDCAN_STANDARD_ID;//��չID������
	sFilterConfig.FilterIndex = 2;
	sFilterConfig.FilterType = FDCAN_FILTER_MASK;
	sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	sFilterConfig.FilterID1 = 0x00000000; // 
	sFilterConfig.FilterID2 = 0x00000000; // 
	if(HAL_FDCAN_ConfigFilter(&hfdcan3, &sFilterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_FDCAN_ConfigGlobalFilter(&hfdcan3, FDCAN_REJECT, FDCAN_REJECT, FDCAN_FILTER_REMOTE, FDCAN_FILTER_REMOTE) != HAL_OK)
	{
		Error_Handler();
	}

	/* ����RX FIFO0���������ж� */
	if (HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_FDCAN_ActivateNotification(&hfdcan3, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK)
	{
		Error_Handler();
	}
	/* Start the FDCAN module */
	if (HAL_FDCAN_Start(&hfdcan3) != HAL_OK)
	{
		Error_Handler();
	}
}
/**
************************************************************************
* @brief:      	fdcanx_send_data(FDCAN_HandleTypeDef *hfdcan, uint16_t id, uint8_t *data, uint32_t len)
* @param:       hfdcan��FDCAN���
* @param:       id��CAN�豸ID
* @param:       data�����͵�����
* @param:       len�����͵����ݳ���
* @retval:     	void
* @details:    	��������
************************************************************************
**/
uint8_t fdcanx_send_data(hcan_t *hfdcan, uint16_t id, uint8_t *data, uint32_t len)
{	
    FDCAN_TxHeaderTypeDef pTxHeader;
    pTxHeader.Identifier=id;
    pTxHeader.IdType=FDCAN_STANDARD_ID;
    pTxHeader.TxFrameType=FDCAN_DATA_FRAME;
	
	if(len<=8)
		pTxHeader.DataLength = len;
	if(len==12)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_12;
	if(len==16)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_16;
	if(len==20)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_20;
	if(len==24)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_24;
	if(len==32)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_32;
	if(len==48)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_48;
	if(len==64)
		pTxHeader.DataLength = FDCAN_DLC_BYTES_64;
    pTxHeader.ErrorStateIndicator=FDCAN_ESI_ACTIVE;
    pTxHeader.BitRateSwitch=FDCAN_BRS_ON;
    pTxHeader.FDFormat=FDCAN_CLASSIC_CAN;
    pTxHeader.TxEventFifoControl=FDCAN_NO_TX_EVENTS;
    pTxHeader.MessageMarker=0;
 	while(HAL_FDCAN_GetTxFifoFreeLevel(hfdcan) == 0); // �ȴ��з����������
	if(HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &pTxHeader, data)!=HAL_OK) 	
		return 1;//����
	return 0;	
}
/**
************************************************************************
* @brief:      	fdcanx_receive(FDCAN_HandleTypeDef *hfdcan, uint8_t *buf)
* @param:       hfdcan��FDCAN���
* @param:       buf���������ݻ���
* @retval:     	���յ����ݳ���
* @details:    	��������
************************************************************************
**/

uint8_t fdcanx_receive(hcan_t *hfdcan, uint16_t *rec_id, uint8_t *buf)
{	
	FDCAN_RxHeaderTypeDef pRxHeader;
	uint8_t len;
	
	if(HAL_FDCAN_GetRxMessage(hfdcan,FDCAN_RX_FIFO0, &pRxHeader, buf)==HAL_OK)
	{
		*rec_id = pRxHeader.Identifier;
		if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_8)
			len = pRxHeader.DataLength;
		else if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_12)
			len = 12;
		else if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_16)
			len = 16;
		else if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_20)
			len = 20;
		else if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_24)
			len = 24;
		else if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_32)
			len = 32;
		else if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_48)
			len = 48;
		else if(pRxHeader.DataLength<=FDCAN_DLC_BYTES_64)
			len = 64;
		
		return len;//��������
	}
	return 0;	
}

/**
************************************************************************
* @brief:      	fdcan1_rx_callback(void)
* @param:       void
* @retval:     	void
* @details:    	CAN1���ջص�
************************************************************************
**/
void fdcan1_rx_callback(void)
{
	uint16_t rec_id;
	uint8_t rx_data[8];
	fdcanx_receive(&hfdcan1, &rec_id,(uint8_t *)rx_data);
	if(rec_id == 0x201)
	{
		CAN_M3508[0].angle=(rx_data[0]<<8)+rx_data[1];
		CAN_M3508[0].speed=(rx_data[2]<<8)+rx_data[3];
		CAN_M3508[0].current=(rx_data[4]<<8)+rx_data[5];
		CAN_M3508[0].temperature=(rx_data[6]<<8);
	}
}

void fdcan2_rx_callback(void){
	uint16_t rec_id;
	uint8_t rx_data[8];
	fdcanx_receive(&hfdcan2, &rec_id,(uint8_t *)rx_data);
	if(rec_id == 0x201)
	{
		CAN_M3508[0].angle=(rx_data[0]<<8)+rx_data[1];
		CAN_M3508[0].speed=(rx_data[2]<<8)+rx_data[3];
		CAN_M3508[0].current=(rx_data[4]<<8)+rx_data[5];
		CAN_M3508[0].temperature=(rx_data[6]<<8);
	}
}
void fdcan3_rx_callback(void){
	uint16_t rec_id;
	uint8_t rx_data[8];
	fdcanx_receive(&hfdcan3, &rec_id,(uint8_t *)rx_data);
	if(rec_id == 0x201)
	{
		CAN_M3508[0].angle=(rx_data[0]<<8)+rx_data[1];
		CAN_M3508[0].speed=(rx_data[2]<<8)+rx_data[3];
		CAN_M3508[0].current=(rx_data[4]<<8)+rx_data[5];
		CAN_M3508[0].temperature=(rx_data[6]<<8);
	}
}


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
	{	 
		if(hfdcan == &hfdcan1)
		{
			fdcan1_rx_callback();
		}else	if(hfdcan == &hfdcan2)
		{
			fdcan2_rx_callback();
		}else	if(hfdcan == &hfdcan3)
		{
			fdcan3_rx_callback();
		}
	}
}

  
void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
{
	if((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != RESET)
	{
		if(hfdcan == &hfdcan1)
		{
			fdcan1_rx_callback();
		}else	if(hfdcan == &hfdcan2)
		{
			fdcan2_rx_callback();
		}else	if(hfdcan == &hfdcan3)
		{
			fdcan3_rx_callback();
		}
	}
}
