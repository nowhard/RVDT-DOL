#include "adc.h"

sbit PIN_1=P3^2;
sbit PIN_2=P3^3;
sbit PHASE_1=P3^4;
sbit PHASE_2=P3^5;
//-------------------global variables-----------------------------------
//volatile struct ADC_Channels xdata adc_channels[ADC_CHANNELS_NUM];
volatile unsigned char adc_mid_counter;//счетчик буфера усреднения
volatile unsigned long PHASE_1_VAL=0,PHASE_2_VAL=0;
volatile unsigned long PHASE_1_RESULT=0,PHASE_2_RESULT=0;

//volatile unsigned char MID_PHASE_1=0,MID_PHASE_2=0;
#pragma OT(6,Speed)
//-------------------------------------------
void ADC_Initialize() //using 0
{	
	ADCCON1=0xA0;	  // делитель 4(0x9),8(0xA), пропуск тактов 1, внутреннее опорное
	ADCCON2=0x00;	 // 0 канал, однократное преобразование
	EADC=1;			 //разрешение прер-я от ADC
	return;
}
//-------------------------------------------
void ADC_ISR(void) interrupt 6 //using 1
{
	 if(CS0==0)
	 {
//		PIN_1=1;
		PHASE_1_VAL+=(((ADCDATAH&0x0F)<<8)|ADCDATAL);//получим результат
//		PIN_1=0;
	 }
	 else
	 {
//		PIN_2=1;
		PHASE_2_VAL+=(((ADCDATAH&0x0F)<<8)|ADCDATAL);//получим результат
	 	adc_mid_counter--;
//		PIN_2=0;
	 }
//	if(PHASE_1==1)
//	{
	    CS0^=1;		
//	}
//	else
//	{
		//CS0=0;	
//	}
	    
	 if(adc_mid_counter==0)
	 {
	 	adc_mid_counter=MID_NUM;
	    PHASE_1_RESULT=PHASE_1_VAL>>4;
		PHASE_2_RESULT=PHASE_2_VAL>>4;	
		//channels[0].channel_data=PHASE_1_VAL>>6;
		PHASE_1_VAL=PHASE_2_VAL=0;

		
	 }
}
//--------------------------------------------------
