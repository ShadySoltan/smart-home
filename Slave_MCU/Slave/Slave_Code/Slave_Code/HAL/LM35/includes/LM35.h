/*
 * LM35.h
 *
 * Created: 4/7/2023 3:51:38 PM
 *  Author: user
 */ 


#ifndef LM35_H_
#define LM35_H_

#include "ADC.h"

void LM35_Init(ADC_InitTypes * options);
u16 LM35_Read(ADC_ChannelTypes channelId);



#endif /* LM35_H_ */