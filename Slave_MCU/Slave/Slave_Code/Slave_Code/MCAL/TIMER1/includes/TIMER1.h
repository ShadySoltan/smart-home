/*
 * TIMER1.h
 *
 * Created: 4/13/2023 2:07:41 PM
 *  Author: user
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

#include "TIMER1_Reg.h"
#include "TIMER1_Types.h"
#include <avr/interrupt.h>

void TIMER1_Init(TIMER1_InitTypes * options);
void TIMER1_OC1AInt_SetCallBack(void (*Timer1Oc1IntCopyFunPtr)(void));
void TIMER1_OC1BInt_SetCallBack(void (*Timer1Oc1bIntCopyFunPtr)(void));
void TIMER1_TOVInt_SetCallBack(void (*Timer1TovIntCopyFunPtr)(void));
void TIMER1_OCR1A_SetValue(u16 value);
void TIMER1_OCR1B_SetValue(u16 value);
void TIMER1_ICR_SetValue(u16 value);


#endif /* TIMER1_H_ */