/*
 * Keypad_Config.h
 *
 * Created: 3/31/2023 2:08:27 PM
 *  Author: user
 */ 


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#include "DIO.h"

#define r0 DIO_ChannelC2
#define r1 DIO_ChannelC3
#define r2 DIO_ChannelC4
#define r3 DIO_ChannelC5

#define c0 DIO_ChannelC6
#define c1 DIO_ChannelC7
#define c2 DIO_ChannelA0
#define c3 DIO_ChannelA1

#define rowsCount 4
#define colsCount 4

u8 keypadRows[rowsCount] = {r0,r1,r2,r3};
u8 keypadCols[colsCount] = {c0,c1,c2,c3};
u8 keypad[rowsCount][colsCount] = {{'7','8','9','/'},
								   {'4','5','6','*'},
								   {'1','2','3','-'},
								   {'C','0','=','+'}};

#endif /* KEYPAD_CONFIG_H_ */