/*
 * LM35.c
 *
 * Created: 4/7/2023 3:51:48 PM
 *  Author: user
 */ 
#include "LM35.h"

void LM35_Init(ADC_InitTypes * options){
	ADC_Init(options);
}
u16 LM35_Read(ADC_ChannelTypes channelId){
	u16 readValue = 0;
	u16 temp = 0;
	readValue = ADC_Read(channelId);
	temp = readValue/4;
	return temp;
}