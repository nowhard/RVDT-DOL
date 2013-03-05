#ifndef PREFERENCES_H
#define	PREFERENCES_H

#define ADUC_841

#ifdef ADUC_842 
#define F_OSC_8 8388608
#endif

#ifdef ADUC_841 
#define F_OSC_11 11059200
#endif

//#define BAUDRATE_9600
#define BAUDRATE_57600
//#define BAUDRATE_38400



//----------------------------------------------------------------------
#ifdef BAUDRATE_57600 //
	#ifdef F_OSC_11
		#define T3CON_VAL	0x83
		#define T3FD_VAL	0x20//0x09
	#endif
#endif


//----------------------------------------------------------------------
#ifdef 	F_OSC_11
	#define PLLCON_VAL 0xF8
	
	#define TH0_VAL 	0xFF//10us
	#define TL0_VAL 	0x23//0x91

	#define TH1_VAL 	0x27
	#define TL1_VAL		0xFF

	#define F_OSC F_OSC_12
#endif

//----------------------------------------------------------------------
#define DEVICE_ADDR_MAX	0xF //максимальный адрес устройства
//----------------------------адреса настроек в ППЗУ--------------------

#define ADC_SETTINGS_ADDR	0x10


#define DEVICE_ADDR_EEPROM	0x2A

#define DEVICE_NAME_EEPROM		0x2B
#define DEVICE_NAME_LENGTH		0x5//длина имени в блоках
#define DEVICE_NAME_LENGTH_SYM	20//длина имени в байтах

#define DEVICE_VER_EEPROM	0x30
#define DEVICE_VER_LENGTH	0x2//длина версии по в блоках-блок-4байта
#define DEVICE_VER_LENGTH_SYM 0x8

#define DEVICE_DESC_EEPROM	0x33
#define DEVICE_DESC_MAX_LENGTH	10//максимальная длина строки описания-5 блоков	по 4 байта
#define DEVICE_DESC_MAX_LENGTH_SYM 40

#define DEVICE_DESC_LEN_EEPROM	0x32//адрес значения длины строки описания в ППЗУ

#define ADC_CALIBRATE_ADDR		0x50
//---------------------------------------------------------------------
#endif
