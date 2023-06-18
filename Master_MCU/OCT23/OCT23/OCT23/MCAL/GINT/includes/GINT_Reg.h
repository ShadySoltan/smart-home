/*
 * GINT_Reg.h
 *
 * Created: 4/1/2023 3:10:07 PM
 *  Author: user
 */ 


#ifndef GINT_REG_H_
#define GINT_REG_H_

#include "STD_Types.h"

#define GINT_SREG_IBit 7

#define GINT_SREG_Reg (*((volatile u8 *)(0x5F)))

#endif /* GINT_REG_H_ */