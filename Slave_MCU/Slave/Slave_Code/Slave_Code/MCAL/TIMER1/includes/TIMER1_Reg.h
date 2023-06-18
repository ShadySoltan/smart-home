/*
 * TIMER1_Reg.h
 *
 * Created: 4/13/2023 2:06:56 PM
 *  Author: user
 */ 


#ifndef TIMER1_REG_H_
#define TIMER1_REG_H_

#include "STD_Types.h"

#define TIMER1_TCCR1A_Reg (*((volatile TIMER1_TCCR1ATypes *)(0x4F)))
#define TIMER1_TCCR1B_Reg (*((volatile TIMER1_TCCR1BTypes *)(0x4E)))
#define TIMER1_OCR1A_Reg (*((volatile u16 *)(0x4A)))
#define TIMER1_OCR1B_Reg (*((volatile u16 *)(0x48)))
#define TIMER1_ICR1_Reg (*((volatile u16 *)(0x46)))
#define TIMER1_TIMSK_Reg (*((volatile u8 *)(0x59)))
#define TIMER1_TIFR_Reg (*((volatile u8 *)(0x58)))
#define TIMER1_TCNT1_Reg (*((volatile u16 *)(0x4C)))

#endif /* TIMER1_REG_H_ */