/*
* TWI_Types.h
*
* Created: 5/5/2023 4:19:25 PM
*  Author: user
*/


#ifndef TWI_TYPES_H_
#define TWI_TYPES_H_

#include "STD_Types.h"

typedef struct{
	u8 TWIE_Bit:1;
	u8 Reserved:1;
	u8 TWEN_Bit:1;
	u8 TWWC_Bit:1;
	u8 TWSTO_Bit:1;
	u8 TWSTA_Bit:1;
	u8 TWEA_Bit:1;
	u8 TWINT_Bit:1;
}TWI_TWCRBits;

typedef union{
	u8 AllRegister;
	TWI_TWCRBits Bits;
}TWI_TWCRTypes;

typedef struct{
	u8 TWBR_Reg;
	u8 TWSR_Reg;
	u8 TWAR_Reg;
	u8 TWDR_Reg;
	u8 Reserved[50];
	TWI_TWCRTypes TWCR_Reg;
}TWI_Registers;


#endif /* TWI_TYPES_H_ */