/*
 * EEPROM.h
 *
 * Created: 5/6/2023 2:33:10 PM
 *  Author: user
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "TWI.h"
#include "DIO.h"

void EEPROM_WriteByte(u8 DeviceAdd,u8 LocAdd,u8 data);
u8 EEPROM_ReadByte(u8 DeviceAdd,u8 LocAdd);

#endif /* EEPROM_H_ */