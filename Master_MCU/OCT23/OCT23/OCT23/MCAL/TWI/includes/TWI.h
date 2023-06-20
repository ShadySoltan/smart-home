/*
 * TWI.h
 *
 * Created: 5/5/2023 4:18:53 PM
 *  Author: user
 */ 


#ifndef TWI_H_
#define TWI_H_

#include "Clock.h"
#include "TWI_Reg.h"
#include "TWI_Types.h"

#define MyTWPS 1
#define F_TWI 100000UL
#define MyTWBR (((F_CPU/F_TWI)-16)/(2*(4^MyTWPS))) 

void TWI_Init(u8 address);
u8 TWI_Status(void);
u8 TWI_Start(void);
u8 TWI_Send(u8 data);
u8 TWI_Read_Ack(u8 * data);
u8 TWI_Read_NAck(u8 * data);
void TWI_Stop(void);



#endif /* TWI_H_ */