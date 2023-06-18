/*
* UART_Types.h
*
* Created: 4/28/2023 3:25:12 PM
*  Author: user
*/


#ifndef UART_TYPES_H_
#define UART_TYPES_H_

#include "STD_Types.h"

#define UCSRC_SelectEnable (1<<7)

typedef struct{
	u8 TXB8_Bit:1;
	u8 RXB8_Bit:1;
	u8 UCSZ2_Bit:1;
	u8 TXEN_Bit:1;
	u8 RXEN_Bit:1;
	u8 UDRIE_Bit:1;
	u8 TXCIE_Bit:1;
	u8 RXCIE_Bit:1;
}UART_UCSRB_Bits;

typedef struct{
	u8 MPCM_Bit:1;
	u8 U2X_Bit:1;
	u8 PE_Bit:1;
	u8 DOR_Bit:1;
	u8 FE_Bit:1;
	u8 UDRE_Bit:1;
	u8 TXC_Bit:1;
	u8 RXC_Bit:1;
}UART_UCSRA_Bits;

typedef struct{
	u8 UCPOL_Bit:1;
	u8 UCSZ0_Bit:1;
	u8 UCSZ1_Bit:1;
	u8 USBS_Bit:1;
	u8 UPM0_Bit:1;
	u8 UPM1_Bit:1;
	u8 UMSEL_Bit:1;
	u8 URSEL_Bit:1;
}UART_UCSRC_Bits;

typedef union{
	u8 AllRegister;
	UART_UCSRA_Bits Bits;
}UCSRA_Types;

typedef union{
	u8 AllRegister;
	UART_UCSRB_Bits Bits;
}UCSRB_Types;

typedef union{
	u8 UCSRC_AllRegister;
	u8 UBRRH_AllRegister;
	UART_UCSRC_Bits UCSRC_Bits;
}UCSRC_UBRRH_Types;

typedef struct{
	u8 UBRRL_Reg;
	UCSRB_Types UCSRB_Reg;
	UCSRA_Types UCSRA_Reg;
	u8 UDR_Reg;
	u8 RESERVED[19];
	UCSRC_UBRRH_Types UCSRC_UBRRH_Reg;
}UART_Registers;

typedef enum{
	Parity_Disable=0,
	Parity_Reserved,
	Parity_Even,
	Parity_Odd
}UART_ParityModeTypes;

typedef enum{
	Stop_1Bit=0,
	Stop_2Bit
}UART_StopBitsTypes;

typedef enum{
	CharacterSize_5Bits=0,
	CharacterSize_6Bits,
	CharacterSize_7Bits,
	CharacterSize_8Bits,
	CharacterSize_Reserved1,
	CharacterSize_Reserved2,
	CharacterSize_Reserved3,
	CharacterSize_9Bits,
}UART_CharacterSizeTypes;

typedef enum{
	BaudRate_2400=2400,
	BaudRate_4800=4800,
	BaudRate_9600=9600,
}UART_BaudRateTypes;

typedef enum{
	TX_Disable=0,
	TX_Enable
}UART_TXTypes;

typedef enum{
	RX_Disable=0,
	RX_Enable
}UART_RXTypes;

typedef enum{
	DoupleSpeed_Disable=0,
	DoupleSpeed_Enable
}UART_DoupleSpeedTypes;

typedef struct{
	UART_BaudRateTypes baudRate;
	UART_DoupleSpeedTypes speedMode;
	UART_CharacterSizeTypes characterSize;
	UART_StopBitsTypes stopBits;
	UART_ParityModeTypes parityMode;
	UART_TXTypes txMode;
	UART_RXTypes rxMode;
}UART_Config;



#endif /* UART_TYPES_H_ */