/*
 * UART.h
 *
 * Created: 4/28/2023 3:24:39 PM
 *  Author: user
 */ 


#ifndef UART_H_
#define UART_H_

#include "UART_Reg.h"
#include "UART_Types.h"
#include "Clock.h"


void UART_Init(UART_Config * options);
void UART_Transmait(u8 data);
void UART_TransmaitString(s8 * string);
u8 UART_Receive(void);


#endif /* UART_H_ */