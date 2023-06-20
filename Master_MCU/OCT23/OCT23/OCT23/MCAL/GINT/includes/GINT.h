/*
 * GINT.h
 *
 * Created: 4/1/2023 3:10:18 PM
 *  Author: user
 */ 


#ifndef GINT_H_
#define GINT_H_

#include "STD_Types.h"
#include "GINT_Reg.h"
#include "BitMath.h"

void GINT_EnableAllInterrupts(void);
void GINT_DisableAllInterrupts(void);

#endif /* GINT_H_ */