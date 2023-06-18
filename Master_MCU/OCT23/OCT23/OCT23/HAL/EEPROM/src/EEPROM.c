/*
* EEPROM.c
*
* Created: 5/6/2023 2:33:25 PM
*  Author: user
*/
#include "EEPROM.h"

void EEPROM_WriteByte(u8 DeviceAdd,u8 LocAdd,u8 data){
	u8 wDeviceAdd = (DeviceAdd & 0xFE);//to clear the first bit
	if (TWI_Start() == 0x08)
	{
		if (TWI_Send(wDeviceAdd) == 0x18)
		{
			if (TWI_Send(LocAdd) == 0x28)
			{
				if (TWI_Send(data) == 0x28)
				{
					TWI_Stop();
				}
			}
		}
	}
}
u8 EEPROM_ReadByte(u8 DeviceAdd,u8 LocAdd){
	u8 wDeviceAdd = (DeviceAdd & 0xFE);//to clear the first bit to write
	u8 rDeviceAdd = (DeviceAdd | 0x01);//to set the first bit to read
	u8 data = 0;
	if (TWI_Start() == 0x08)
	{
		if (TWI_Send(wDeviceAdd) == 0x18)
		{
			if (TWI_Send(LocAdd) == 0x28)
			{
				if (TWI_Start() == 0x10)
				{
					if (TWI_Send(rDeviceAdd) == 0x40)
					{
						//_delay_ms(50);
						if(TWI_Read_NAck(&data) == 0x58){
							TWI_Stop();
						}
					}
				}
			}
		}
	}
	return data;
}