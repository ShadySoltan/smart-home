/*
* Slave_Code.c
*
* Created: 5/25/2023 5:35:52 AM
* Author : Administrator
*/

#include "Clock.h"
#include "STD_Types.h"
#include "BitMath.h"
#include "SPI.h"
#include "DIO.h"
#include "LM35.h"
#include "ADC.h"
#include "TIMER1.h"
#include "GINT.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define Led1 '1'
#define Led2 '2'
#define Led3 '3'
#define Led4 '4'
#define Led5 '5'
#define Air_Cond '6'

#define On 'O'
#define Off 'F'

#define Ack 0x01

#define Led1_TurnOn 0x11
#define Led2_TurnOn 0x12
#define Led3_TurnOn 0x13
#define Led4_TurnOn 0x14
#define Led5_TurnOn 0x15
#define Air_Cond_TurnOn 0x16

#define Led1_TurnOff 0x21
#define Led2_TurnOff 0x22
#define Led3_TurnOff 0x23
#define Led4_TurnOff 0x24
#define Led5_TurnOff 0x25
#define Air_Cond_TurnOff 0x26

#define Return_MainMenu 0x99

u8 Air_Cond_Temp_Now = STD_Low; //store the value of temp set by master
u8 Room_Temp_Now = STD_Low;
u8 Air_Cond_Flag = STD_Low; //Check if air cond is on or off


u32 volatile Interrupt_Counter = 0;
void Timer1_OV_Interrupt_Handler(void);

int main(void)
{
	DIO_Init(); //Initialize DIO Pins of Slave MCU
	GINT_EnableAllInterrupts();
	SPI_ConfigTypes SPI_options = {Slave,MSB,SPIClock_64,DoupleSpeedDisable}; //Slave SPI Config Options
	ADC_InitTypes ADC_Options = {ADC_Prescaler64, ADC_Vref_Internal}; //ADC Config Options
	TIMER1_InitTypes Options = {Normal,Clock_64,COM1A_No_PWM,COM1B_No_PWM,OC1AInt_Disable,OC1BInt_Disable,ICInt_Disable, TOVInt_Enable}; //Timer one config for Air Cond On.
	TIMER1_InitTypes Options2 = {Normal,No_Clock,COM1A_No_PWM,COM1B_No_PWM,OC1AInt_Disable,OC1BInt_Disable,ICInt_Disable, TOVInt_Disable};
	SPI_Init(&SPI_options); //Initialize Slave SPI
	LM35_Init(&ADC_Options); //Initialize LM35 Temp. Sensor
	TIMER1_TOVInt_SetCallBack(Timer1_OV_Interrupt_Handler);
	
	
	while (1)
	{
		u8 Received_From_Master = STD_Low;
		u8 Slave_Response;
		
		Received_From_Master = SPI_TxRx(Ack);
		switch(Received_From_Master)
		{
			case Led1:
			if(DIO_ReadChannel(DIO_ChannelA6) == STD_High)
			{
				Slave_Response = On;
			}
			else
			{
				Slave_Response = Off;
			}
			SPI_TxRx(Slave_Response);
			break;
			
			case Led2:
			if(DIO_ReadChannel(DIO_ChannelA7) == STD_High)
			{
				Slave_Response = On;
			}
			else
			{
				Slave_Response = Off;
			}
			SPI_TxRx(Slave_Response);			
			break;
			
			case Led3:
			if(DIO_ReadChannel(DIO_ChannelC0) == STD_High)
			{
				Slave_Response = On;
			}
			else
			{
				Slave_Response = Off;
			}
			SPI_TxRx(Slave_Response);			
			break;
			
			case Led4:
			if(DIO_ReadChannel(DIO_ChannelC1) == STD_High)
			{
				Slave_Response = On;
			}
			else
			{
				Slave_Response = Off;
			}
			SPI_TxRx(Slave_Response);			
			break;
			
			case Led5:
			if(DIO_ReadChannel(DIO_ChannelC2) == STD_High)
			{
				Slave_Response = On;
			}
			else
			{
				Slave_Response = Off;
			}
			SPI_TxRx(Slave_Response);			
			break;
			
			case Air_Cond:
			if(Air_Cond_Flag == STD_High)
			{
				Slave_Response = On;
			}
			else
			{
				Slave_Response = Off;
			}
			SPI_TxRx(Slave_Response);
			break;
			
			case Led1_TurnOn:
			DIO_WriteChannel(DIO_ChannelA6,STD_High);
			break;
			
			case Led1_TurnOff:
			DIO_WriteChannel(DIO_ChannelA6,STD_Low);
			break;
			
			case Led2_TurnOn:
			DIO_WriteChannel(DIO_ChannelA7,STD_High);
			break;
			
			case Led2_TurnOff:
			DIO_WriteChannel(DIO_ChannelA7,STD_Low);
			break;
			
			case Led3_TurnOn:
			DIO_WriteChannel(DIO_ChannelC0,STD_High);
			break;
			
			case Led3_TurnOff:
			DIO_WriteChannel(DIO_ChannelC0,STD_Low);
			break;	
			
			case Led4_TurnOn:
			DIO_WriteChannel(DIO_ChannelC1,STD_High);
			break;
			
			case Led4_TurnOff:
			DIO_WriteChannel(DIO_ChannelC1,STD_Low);
			break;		
			
			case Led5_TurnOn:
			DIO_WriteChannel(DIO_ChannelC2,STD_High);
			break;
			
			case Led5_TurnOff:
			DIO_WriteChannel(DIO_ChannelC2,STD_Low);
			break;
			
			case Air_Cond_TurnOff:
			DIO_WriteChannel(DIO_ChannelD5,STD_Low);
			DIO_WriteChannel(DIO_ChannelD1,STD_Low);
			DIO_WriteChannel(DIO_ChannelD0,STD_Low);
			Air_Cond_Flag = STD_Low;
			TIMER1_Init(&Options2);
			GINT_DisableAllInterrupts();
			Air_Cond_Temp_Now = STD_Low;
			break;
			
			case Air_Cond_TurnOn:
			Air_Cond_Temp_Now = SPI_TxRx(Ack);
			_delay_ms(100);
			TIMER1_Init(&Options);
			GINT_EnableAllInterrupts();
			Air_Cond_Flag = STD_High;
			break;
		}
	}
}

void Timer1_OV_Interrupt_Handler(void){
	Interrupt_Counter++;
	if(Interrupt_Counter == 4)
	{
		Room_Temp_Now = LM35_Read(ADC_Channel1);
		if(Room_Temp_Now >= Air_Cond_Temp_Now)
		{
			DIO_WriteChannel(DIO_ChannelD5,STD_High);
			DIO_WriteChannel(DIO_ChannelD0,STD_High);
			DIO_WriteChannel(DIO_ChannelD1,STD_Low);
			Interrupt_Counter = 0;
		}
		else
		{
			DIO_WriteChannel(DIO_ChannelD5,STD_Low);
			DIO_WriteChannel(DIO_ChannelD0,STD_Low);
			DIO_WriteChannel(DIO_ChannelD1,STD_High);
			Interrupt_Counter = 0;
		}
	}
}
