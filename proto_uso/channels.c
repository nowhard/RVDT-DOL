#include "channels.h"


//-----------------------------------
volatile struct Channel xdata channels[CHANNEL_NUMBER] /*_at_ 0x20*/;
//-----------------------------------
void ChannelsInit(void) //using 0//инициализация структуры каналов
{
	
//	Restore_Channels_Data();
	if(channels[0].settings.set.type!=0 || channels[1].settings.set.type!=0)
	{	
		// КАНАЛ 12 - ДОЛ I2C
		channels[0].number=0;		 
		channels[0].settings.set.type=1;
		channels[0].settings.set.modific=0;
		channels[0].settings.set.state_byte_1=0x40;
		channels[0].settings.set.state_byte_2=0x0A;
		channels[0].channel_data=0x0;
		channels[0].calibrate.cal.calibrate=0;
// КАНАЛ 2 - фиксированый АЦП
		channels[1].number=1;
		channels[1].settings.set.type=0;
		channels[1].settings.set.modific=3;
		channels[1].settings.set.state_byte_1=0x40;
		channels[1].settings.set.state_byte_2=0x06;
		channels[1].channel_data=0;
		channels[1].channel_data_calibrate=0;
		channels[1].calibrate.cal.calibrate=0;
		// КАНАЛ 3 - фиксированый АЦП
		channels[2].number=2;		 
		channels[2].settings.set.type=0;
		channels[2].settings.set.modific=3;
		channels[2].settings.set.state_byte_1=0x40;
		channels[2].settings.set.state_byte_2=0x06;
		channels[2].channel_data=0;
		channels[2].channel_data_calibrate=0;
		channels[2].calibrate.cal.calibrate=0;
// КАНАЛ 2 - фиксированый АЦП
		channels[3].number=3;
		channels[3].settings.set.type=0;
		channels[3].settings.set.modific=3;
		channels[3].settings.set.state_byte_1=0x40;
		channels[3].settings.set.state_byte_2=0x06;
		channels[3].channel_data=0;
		channels[3].channel_data_calibrate=0;
		channels[3].calibrate.cal.calibrate=0;
		// КАНАЛ 3 - фиксированый АЦП
		channels[4].number=4;		 
		channels[4].settings.set.type=0;
		channels[4].settings.set.modific=3;
		channels[4].settings.set.state_byte_1=0x40;
		channels[4].settings.set.state_byte_2=0x06;
		channels[4].channel_data=0;
		channels[4].channel_data_calibrate=0;
		channels[4].calibrate.cal.calibrate=0;
	}
	channels[0].channel_data=0x80008000;
	return;
}
//-----------------------------------
//void Store_Channels_Data(void) //using 0//Сохраним данные каналов в ППЗУ
//{
//	unsigned char i=0;
//	for(i=0;i<CHANNEL_NUMBER;i++)
//	{
//		EEPROM_Write(&channels[i].settings.serialize,1,ADC_SETTINGS_ADDR+i);
//	}
//	return;
//}
////-----------------------------------
//void Restore_Channels_Data(void) //using 0//Восстановим данные каналов из ППЗУ
//{
//	unsigned char i=0;
//	for(i=0;i<CHANNEL_NUMBER;i++)
//	{
//		EEPROM_Read(&channels[i].settings.serialize,1,ADC_SETTINGS_ADDR+i);
//	}
//	return;
//}
