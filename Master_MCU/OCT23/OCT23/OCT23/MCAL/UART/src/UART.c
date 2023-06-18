/*
 * UART.c
 *
 * Created: 4/28/2023 3:23:54 PM
 *  Author: user
 */ 
#include "UART.h"

void UART_Init(UART_Config * options){
	u16 MyUBRR = 0;
	if (options->speedMode == DoupleSpeed_Enable)
	{
		UART->UCSRA_Reg.Bits.U2X_Bit = 1;
		MyUBRR = (F_CPU/(8UL*options->baudRate))-1;
	} 
	else
	{
		UART->UCSRA_Reg.Bits.U2X_Bit = 0;
		MyUBRR = (F_CPU/(16UL*options->baudRate))-1;
	}
	UART->UBRRL_Reg = MyUBRR;
	UART->UCSRC_UBRRH_Reg.UBRRH_AllRegister = MyUBRR>>8;
	
	if (options->characterSize == CharacterSize_9Bits)
	{
		UART->UCSRC_UBRRH_Reg.UCSRC_Bits.UCSZ0_Bit = 1;
		UART->UCSRC_UBRRH_Reg.UCSRC_Bits.UCSZ1_Bit = 1;
		UART->UCSRB_Reg.Bits.UCSZ2_Bit = 1;
	} 
	else
	{
		UART->UCSRC_UBRRH_Reg.UCSRC_AllRegister |= (UCSRC_SelectEnable)|(options->characterSize<<1);
	}
	UART->UCSRC_UBRRH_Reg.UCSRC_AllRegister |= (UCSRC_SelectEnable)|(options->stopBits<<3);
	UART->UCSRC_UBRRH_Reg.UCSRC_AllRegister |= (UCSRC_SelectEnable)|(options->parityMode<<4);
	UART->UCSRB_Reg.Bits.TXEN_Bit = options->txMode;
	UART->UCSRB_Reg.Bits.RXEN_Bit = options->rxMode;
}
void UART_Transmait(u8 data){
	while(UART->UCSRA_Reg.Bits.UDRE_Bit == 0);
	UART->UDR_Reg = data;
}
void UART_TransmaitString(s8 * string){
	u8 i = 0;
	while(string[i] != '\0'){
		UART_Transmait(string[i]);
		i++;
	}
}
u8 UART_Receive(void){
	while (UART->UCSRA_Reg.Bits.RXC_Bit == 0);
	return UART->UDR_Reg;
}