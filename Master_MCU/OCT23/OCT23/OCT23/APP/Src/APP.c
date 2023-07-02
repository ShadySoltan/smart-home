/*
* APP.c
*
* Created: 5/31/2023 8:29:53 AM
*  Author: Administrator
*/
#include "APP.h"

/*************************************************************
Custom Characters / Symbols
*************************************************************/

s8 customChar[] = {
	0x07,
	0x05,
	0x07,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00
}; //Degree Symbol for LCD

/*************************************************************
Check Password Existence Function
*************************************************************/

u8 Password_Exist(u8 location)
{
	u8 passWord[PASSWORD_LENGTH] = {STD_Low}, password_counter = 0;
	
	for(u8 i = 0 ; i < PASSWORD_LENGTH; i++)
	{
		passWord[i] = EEPROM_ReadByte(location,i);
	}
	
	for(u8 i = 0 ; i < PASSWORD_LENGTH; i++)
	{
		if(passWord[i] == 0xFF)
		{
			password_counter++;
		}
	}
	
	if(password_counter == 4)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*************************************************************
Get Saved Password from EEPROM Function
*************************************************************/

void getPassword(u8 location, s8* Store)
{
	for(u8 i = 0; i < PASSWORD_LENGTH; i++)
	{
		Store[i] = EEPROM_ReadByte(location,i);
		_delay_ms(50);
	}
}

/*************************************************************
Registration Menu Function
*************************************************************/
void Menu1(u8 location)
{
	LCD_Clear();
	_delay_ms(30);
	LCD_SetPos(1,2);
	LCD_String("Smart - Home");
	LCD_SetPos(2,4);
	LCD_String("Project!");
	_delay_ms(400);
	LCD_Clear();
	
	if(Password_Exist(location) == 0)
	{
		s8 Password_User[PASSWORD_LENGTH] = {STD_Low};
		s8 Password_Confirm[PASSWORD_LENGTH] = {STD_Low};
		
		LCD_String("Login first time");
		_delay_ms(400);
		LCD_Clear();
		
		RetryPassword:LCD_String("SetPassword:");
		if(location == USER_PASS_LOC)
		{
			LCD_SetPos(2,0);
			LCD_String("*****USER1*****");
			LCD_SetPos(1,12);
		}
		else if (location == USER2_PASS_LOC)
		{
			LCD_SetPos(2,0);
			LCD_String("*****USER2*****");	
			LCD_SetPos(1,12);		
		}
		u8 Password_Counter = 0;
		while(Password_Counter<PASSWORD_LENGTH)
		{
			u8 keypad = STD_Low;
			keypad = GetKey();
			if(keypad != STD_Low)
			{
				LCD_Char(keypad);
				_delay_ms(50);
				LCD_SetPos(1,12+Password_Counter);
				LCD_Char('*');
				Password_User[Password_Counter] = keypad;
				Password_Counter++;
			}
		}
		
		LCD_Clear();
		LCD_String("Confirm:");
		Password_Counter = 0;
		while(Password_Counter<PASSWORD_LENGTH)
		{
			u8 keypad = STD_Low;
			keypad = GetKey();
			if(keypad != STD_Low)
			{
				LCD_Char(keypad);
				_delay_ms(50);
				LCD_SetPos(1,8+Password_Counter);
				LCD_Char('*');
				Password_Confirm[Password_Counter] = keypad;
				Password_Counter++;
			}
		}
		
		Password_Counter = 0;
		LCD_Clear();
		for(u8 i = 0; i < PASSWORD_LENGTH; i++)
		{
			if(Password_User[i] == Password_Confirm[i])
			{
				Password_Counter++;
			}
		}
		
		if(Password_Counter == 4)
		{
			for(u8 i = 0; i < PASSWORD_LENGTH; i++)
			{
				EEPROM_WriteByte(location,i,Password_User[i]);
				_delay_ms(200);
			}
			LCD_String("Password Saved!");
			_delay_ms(400);
			LCD_Clear();
			Bluetooth_TransmaitString("\nUser Registered successfully!");
			AdminMenu();
		}
		else
		{
			LCD_String("Pass mismatch!");
			_delay_ms(200);
			LCD_SetPos(2,0);
			LCD_String("Try again!");
			_delay_ms(200);
			LCD_Clear();
			goto RetryPassword;
		}
	}
	else
	{
		//Already have an account
		//Greetings
		LCD_Clear();
		LCD_SetPos(1,2);
		LCD_String("Welcome Home");
		_delay_ms(400);
		LCD_Clear();
		Menu2(location);
	}
}

/*************************************************************
Login Menu Function
*************************************************************/
void Menu2(u8 location)
{
	s8 Password_User[PASSWORD_LENGTH] = {STD_Low};
	s8 SavedPassword[PASSWORD_LENGTH] = {STD_Low};
	u8 password_trials = 0;
	s8 LCD_TRIALS_CHAR = '3';
	u8 Password_Counter = 0;
	
	getPassword(location,SavedPassword);
	_delay_ms(50);
	
	Retry://If Entered Password wrong return here
	Password_Counter = 0;
	LCD_Clear();
	LCD_String("Password:");
	LCD_SetPos(2,0);
	if(location == USER_PASS_LOC)
	{
		LCD_String("*****USER1*****");
	}
	else if (location == USER2_PASS_LOC)
	{
		LCD_String("*****USER2*****");
	}
	else
	{
		//Do nothing
	}
	LCD_SetPos(1,9);
	
	while(Password_Counter<PASSWORD_LENGTH)
	{
		u8 keypad = STD_Low;
		keypad = GetKey();
		if(keypad != STD_Low)
		{
			LCD_Char(keypad);
			_delay_ms(50);
			LCD_SetPos(1,9+Password_Counter);
			LCD_Char('*');
			Password_User[Password_Counter] = keypad;
			Password_Counter++;
		}
	}
	
	Password_Counter = 0;
	for(u8 i = 0; i < PASSWORD_LENGTH; i++)
	{
		if(SavedPassword[i] == Password_User[i])
		{
			Password_Counter++;
		}
	}
	
	if(Password_Counter == 4)
	{
		LCD_Clear();
		LCD_String("Correct Password!");
		_delay_ms(400);
		LCD_SetPos(2,0);
		LCD_String("!HomeSweetHome!");
		_delay_ms(500);
		LCD_Clear();
		MainMenu(location);
	}
	else
	{
		LCD_Clear();
		LCD_String("Wrong Password!");
		password_trials++;
		LCD_TRIALS_CHAR--;
		if(password_trials == PASSWORD_TRIALS)
		{
			LCD_Clear();
			LCD_String("System Blocked!");
			LCD_SetPos(2,0);
			LCD_String("Firing Alarm!!!");
			Bluetooth_TransmaitString("Alarm triggered!");
			EEPROM_WriteByte(ALARM_LOC,0,'1');
			_delay_ms(50);
			DIO_WriteChannel(DIO_ChannelB0,STD_High);
			_delay_ms(400);
			ALARM();
		}
		else
		{
			LCD_SetPos(2,0);
			LCD_String("Trials left: ");
			LCD_Char(LCD_TRIALS_CHAR);
			_delay_ms(400);
			LCD_Clear();
			goto Retry;
		}
	}
}

/*************************************************************
Checking & Firing Alarm Function
*************************************************************/

void ALARM(void)
{
	if(EEPROM_ReadByte(ALARM_LOC,0) != 0xFF)
	{
		while(1)
		{
			LCD_Clear();
			LCD_String("ALARM!!!!");
			_delay_ms(200);
			LCD_Clear();
			DIO_WriteChannel(DIO_ChannelB0,STD_High);
		}
	}
	else
	{
		//Do Nothing
	}

}

/*************************************************************
User Control Main Menu
*************************************************************/

void MainMenu(u8 location) //Main App Menu
{
	u8 PressKey = STD_Low;
	LCD_Clear();
	LCD_String("1:ROOM1  2:ROOM2");
	LCD_SetPos(2,0);
	LCD_String("3:Admin  4:Lock");
	
	while(PressKey == STD_Low){
		PressKey = GetKey(); //Wait for user Input
		if(PressKey != STD_Low)
		{
			switch(PressKey)
			{
				case '1':
				LCD_Clear();
				PressKey = STD_Low;
				ROOM1(location);
				break;
				
				case '2':
				LCD_Clear();
				PressKey = STD_Low;
				ROOM2(location);
				break;
				
				case '3':
				LCD_Clear();
				PressKey = STD_Low;
				AdminMenu();
				break;
				
				case '4':
				LCD_Clear();
				PressKey = STD_Low;
				LCD_String("Locking System...");
				_delay_ms(200);
				LCD_SetPos(2,0);
				LCD_String("System Locked");
				_delay_ms(200);
				Menu2(location);
				break;
				
				default:
				LCD_Clear();
				LCD_String("Wrong Choice!");
				_delay_ms(400);
				LCD_Clear();
				MainMenu(location);
				break;
			}
		}
	}
}

/*************************************************************
Checking Door Last Position Function
*************************************************************/

void DoorCheck(void)
{
	u8 Door_Status = STD_Low;
	Door_Status = EEPROM_ReadByte(DOOR_Status_Loc,0);
	_delay_ms(50);
	if(Door_Status != 0xFF)
	{
		ServoMotor(90);
	}
	else
	{
		//Do nothing
	}
}

/*************************************************************
Room1 Controlling Menu
*************************************************************/

void ROOM1(u8 location)
{
	u8 Key = STD_Low;
	u8 Slave_Status = STD_Low;
	Trylamp:LCD_Clear();
	LCD_String("1:Lamp1 2:Lamp2");
	LCD_SetPos(2,0);
	LCD_String("3:AC    4:Return");
	
	while(Key == STD_Low)
	{
		Key = GetKey();
		if (Key != STD_Low)
		{
			switch(Key)
			{
				case '1':
				LCD_Clear();
				Key = STD_Low;
				_delay_ms(50);
				SPI_TxRx(Led1);
				_delay_ms(50);
				Slave_Status = SPI_TxRx(Ack);
				if(Slave_Status == On)
				{
					LCD_Clear();
					LCD_String("Led is On!");
					LCD_SetPos(2,0);
					LCD_String("1:Turnoff 2:back");
					
					while(Key == STD_Low)
					{
						Key = GetKey();
						if(Key != STD_Low)
						{
							_delay_ms(100);
							switch(Key)
							{
								case '1':
								SPI_TxRx(Led1_TurnOff);
								Bluetooth_TransmaitString("\nLamp1,Room1 is Off now!");
								Key = STD_Low;
								ROOM1(location);
								break;
								
								case '2':
								SPI_TxRx(Return_MainMenu);
								ROOM1(location);
								break;
							}
						}
					}
				}
				else if (Slave_Status == Off)
				{
					LCD_Clear();
					LCD_String("Led is Off!");
					LCD_SetPos(2,0);
					LCD_String("1:TurnOn 2:back");
					
					while(Key == STD_Low)
					{
						Key = GetKey();
						if(Key != STD_Low)
						{
							_delay_ms(100);
							switch(Key)
							{
								case '1':
								SPI_TxRx(Led1_TurnOn);
								Bluetooth_TransmaitString("\nLamp1,Room1 is on now!");
								Key = STD_Low;
								ROOM1(location);
								break;
								
								case '2':
								SPI_TxRx(Return_MainMenu);
								ROOM1(location);
								break;
							}
						}
					}
				}
				else
				{
					//Do nothing
				}
				LCD_Clear();
				ROOM1(location);
				break;
				
				
				case '2':
				LCD_Clear();
				Key = STD_Low;
				_delay_ms(50);
				SPI_TxRx(Led2);
				_delay_ms(50);
				Slave_Status = SPI_TxRx(Ack);
				if(Slave_Status == On)
				{
					LCD_Clear();
					LCD_String("Led is On!");
					LCD_SetPos(2,0);
					LCD_String("1:Turnoff 2:back");
					
					while(Key == STD_Low)
					{
						Key = GetKey();
						if(Key != STD_Low)
						{
							_delay_ms(100);
							switch(Key)
							{
								case '1':
								SPI_TxRx(Led2_TurnOff);
								Bluetooth_TransmaitString("\nLamp2,Room1 is Off now!");
								Key = STD_Low;
								ROOM1(location);
								break;
								
								case '2':
								SPI_TxRx(Return_MainMenu);
								ROOM1(location);
								break;
							}
						}
					}
				}
				else if (Slave_Status == Off)
				{
					LCD_Clear();
					LCD_String("Led is Off!");
					LCD_SetPos(2,0);
					LCD_String("1:TurnOn 2:back");
					
					while(Key == STD_Low)
					{
						Key = GetKey();
						if(Key != STD_Low)
						{
							_delay_ms(100);
							switch(Key)
							{
								case '1':
								SPI_TxRx(Led2_TurnOn);
								Bluetooth_TransmaitString("\nLamp2,Room1 is on now!");
								Key = STD_Low;
								ROOM1(location);
								break;
								
								case '2':
								SPI_TxRx(Return_MainMenu);
								Key = STD_Low;
								ROOM1(location);
								break;
							}
						}
					}
				}
				else
				{
					//Do nothing
				}
				LCD_Clear();
				ROOM1(location);
				break;
				
				case '3':
				LCD_Clear();
				Key = STD_Low;
				_delay_ms(50);
				SPI_TxRx(Air_Cond);
				_delay_ms(50);
				Slave_Status = SPI_TxRx(Ack);
				if(Slave_Status == On)
				{
					LCD_Clear();
					LCD_String("Air-Cond is On!");
					LCD_SetPos(2,0);
					LCD_String("1:Turnoff 2:back");
					
					while(Key == STD_Low)
					{
						Key = GetKey();
						if(Key != STD_Low)
						{
							_delay_ms(100);
							switch(Key)
							{
								case '1':
								SPI_TxRx(Air_Cond_TurnOff);
								Bluetooth_TransmaitString("\nAir conditioner,Room1 is Off now!");
								Key = STD_Low;
								ROOM1(location);
								break;
								
								case '2':
								SPI_TxRx(Return_MainMenu);
								ROOM1(location);
								break;
							}
						}
					}
				}
				else if (Slave_Status == Off)
				{
					LCD_Clear();
					LCD_String("Air-Cond is Off!");
					LCD_SetPos(2,0);
					LCD_String("1:TurnOn 2:back");
					
					while(Key == STD_Low)
					{
						Key = GetKey();
						if(Key != STD_Low)
						{
							_delay_ms(100);
							switch(Key)
							{
								case '1':
								Key = STD_Low;
								u8 Tenth = STD_Low, Ones = STD_Low, Temperature = STD_Low, Counter = 1;
								LCD_Clear();
								LCD_String("Set Temp:__");
								LCD_Custome_Char(1,customChar); //Degree symbol
								LCD_SetPos(1,11);
								LCD_Char(1);
								LCD_Char('C');
								LCD_SetPos(1,9);
								while(Key == STD_Low && Counter <= 2)
								{
									Key = GetKey();
									if((Key != STD_Low) && (Counter == 1))
									{
										Tenth = Key;
										LCD_Char(Tenth);
										Key = STD_Low;
										Counter++;
									}
									else if((Key != STD_Low) && (Counter == 2))
									{
										Ones = Key;
										LCD_Char(Ones);
										Key = STD_Low;
										Counter++;
									}
									else
									{
										//Do Nothing
									}
								}
								Temperature = (unsigned char)((((unsigned char)Tenth - '0') * 10) + (Ones - '0'));
								_delay_ms(100);
								SPI_TxRx(Air_Cond_TurnOn);
								Bluetooth_TransmaitString("\nAir conditioner,Room1 is on now!");
								SPI_TxRx(Temperature);
								ROOM1(location);
								break;
								
								case '2':
								SPI_TxRx(Return_MainMenu);
								Key = STD_Low;
								ROOM1(location);
								break;
							}
						}
					}
				}
				else
				{
					//Do nothing
				}
				LCD_Clear();
				ROOM1(location);
				break;
				
				case '4':
				LCD_Clear();
				MainMenu(location);
				break;
				
				default:
				LCD_Clear();
				LCD_String("Wrong choice!");
				_delay_ms(500);
				Key = STD_Low;
				goto Trylamp;
				break;
			}
		}
	}
}

/*************************************************************
Room2 Controlling Menu
*************************************************************/
void ROOM2(u8 location)
{
	u8 Key = STD_Low;
	u8 Slave_Status = STD_Low;
	Trylamp:LCD_Clear();
	LCD_String("1:Lamp1 2:Lamp2");
	LCD_SetPos(2,0);
	LCD_String("3:Lamp3 4:Return");
	
	while(Key == STD_Low)
	{
		Key = GetKey();
		if (Key != STD_Low)
		{
			switch(Key)
			{
				case '1':
				LCD_Clear();
				Key = STD_Low;
				_delay_ms(50);
				SPI_TxRx(Led3);
				_delay_ms(50);
				Slave_Status = SPI_TxRx(Ack);
				if(Slave_Status == On)
				{
					LCD_Clear();
					LCD_String("Led is On!");
					LCD_SetPos(2,0);
					LCD_String("1:Turnoff 2:back");
					
					while(Key == STD_Low)
					{
						Key = GetKey();
						if(Key != STD_Low)
						{
							_delay_ms(100);
							switch(Key)
							{
								case '1':
								SPI_TxRx(Led3_TurnOff);
								Bluetooth_TransmaitString("\nLamp1,Room2 is Off now!");
								Key = STD_Low;
								ROOM2(location);
								break;
								
								case '2':
								SPI_TxRx(Return_MainMenu);
								ROOM2(location);
								break;
							}
						}
					}
				}
				else if (Slave_Status == Off)
				{
					LCD_Clear();
					LCD_String("Led is Off!");
					LCD_SetPos(2,0);
					LCD_String("1:TurnOn 2:back");
					
					while(Key == STD_Low)
					{
						Key = GetKey();
						if(Key != STD_Low)
						{
							_delay_ms(100);
							switch(Key)
							{
								case '1':
								SPI_TxRx(Led3_TurnOn);
								Bluetooth_TransmaitString("\nLamp1,Room2 is on now!");
								Key = STD_Low;
								ROOM2(location);
								break;
								
								case '2':
								SPI_TxRx(Return_MainMenu);
								ROOM2(location);
								break;
							}
						}
					}
				}
				else
				{
					//Do nothing
				}
				LCD_Clear();
				ROOM2(location);
				break;
				
				
				case '2':
				LCD_Clear();
				Key = STD_Low;
				_delay_ms(50);
				SPI_TxRx(Led4);
				_delay_ms(50);
				Slave_Status = SPI_TxRx(Ack);
				if(Slave_Status == On)
				{
					LCD_Clear();
					LCD_String("Led is On!");
					LCD_SetPos(2,0);
					LCD_String("1:Turnoff 2:back");
					
					while(Key == STD_Low)
					{
						Key = GetKey();
						if(Key != STD_Low)
						{
							_delay_ms(100);
							switch(Key)
							{
								case '1':
								SPI_TxRx(Led4_TurnOff);
								Bluetooth_TransmaitString("\nLamp2,Room2 is Off now!");
								Key = STD_Low;
								ROOM2(location);
								break;
								
								case '2':
								SPI_TxRx(Return_MainMenu);
								ROOM2(location);
								break;
							}
						}
					}
				}
				else if (Slave_Status == Off)
				{
					LCD_Clear();
					LCD_String("Led is Off!");
					LCD_SetPos(2,0);
					LCD_String("1:TurnOn 2:back");
					
					while(Key == STD_Low)
					{
						Key = GetKey();
						if(Key != STD_Low)
						{
							_delay_ms(100);
							switch(Key)
							{
								case '1':
								SPI_TxRx(Led4_TurnOn);
								Bluetooth_TransmaitString("\nLamp2,Room2 is on now!");
								Key = STD_Low;
								ROOM2(location);
								break;
								
								case '2':
								SPI_TxRx(Return_MainMenu);
								Key = STD_Low;
								ROOM2(location);
								break;
							}
						}
					}
				}
				else
				{
					//Do nothing
				}
				LCD_Clear();
				ROOM2(location);
				break;
				
				case '3':
				LCD_Clear();
				Key = STD_Low;
				_delay_ms(50);
				SPI_TxRx(Led5);
				_delay_ms(50);
				Slave_Status = SPI_TxRx(Ack);
				if(Slave_Status == On)
				{
					LCD_Clear();
					LCD_String("Led is On!");
					LCD_SetPos(2,0);
					LCD_String("1:Turnoff 2:back");
					
					while(Key == STD_Low)
					{
						Key = GetKey();
						if(Key != STD_Low)
						{
							_delay_ms(100);
							switch(Key)
							{
								case '1':
								SPI_TxRx(Led5_TurnOff);
								Bluetooth_TransmaitString("\nLamp3,Room2 is Off now!");
								Key = STD_Low;
								ROOM2(location);
								break;
								
								case '2':
								SPI_TxRx(Return_MainMenu);
								ROOM2(location);
								break;
							}
						}
					}
				}
				else if (Slave_Status == Off)
				{
					LCD_Clear();
					LCD_String("Led is Off!");
					LCD_SetPos(2,0);
					LCD_String("1:TurnOn 2:back");
					
					while(Key == STD_Low)
					{
						Key = GetKey();
						if(Key != STD_Low)
						{
							_delay_ms(100);
							switch(Key)
							{
								case '1':
								SPI_TxRx(Led5_TurnOn);
								Bluetooth_TransmaitString("\nLamp3,Room2 is on now!");
								Key = STD_Low;
								ROOM2(location);
								break;
								
								case '2':
								SPI_TxRx(Return_MainMenu);
								Key = STD_Low;
								ROOM2(location);
								break;
							}
						}
					}
				}
				else
				{
					//Do nothing
				}
				LCD_Clear();
				ROOM2(location);
				break;
				
				case '4':
				LCD_Clear();
				MainMenu(location);
				break;
				
				default:
				LCD_Clear();
				LCD_String("Wrong choice!");
				_delay_ms(500);
				Key = STD_Low;
				goto Trylamp;
				break;
			}
		}
	}
}

/*************************************************************
Admin Mode Controlling Menu
*************************************************************/

void AdminMenu(void)
{
	LCD_Clear();
	LCD_String("Admin mode on");
	Bluetooth_TransmaitString("\n\nSmart-Home Project\nAdmin mode\n");
	Bluetooth_TransmaitString("Room1\n11)Lamp1\n22)Lamp2\n33)Air-Conditioner\n\n________________________________");
	Bluetooth_TransmaitString("\nRoom2\n44)Lamp1\n55)Lamp2\n66)Lamp3\n7)Main-Door\n\n________________________________\nNumber\na)Register User\nb)Delete User One\nc)Delete User Two\nd)Number of registered users\ne)User-Mode");
	u8 Admin_Choice = STD_Low, status = STD_Low, usersCount = 0;
	
	adminmenu:
	Admin_Choice = STD_Low;
	usersCount = 0;
	Admin_Choice = Bluetooth_Receive();
	

	switch(Admin_Choice)
	{
		case '1':
		status = SPI_TxRx(Led1);
		if(status == On)
		{
			Bluetooth_TransmaitString("\nLamp Turned Off!\n");
			SPI_TxRx(Led1_TurnOff);
			Admin_Choice = STD_Low;
		}
		else if(status == Off)
		{
			Bluetooth_TransmaitString("\nLamp Turned on!\n");
			SPI_TxRx(Led1_TurnOn);
			Admin_Choice = STD_Low;
		}
		goto adminmenu;
		break;
		
		case '2':
		status = SPI_TxRx(Led2);
		if(status == On)
		{
			SPI_TxRx(Led2_TurnOff);
			Bluetooth_TransmaitString("\nLamp Turned Off!\n");
		}
		else if(status == Off)
		{
			SPI_TxRx(Led2_TurnOn);
			Bluetooth_TransmaitString("\nLamp Turned on!\n");
		}
		goto adminmenu;
		break;
		
		case '3':
		status = SPI_TxRx(Air_Cond);
		if(status == On)
		{
			SPI_TxRx(Air_Cond_TurnOff);
			Bluetooth_TransmaitString("\nAir conditioner Turned Off!\n");
		}
		else if(status == Off)
		{
			SPI_TxRx(Air_Cond_TurnOn);
			SPI_TxRx(24);
			Bluetooth_TransmaitString("\nAir conditioner Turned on!\n");
		}
		goto adminmenu;
		break;
		
		case '4':
		status = SPI_TxRx(Led3);
		if(status == On)
		{
			SPI_TxRx(Led3_TurnOff);
			Bluetooth_TransmaitString("\nLamp Turned Off!\n");
		}
		else if(status == Off)
		{
			SPI_TxRx(Led3_TurnOn);
			Bluetooth_TransmaitString("\nLamp Turned on!\n");
		}
		goto adminmenu;
		break;
		
		case '5':
		status = SPI_TxRx(Led4);
		if(status == On)
		{
			SPI_TxRx(Led4_TurnOff);
			Bluetooth_TransmaitString("\nLamp Turned Off!\n");
		}
		else if(status == Off)
		{
			SPI_TxRx(Led4_TurnOn);
			Bluetooth_TransmaitString("\nLamp Turned on!\n");
		}
		goto adminmenu;
		break;
		
		case '6':
		status = SPI_TxRx(Led5);
		if(status == On)
		{
			SPI_TxRx(Led5_TurnOff);
			Bluetooth_TransmaitString("\nLamp Turned Off!\n");
		}
		else if(status == Off)
		{
			SPI_TxRx(Led5_TurnOn);
			Bluetooth_TransmaitString("\nLamp Turned on!\n");
		}
		goto adminmenu;
		break;
		
		case '7':
		if(EEPROM_ReadByte(DOOR_Status_Loc,0) == 0xFF)
		{
			UART_TransmaitString("\nOpening Main Door!\n");
			ServoMotor(90);
			EEPROM_WriteByte(DOOR_Status_Loc,0,'1');
			_delay_ms(200);
			Admin_Choice = STD_Low;
			goto adminmenu;
		}
		else
		{
			UART_TransmaitString("\nClosing Main Door!\n");
			ServoMotor(0);
			EEPROM_WriteByte(DOOR_Status_Loc,0,0xFF);
			_delay_ms(200);
			Admin_Choice = STD_Low;
			goto adminmenu;
		}
		break;
		
		case 'e':
		usersCount = Users_Count();
		if(usersCount == 0)
		{
			Bluetooth_TransmaitString("\nNo Registered Users, register a user first!");
			goto adminmenu;
		}
		else if(usersCount == 1)
		{
			u8 exist1=STD_Low,exist2 = STD_Low;
			exist1 = Password_Exist(USER_PASS_LOC);
			exist2 = Password_Exist(USER2_PASS_LOC);
			if(exist1 == 1)
			{
				Bluetooth_TransmaitString("\n\n\n\n\n\n\n\nUser One mode On!");
				_delay_ms(50);
				Menu1(USER_PASS_LOC);
			}
			else if (exist2 == 1)
			{
				Bluetooth_TransmaitString("\n\n\n\n\n\n\n\nUser Two mode On!");
				_delay_ms(50);
				Menu1(USER2_PASS_LOC);
			}
			else
			{
				//Do nothing
			}
		}
		else if(usersCount == 2)
		{
			ChooseUser();
		}

		break;
		
		case 'd':
		usersCount = Users_Count();
		if(usersCount == 0)
		{
			Bluetooth_TransmaitString("\nNo users Registered! (0/2)");
			goto adminmenu;
		}
		else if(usersCount == 1)
		{
			Bluetooth_TransmaitString("\nOne users Registered! (1/2)");
			goto adminmenu;
		}
		else if(usersCount == 2)
		{
			Bluetooth_TransmaitString("\nTwo users Registered! (2/2)");
			goto adminmenu;
		}
		else
		{
			//Do nothing
		}
		goto adminmenu;
		break;
		
		case 'a':
		usersCount = Users_Count();
		if(usersCount == 2)
		{
			Bluetooth_TransmaitString("\nAll users are registered!");
			goto adminmenu;
		}
		else
		{
			u8 exist1 = STD_Low;
			exist1 = Password_Exist(USER_PASS_LOC);
			if(exist1 == 1)
			{
				Bluetooth_TransmaitString("\nRegister User Two Now!");
				Menu1(USER2_PASS_LOC);
			}
			else
			{
				Bluetooth_TransmaitString("\nRegister user One Now!");
				Menu1(USER_PASS_LOC);
			}
		}
		break;
		
		case 'b':
		if(Password_Exist(USER_PASS_LOC) == 1)
		{
			for(u8 i = 0 ; i < 4; i++)
			{
				EEPROM_WriteByte(USER_PASS_LOC,i,0xFF);
				_delay_ms(200);
			}
			Bluetooth_TransmaitString("\nUser One deleted successfully!");
			goto adminmenu;
		}
		else
		{
			Bluetooth_TransmaitString("\nUser One is not registered yet!");
			goto adminmenu;
		}
		break;
		
		case 'c':
		if(Password_Exist(USER2_PASS_LOC) == 1)
		{
			for(u8 i = 0 ; i < 4; i++)
			{
				EEPROM_WriteByte(USER2_PASS_LOC,i,0xFF);
				_delay_ms(200);
			}
			Bluetooth_TransmaitString("\nUser Two deleted successfully!");
			goto adminmenu;
		}
		else
		{
			Bluetooth_TransmaitString("\nUser Two is not registered yet!");
			goto adminmenu;
		}
		break;
		
		default:
		goto adminmenu;
		break;
	}
}

/*************************************************************
Door Controlling Function
*************************************************************/

/*void Door(void)
{
LCD_Clear();
u8 Door_Status = STD_Low;
u8 Key = STD_Low;
Door_Status = EEPROM_ReadByte(DOOR_Status_Loc,0);
_delay_ms(50);
if(Door_Status == 0xFF)
{
LCD_Clear();
LCD_String("Door is closed!");
_delay_ms(500);
Tryagain1:LCD_Clear();
LCD_String("press 1 open");
LCD_SetPos(2,0);
LCD_String("press 0 return");
_delay_ms(20);

while(Key == STD_Low)
{
Key = GetKey();
if (Key != STD_Low)
{
switch(Key)
{
case '1':
LCD_Clear();
LCD_String("Opening Door");
Bluetooth_TransmaitString("\nMain Door is Opened!");
ServoMotor(90);
EEPROM_WriteByte(DOOR_Status_Loc,0,'1');
_delay_ms(500);
Key = STD_Low;
LCD_Clear();
MainMenu();
break;

case '0':
LCD_Clear();
LCD_String("Return to menu!");
_delay_ms(400);
Key = STD_Low;
LCD_Clear();
MainMenu();
break;

default:
LCD_Clear();
LCD_String("Wrong choice!");
_delay_ms(500);
Key = STD_Low;
goto Tryagain1;
break;
}
}
}
}
else
{
LCD_Clear();
LCD_String("Door is opened!");
_delay_ms(500);
Tryagain2:LCD_Clear();
LCD_String("press 1 close");
LCD_SetPos(2,0);
LCD_String("press 0 return");
_delay_ms(20);

while(Key == STD_Low)
{
Key = GetKey();
if (Key != STD_Low)
{
switch(Key)
{
case '1':
LCD_Clear();
LCD_String("Closing Door");
Bluetooth_TransmaitString("\nMain Door is Closed!");
ServoMotor(0);
EEPROM_WriteByte(DOOR_Status_Loc,0,0xFF);
_delay_ms(500);
Key = STD_Low;
LCD_Clear();
MainMenu();
break;

case '0':
LCD_Clear();
LCD_String("Return to menu!");
_delay_ms(400);
Key = STD_Low;
LCD_Clear();
MainMenu();
break;

default:
LCD_Clear();
LCD_String("Wrong choice!");
_delay_ms(500);
Key = STD_Low;
goto Tryagain2;
break;
}
}
}
}
}*/

u8 Users_Count(void)
{
	u8 Password_characters_count = 0;
	if(Password_Exist(USER_PASS_LOC) == 1)
	{
		Password_characters_count++;
	}
	else
	{
		Password_characters_count = Password_characters_count;
	}
	
	if(Password_Exist(USER2_PASS_LOC) == 1)
	{
		Password_characters_count++;
	}
	else
	{
		Password_characters_count = Password_characters_count;
	}
	return Password_characters_count;
}

void Register(void)
{
	u8 exist1 = STD_Low,exist2 = STD_Low;
	exist1 = Password_Exist(USER_PASS_LOC);
	exist2 = Password_Exist(USER2_PASS_LOC);
	if(exist1 == 1)
	{
		Menu1(USER_PASS_LOC);
	}
	else if(exist2 == 1)
	{
		Menu1(USER2_PASS_LOC);
	}
	else
	{
		//Do nothing
	}
}

void ChooseUser(void)
{
	u8 Key = STD_Low;
	LCD_Clear();
	LCD_String("1:User1 2:User2");
	while(Key == STD_Low)
	{
		Key = GetKey();
		if(Key != STD_Low)
		{
			switch(Key)
			{
				case '1':
				Menu2(USER_PASS_LOC);
				Bluetooth_TransmaitString("\nUser One is now in control!");
				Bluetooth_TransmaitString("\n\n\n\n\n\n\n\nUser One mode On!");
				break;
				
				case '2':
				Menu2(USER2_PASS_LOC);
				Bluetooth_TransmaitString("\nUser Two is now in control!");
				Bluetooth_TransmaitString("\n\n\n\n\n\n\n\nUser Two mode On!");
				break;
			}
		}
	}
}


