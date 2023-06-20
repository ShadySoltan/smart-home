/*
* TWI.c
*
* Created: 5/5/2023 4:19:41 PM
*  Author: user
*/
#include "TWI.h"

void TWI_Init(u8 address){
	TWI->TWAR_Reg = address;
	TWI->TWBR_Reg = MyTWBR;
}
u8 TWI_Status(void){
	return (TWI->TWSR_Reg & 0xF8);
}
u8 TWI_Start(void){
	TWI->TWCR_Reg.Bits.TWSTA_Bit = 1;//Enable/Disable Start
	TWI->TWCR_Reg.Bits.TWSTO_Bit = 0;//Enable/Disable Stop at the End
	TWI->TWCR_Reg.Bits.TWEA_Bit = 0;//Read with Ack. Bit
	TWI->TWCR_Reg.Bits.TWEN_Bit = 1;//Enable TWI
	TWI->TWCR_Reg.Bits.TWINT_Bit = 1;//Clear The Flag
	while(TWI->TWCR_Reg.Bits.TWINT_Bit == 0);//Waiting the flag
	return TWI_Status();
}
u8 TWI_Send(u8 data){
	TWI->TWDR_Reg = data;
	TWI->TWCR_Reg.Bits.TWSTA_Bit = 0;//Enable/Disable Start
	TWI->TWCR_Reg.Bits.TWSTO_Bit = 0;//Enable/Disable Stop at the End
	TWI->TWCR_Reg.Bits.TWEA_Bit = 0;//Read with Ack. Bit
	TWI->TWCR_Reg.Bits.TWEN_Bit = 1;//Enable TWI
	TWI->TWCR_Reg.Bits.TWINT_Bit = 1;//Clear The Flag
	while(TWI->TWCR_Reg.Bits.TWINT_Bit == 0);//Waiting the flag
	return TWI_Status();
}
u8 TWI_Read_Ack(u8 * data){
	TWI->TWCR_Reg.Bits.TWSTA_Bit = 0;//Enable/Disable Start
	TWI->TWCR_Reg.Bits.TWSTO_Bit = 0;//Enable/Disable Stop at the End
	TWI->TWCR_Reg.Bits.TWEA_Bit = 1;//Read with Ack. Bit
	TWI->TWCR_Reg.Bits.TWEN_Bit = 1;//Enable TWI
	TWI->TWCR_Reg.Bits.TWINT_Bit = 1;//Clear The Flag
	while(TWI->TWCR_Reg.Bits.TWINT_Bit == 0);//Waiting the flag
	*data = TWI->TWDR_Reg;
	return TWI_Status();
}
u8 TWI_Read_NAck(u8 * data){
	TWI->TWCR_Reg.Bits.TWSTA_Bit = 0;//Enable/Disable Start
	TWI->TWCR_Reg.Bits.TWSTO_Bit = 0;//Enable/Disable Stop at the End
	TWI->TWCR_Reg.Bits.TWEA_Bit = 0;//Read with Ack. Bit
	TWI->TWCR_Reg.Bits.TWEN_Bit = 1;//Enable TWI
	TWI->TWCR_Reg.Bits.TWINT_Bit = 1;//Clear The Flag
	while(TWI->TWCR_Reg.Bits.TWINT_Bit == 0);//Waiting the flag
	*data = TWI->TWDR_Reg;
	return TWI_Status();
}
void TWI_Stop(void){
	TWI->TWCR_Reg.Bits.TWSTA_Bit = 0;//Enable/Disable Start
	TWI->TWCR_Reg.Bits.TWSTO_Bit = 1;//Enable/Disable Stop at the End
	TWI->TWCR_Reg.Bits.TWEA_Bit = 0;//Read with Ack. Bit
	TWI->TWCR_Reg.Bits.TWEN_Bit = 1;//Enable TWI
	TWI->TWCR_Reg.Bits.TWINT_Bit = 1;//Clear The Flag
}