/*
 * ServoMotor.h
 *
 * Created: 4/15/2023 1:44:29 PM
 *  Author: user
 */ 


#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include "TIMER1.h"
#include "DIO.h"

#define MiniAngle 0
#define MaxAngle 180
#define MiniCount 250
#define MaxCount 500

void ServoMotor(u16 angle);

#endif /* SERVOMOTOR_H_ */