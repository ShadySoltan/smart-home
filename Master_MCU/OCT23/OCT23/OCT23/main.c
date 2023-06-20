/*
* OCT23.c
*
* Created: 3/17/2023 3:45:07 PM
* Author : user
*/

#include <avr/io.h>
#include <stdlib.h>
#include "BitMath.h"
#include "Clock.h"
#include "STD_Types.h"
#include "DIO.h"
#include "LCD.h"
#include "Keypad.h"
#include "GINT.h"
#include "Ext_Int.h"
#include <avr/interrupt.h>
#include "PWM.h"
#include "ServoMotor.h"
#include "Bluetooth.h"
#include "SPI.h"
#include "TWI.h"
#include "EEPROM.h"
#include "APP.h"


int main(void)
{
	SPI_ConfigTypes options = {Master,MSB,SPIClock_64,DoupleSpeedDisable}; //SPI Config to master
	DIO_Init(); //Initialize DIO with MASTER MCU
	LCD_Init(); //Initialize LCD with MASTER MCU
	Keypad_Init(); //Initialize keypad with MASTER MCU
	TWI_Init(0x66); //Setting Master MCU address "I2C COMM."
	SPI_Init(&options); //Initialize Master SPI
	UART_Config uartconf = {BaudRate_9600,DoupleSpeedDisable,CharacterSize_8Bits,Stop_1Bit,Parity_Disable,TX_Enable,RX_Enable}; //Configure UART
	Bluetooth_Init(&uartconf); //Initialize blue tooth module
	DIO_ConfigChannel(DIO_ChannelD0,Input); //Make RX pin input for receiving 
	_delay_ms(100);
	
	ALARM(); //if alarm not set will proceed to menu1
	DoorCheck();
	goto admin;
	Menu1(); //if passed menu1 will proceed to menu2
	Menu2(); //if passed menu2 will proceed to Main Menu
	
	while (1)
	{
		MainMenu(); //Main menu to control Home
		admin:
		AdminMenu();
	}
}