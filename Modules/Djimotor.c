#include "Djimotor.h"
#define __fabs(v)  v > 0 ? v:-v 
uint32_t CAN2_CNT = 0;

CAN_GM6020_TypeDef 	CAN_GM6020[6];	
CAN_M2006_TypeDef 	CAN_M2006[1];
CAN_M3508_TypeDef 	CAN_M3508[6];


void get_total_angle(CAN_M3508_TypeDef *p) {

    int res1, res2;
    float delta;
    if(p->angle < p->last_angle) {				
        res1 = p->angle + 8192 - p->last_angle;		
        res2 = p->angle - p->last_angle;		
    } 
	else {	//angle > last
        res1 = p->angle - 8192 - p->last_angle ;		
        res2 = p->angle - p->last_angle;			
    }
  
    if(__fabs(res1)<__fabs(res2))
        delta = res1;
    else
        delta = res2;

    p->total_angle += delta*0.0520746310219f;
    p->last_angle = p->angle;
}
void get_total_angle_2006(CAN_M2006_TypeDef *p) {

    int res1, res2;
    float delta;
    if(p->angle < p->last_angle) {						
        res1 = p->angle + 8192 - p->last_angle;			
        res2 = p->angle - p->last_angle;				
    } 
	else {	//angle > last
        res1 = p->angle - 8192 - p->last_angle ;		
        res2 = p->angle - p->last_angle;			
    }
   
    if(__fabs(res1)<__fabs(res2))
        delta = res1;
    else
        delta = res2;

    p->total_angle += delta*0.001220703125f;
    p->last_angle = p->angle;
}
void get_total_angle_6020(CAN_GM6020_TypeDef *p) {

    int res1, res2;
    float delta;
    if(p->angle < p->last_angle) {						
        res1 = p->angle + 8192 - p->last_angle;			
        res2 = p->angle - p->last_angle;				
    } 
	else {	
        res1 = p->angle - 8192 - p->last_angle ;	
        res2 = p->angle - p->last_angle;				
    }
    if(__fabs(res1)<__fabs(res2))
	{
		delta = res1;		
	}
    else
        delta = res2;
    p->total_angle += delta;
    p->last_angle = p->angle;
}

