/*
* Ext_Int.c
*
* Created: 4/1/2023 3:37:30 PM
*  Author: user
*/
#include "Ext_Int.h"

void (*ExtInt0FunPtr) (void) = 0;
void (*ExtInt1FunPtr) (void) = 0;
void (*ExtInt2FunPtr) (void) = 0;

void Ext_Interrupt_Enable(Ext_Int_Types extIntId){
	switch(extIntId){
		case Ext_INT0:
		SetBit(Ext_Int_GICR_Reg,6);
		break;
		case Ext_INT1:
		SetBit(Ext_Int_GICR_Reg,7);
		break;
		case Ext_INT2:
		SetBit(Ext_Int_GICR_Reg,5);
		break;
	}
}
void Ext_Interrupt_Disable(Ext_Int_Types extIntId){
	switch(extIntId){
		case Ext_INT0:
		ClearBit(Ext_Int_GICR_Reg,6);
		break;
		case Ext_INT1:
		ClearBit(Ext_Int_GICR_Reg,7);
		break;
		case Ext_INT2:
		ClearBit(Ext_Int_GICR_Reg,5);
		break;
	}
}
void Ext_Interrupt_Sncontrol(Ext_Int_Types extIntId,Ext_Int_SncTypes mode){
	switch(extIntId){
		case Ext_INT0:
		Ext_Int_MCUCR_Reg |= (mode<<0);
		break;
		case Ext_INT1:
		Ext_Int_MCUCR_Reg |= (mode<<2);
		break;
		case Ext_INT2:
		if (mode == Falling_Edge)
		{
			ClearBit(Ext_Int_MCUCSR_Reg,6);
		}
		else if(mode == Rising_Edge)
		{
			SetBit(Ext_Int_MCUCSR_Reg,6);
		}
		else{
			//Do Nothing
		}
		break;
	}
}
void Ext_Interrupt_SetCallBack(Ext_Int_Types extIntId, void (*ExtIntCopyPtr)(void)){
	switch(extIntId){
		case Ext_INT0:
		ExtInt0FunPtr = ExtIntCopyPtr;
		break;
		case Ext_INT1:
		ExtInt1FunPtr = ExtIntCopyPtr;
		break;
		case Ext_INT2:
		ExtInt2FunPtr = ExtIntCopyPtr;
		break;
	}
}


ISR(INT0_vect){
	ExtInt0FunPtr();
}

ISR(INT1_vect){
	ExtInt1FunPtr();
}

ISR(INT2_vect){
	ExtInt2FunPtr();
}