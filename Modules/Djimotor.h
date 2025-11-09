#ifndef DJIMOTOR_H
#define DJIMOTOR_H
#include <stdint.h>
#ifdef __cplusplus
 extern "C" {
#endif

typedef struct {
    int16_t  	set_current;	//设定输出电流  (16384 -> 20A)
	float       set_speed;      //设定输出转速  (RPM)
    uint16_t 	angle;	        //反馈角度  (8192 -> 360°)
	int16_t  	last_angle;     //上一时刻反馈角度  (8192 -> 360°)
	float 		total_angle;    //上电后总转角      (8192 -> 360°)
    int16_t 	speed;		    //反馈速度  (RPM)
    int16_t		current;		//反馈电流  (16384 -> 20A)
    uint8_t 	temperature;    //反馈温度  (℃)
} CAN_M3508_TypeDef;



typedef struct
{
    int16_t  	set_voltage;	//设定输出电流  (16384 -> 20A)
	float       set_speed;      //设定输出转速  (RPM)
    uint16_t 	set_angle;      //设定转角  (8192 -> 360°)
    uint16_t    init_angle;     //初始转角  (8192 -> 360°)
    uint16_t 	angle;	        //反馈角度  (8192 -> 360°)
	int16_t  	last_angle;     //上一时刻反馈角度  (8192 -> 360°)
	float 		total_angle;    //上电后总转角      (8192 -> 360°)
    int16_t 	speed;		    //反馈速度  (RPM)
    int16_t		current;		//反馈电流  (16384 -> 20A)
    uint8_t 	temperature;    //反馈温度  (℃)
} CAN_GM6020_TypeDef;


typedef struct
{
    int16_t  	set_current;	//设定输出电流  (16384 -> 20A)
	float       set_speed;      //设定输出转速  (RPM)
    uint16_t 	angle;	        //反馈角度  (8192 -> 360°)
	int16_t  	last_angle;     //上一时刻反馈角度  (8192 -> 360°)
	float 		total_angle;    //上电后总转角      (8192 -> 360°)
    int16_t 	speed;		    //反馈速度  (RPM)
    int16_t		current;		//反馈电流  (16384 -> 20A)
    uint8_t 	temperature;    //反馈温度  (℃)
} CAN_M2006_TypeDef;


extern CAN_GM6020_TypeDef 	CAN_GM6020[];	
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
