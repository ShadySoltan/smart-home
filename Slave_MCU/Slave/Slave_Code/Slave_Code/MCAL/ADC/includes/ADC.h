/*
 * ADC.h
 *
 * Created: 4/7/2023 2:54:11 PM
 *  Author: user
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "BitMath.h"
#include "ADC_Reg.h"
#include "ADC_Types.h"

void ADC_Init(ADC_InitTypes * options);
u16 ADC_Read(ADC_ChannelTypes channelId);

#endif /* ADC_H_ */