/*
 * ServoMotor.c
 *
 * Created: 4/15/2023 1:44:42 PM
 *  Author: user
 */ 
#include "ServoMotor.h"

void ServoMotor(u16 angle){
	DIO_ConfigChannel(DIO_ChannelD5,Output);
	u16 ICR_Value = (u16)4999;
	u16 OCR1A_Value = (u16)(((angle-MiniAngle)*((float)(MaxCount-MiniCount)/(MaxAngle-MiniAngle)))+MiniCount-1);
	TIMER1_ICR_SetValue(ICR_Value);
	TIMER1_OCR1A_SetValue(OCR1A_Value);
	TIMER1_InitTypes options = {PWM_Fast,Clock_64,COM1A_Non_Inverting_PWM,COM1B_No_PWM,OC1AInt_Disable,OC1BInt_Disable,ICInt_Disable,TOVInt_Disable};
	TIMER1_Init(&options);
}