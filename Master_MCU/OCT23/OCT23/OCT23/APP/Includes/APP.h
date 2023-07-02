/*
 * APP.h
 *
 * Created: 5/31/2023 8:29:41 AM
 *  Author: Administrator
 */ 


#ifndef APP_H_
#define APP_H_
#include "BitMath.h"
#include "DIO.h"
#include "LCD.h"
#include "STD_Types.h"
#include "Keypad.h"
#include "Bluetooth.h"
#include "SPI.h"
#include "TWI.h"
#include "ServoMotor.h"
#include "EEPROM.h"

#define PASSWORD_LENGTH 4
#define USER_PASS_LOC 0b10100000
#define USER2_PASS_LOC 0b10101000
#define PASSWORD_TRIALS 3
#define ALARM_LOC 0b10100010
#define DOOR_Status_Loc 0b10100100

u8 Password_Exist(u8 location);
void getPassword(u8 location, s8* Store);
void Menu1(u8 location);
void Menu2(u8 location);
void MainMenu(u8 location);
void ALARM(void);
void AdminMenu(void);

//Main Menu Functions
void Door(void); //Check if door is open or closed
void DoorCheck(void);
void ROOM1(u8 location);
void ROOM2(u8 location);
void ChooseUser(void);

//Admin MoreMenu More Options
u8 Users_Count(void);
void Register(void);

//SPI Design
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


#endif /* APP_H_ */