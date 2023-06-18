/*
 * ADC.c
 *
 * Created: 4/7/2023 3:18:19 PM
 *  Author: user
 */ 
#include "ADC.h"

void ADC_Init(ADC_InitTypes * options){
	ADC_ADMUX_Reg = ((options->adcVref)<<6);//set VREF -> 2.56v
	ADC_ADCSRA_Reg = (1<<ADC_ADCSRA_ADEN_Bit)|(options->adcClock);//enable ADC & Prescaler
}
u16 ADC_Read(ADC_ChannelTypes channelId){
	u16 readValue = 0;
	ADC_ADMUX_Reg = (ADC_ADMUX_Reg & 0b11100000)|(channelId & 0b00011111);
	SetBit(ADC_ADCSRA_Reg,ADC_ADCSRA_ADSC_Bit);//Start ADC Conv.
	while (GetBit(ADC_ADCSRA_Reg,ADC_ADCSRA_ADIF_Bit) == 0);//waiting for ADC to End  
	SetBit(ADC_ADCSRA_Reg,ADC_ADCSRA_ADIF_Bit);//clear the flag
	readValue = (ADC_ADCL_Reg)|(ADC_ADCH_Reg<<8);
	return readValue;
}