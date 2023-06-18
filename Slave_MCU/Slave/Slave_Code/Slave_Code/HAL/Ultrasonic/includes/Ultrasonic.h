/*
 * Ultrasonic.h
 *
 * Created: 4/15/2023 2:31:06 PM
 *  Author: user
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "TIMER1.h"
#include "GINT.h"
#include "DIO.h"
#include "Clock.h"
#include "util/delay.h"

#define Ultrasonic_Trigger_Pin DIO_ChannelA0
#define Ultrasonic_Echo_Pin DIO_ChannelD6
#define Ultrasonic_ICF1_Bit 5

double Ultrasonic_Read();
void TIMER1_OVHandler();

#endif /* ULTRASONIC_H_ */