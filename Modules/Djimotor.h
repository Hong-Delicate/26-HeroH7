#ifndef DJIMOTOR_H
#define DJIMOTOR_H
#include <stdint.h>
#ifdef __cplusplus
 extern "C" {
#endif


/* ����3508״̬�ṹ�壬�洢��ǰ3508�ķ���ֵ*/
typedef struct {
    int16_t  	set_current;	// д����ڻ��������
		float set_speed;  //�⻷������ٶ�
    uint16_t 	angle;			// �Ƕ�
	  int16_t  	last_angle;
	  float 		total_angle;
    int16_t 	speed;			// �ٶ�
    int16_t		current;		// ����
    uint8_t 	temperature;	// �¶�
} CAN_M3508_TypeDef;


/* ����6020״̬�ṹ�壬�洢��ǰ6020�ķ���ֵ*/
typedef struct
{
  int16_t  set_voltage;	// д����ڻ������ѹ
	float set_angle_speed;//�⻷����Ľ��ٶ�
  int16_t angle;			// �Ƕ�
	int16_t  	last_angle;
	float 		total_angle;
  int16_t  speed;         // �ٶ�
  int16_t  current;       // ����
  int8_t  temperature;   // �¶�

} CAN_GM6020_TypeDef;

/* ����2006״̬�ṹ�壬�洢��ǰ6020�ķ���ֵ*/
typedef struct
{
    int16_t  set_current;	// д��ĵ���
    uint16_t angle;			// �Ƕ�
	int16_t  	last_angle;
	float 		total_angle;
    int16_t  speed;         // �ٶ�
    int16_t  current;       // ����
    uint8_t  temperature;   // �¶�
} CAN_M2006_TypeDef;

/******************** �������ID ����***********************/
#define	CAN1_M3508_ID1 0x201	// ���̵��0   
#define	CAN1_M3508_ID2 0x202	// ���̵��1
#define	CAN1_M3508_ID3 0x203	// ���̵��2
#define	CAN1_M3508_ID4 0x204	// ���̵��3
#define CAN1_GM6020_ID1  0x205	// ��̨yaw���            

#define CAN2_GM6020_ID1  0x205	// ��̨pitch���
#define	CAN2_M3508_ID2  0x202	// Ħ���ֵ�� ��3
#define	CAN2_M3508_ID3  0x203	// Ħ���ֵ�� ��4
#define CAN2_M2006_ID1  0x201	// ���̵��
/**********************************************************/

extern CAN_GM6020_TypeDef 	CAN_GM6020[];	// ��̨���
extern CAN_M2006_TypeDef 	CAN_M2006[];
extern CAN_M3508_TypeDef 	CAN_M3508[];
void get_total_angle(CAN_M3508_TypeDef *p);
void get_total_angle_2006(CAN_M2006_TypeDef *p);
void get_total_angle_6020(CAN_GM6020_TypeDef *p);
void Djimotor_Callback(uint16_t id,uint8_t rx_data[]);
#ifdef __cplusplus
 }
#endif
#endif /*DJIMOTOR_H*/
