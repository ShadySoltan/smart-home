/*
* Ultrasonic.c
*
* Created: 4/15/2023 2:31:25 PM
*  Author: user
*/
#include "Ultrasonic.h"

volatile u32 OV_Count = 0;

double Ultrasonic_Read(){
	DIO_ConfigChannel(Ultrasonic_Echo_Pin,Input);
	DIO_ConfigChannel(Ultrasonic_Trigger_Pin,Output);
	GINT_EnableAllInterrupts();
	TIMER1_TOVInt_SetCallBack(TIMER1_OVHandler);
	TIMER1_InitTypes options = {Normal,Clock_64,COM1A_No_PWM,COM1B_No_PWM,OC1AInt_Disable,OC1BInt_Disable,ICInt_Disable,TOVInt_Enable};
	TIMER1_Init(&options);

	TIMER1_TCCR1B_Reg.ICES1_Bit = 1;//Rising Edge
	
	DIO_WriteChannel(Ultrasonic_Trigger_Pin,STD_High);
	_delay_us(10);
	DIO_WriteChannel(Ultrasonic_Trigger_Pin,STD_Low);
	
	while (GetBit(TIMER1_TIFR_Reg,Ultrasonic_ICF1_Bit) == 0);//waiting Rising Edge
	TIMER1_TCNT1_Reg = 0;
	TIMER1_ICR1_Reg = 0;
	OV_Count = 0;
	TIMER1_TCCR1B_Reg.ICES1_Bit = 0;//Falling Edge
	SetBit(TIMER1_TIFR_Reg,Ultrasonic_ICF1_Bit);//Clear the FLag
	
	while (GetBit(TIMER1_TIFR_Reg,Ultrasonic_ICF1_Bit) == 0);//waiting Falling Edge
	SetBit(TIMER1_TIFR_Reg,Ultrasonic_ICF1_Bit);//Clear the FLag
	u32 count = (OV_Count*65536)+TIMER1_ICR1_Reg;
	double distance = (double)0.0686*count;//N=64 , SoundSpeed = 34300 , F_CPU = 16000000
	return distance;
}

void TIMER1_OVHandler(){
	OV_Count++;
}