/*
 * GINT.c
 *
 * Created: 4/1/2023 3:10:30 PM
 *  Author: user
 */ 
#include "GINT.h"

void GINT_EnableAllInterrupts(void){
	SetBit(GINT_SREG_Reg,GINT_SREG_IBit);
}
void GINT_DisableAllInterrupts(void){
	ClearBit(GINT_SREG_Reg,GINT_SREG_IBit);
}