/*
* TIMER1.c
*
* Created: 4/13/2023 2:07:57 PM
*  Author: user
*/
#include "TIMER1.h"

void (*Timer1Oc1aIntFunPtr)(void) = 0;
void (*Timer1Oc1bIntFunPtr)(void) = 0;
void (*Timer1TovIntFunPtr)(void) = 0;

void TIMER1_Init(TIMER1_InitTypes * options){
	switch(options->mode){
		case Normal:
		TIMER1_TCCR1A_Reg.WGM10_Bit = 0;
		TIMER1_TCCR1A_Reg.WGM11_Bit = 0;
		TIMER1_TCCR1B_Reg.WGM12_Bit = 0;
		TIMER1_TCCR1B_Reg.WGM13_Bit = 0;
		break;
		case CTC:
		TIMER1_TCCR1A_Reg.WGM10_Bit = 0;
		TIMER1_TCCR1A_Reg.WGM11_Bit = 0;
		TIMER1_TCCR1B_Reg.WGM12_Bit = 1;
		TIMER1_TCCR1B_Reg.WGM13_Bit = 0;
		break;
		case PWM_Fast:
		TIMER1_TCCR1A_Reg.WGM10_Bit = 0;
		TIMER1_TCCR1A_Reg.WGM11_Bit = 1;
		TIMER1_TCCR1B_Reg.WGM12_Bit = 1;
		TIMER1_TCCR1B_Reg.WGM13_Bit = 1;
		break;
		case PWM_Phase_Correct:
		TIMER1_TCCR1A_Reg.WGM10_Bit = 0;
		TIMER1_TCCR1A_Reg.WGM11_Bit = 1;
		TIMER1_TCCR1B_Reg.WGM12_Bit = 0;
		TIMER1_TCCR1B_Reg.WGM13_Bit = 1;
		break;
	}
	switch(options->prescaling){
		case No_Clock:
		TIMER1_TCCR1B_Reg.CS10_Bit = 0;
		TIMER1_TCCR1B_Reg.CS11_Bit = 0;
		TIMER1_TCCR1B_Reg.CS12_Bit = 0;
		break;
		case No_Prescaling:
		TIMER1_TCCR1B_Reg.CS10_Bit = 1;
		TIMER1_TCCR1B_Reg.CS11_Bit = 0;
		TIMER1_TCCR1B_Reg.CS12_Bit = 0;
		break;
		case Clock_8:
		TIMER1_TCCR1B_Reg.CS10_Bit = 0;
		TIMER1_TCCR1B_Reg.CS11_Bit = 1;
		TIMER1_TCCR1B_Reg.CS12_Bit = 0;
		break;
		case Clock_64:
		TIMER1_TCCR1B_Reg.CS10_Bit = 1;
		TIMER1_TCCR1B_Reg.CS11_Bit = 1;
		TIMER1_TCCR1B_Reg.CS12_Bit = 0;
		break;
		case Clock_256:
		TIMER1_TCCR1B_Reg.CS10_Bit = 0;
		TIMER1_TCCR1B_Reg.CS11_Bit = 0;
		TIMER1_TCCR1B_Reg.CS12_Bit = 1;
		break;
		case Clock_1024:
		TIMER1_TCCR1B_Reg.CS10_Bit = 1;
		TIMER1_TCCR1B_Reg.CS11_Bit = 0;
		TIMER1_TCCR1B_Reg.CS12_Bit = 1;
		break;
	}
	switch(options->COM1APWM_mode){
		case COM1A_No_PWM:
		TIMER1_TCCR1A_Reg.COM1A0_Bit = 0;
		TIMER1_TCCR1A_Reg.COM1A1_Bit = 0;
		break;
		case COM1A_Non_Inverting_PWM:
		TIMER1_TCCR1A_Reg.COM1A0_Bit = 0;
		TIMER1_TCCR1A_Reg.COM1A1_Bit = 1;
		break;
		case COM1A_Inverting_PWM:
		TIMER1_TCCR1A_Reg.COM1A0_Bit = 0;
		TIMER1_TCCR1A_Reg.COM1A1_Bit = 0;
		break;
		
	}
	TIMER1_TIMSK_Reg |= ((options->TOVInt_Status)<<2);
}
void TIMER1_OC1AInt_SetCallBack(void (*Timer1Oc1IntCopyFunPtr)(void)){
	Timer1Oc1aIntFunPtr = Timer1Oc1IntCopyFunPtr;
}
void TIMER1_OC1BInt_SetCallBack(void (*Timer1Oc1bIntCopyFunPtr)(void)){
	Timer1Oc1bIntFunPtr = Timer1Oc1bIntCopyFunPtr;
}
void TIMER1_TOVInt_SetCallBack(void (*Timer1TovIntCopyFunPtr)(void)){
	Timer1TovIntFunPtr = Timer1TovIntCopyFunPtr;
}
void TIMER1_OCR1A_SetValue(u16 value){
	TIMER1_OCR1A_Reg = value;
}
void TIMER1_OCR1B_SetValue(u16 value){
	TIMER1_OCR1B_Reg = value;
}
void TIMER1_ICR_SetValue(u16 value){
	TIMER1_ICR1_Reg = value;
}

ISR(TIMER1_COMPA_vect){
	Timer1Oc1aIntFunPtr();
}

ISR(TIMER1_COMPB_vect){
	Timer1Oc1bIntFunPtr();
}

ISR(TIMER1_OVF_vect){
	Timer1TovIntFunPtr();
}
