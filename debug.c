#include <ADuC841.h>

#include "timer3.h"
#include "timer2.h"
#include "proto_uso/proto_uso.h"
#include "preferences.h"
#include "eeprom/eeprom.h"

#include "rtos/timer1.h"
#include "adc.h"
#include "watchdog.h"
#include "proto_uso/channels.h"



//#include "calibrate/calibrate.h"
#include "pt/pt.h"
#include "dol.h"

extern struct pt pt_proto;
extern volatile unsigned long PHASE_1_RESULT,PHASE_2_RESULT;
extern volatile unsigned long PHASE_1_RESULT_LAST,PHASE_2_RESULT_LAST;	//предыдущий результат
extern volatile unsigned int ADC_MID_1,ADC_MID_2;
extern volatile unsigned long turn_counter;
volatile struct pt pt_out;

volatile long angle=0, last_angle=0;

PT_THREAD(OutProcess(struct pt *pt));

//-----------------------------------------

//PT_THREAD(I2C_RepeatRead(struct pt *pt));
 //---------------------------------------

void main(void) //using 0
{			   
	unsigned char i=0;
	EA = 0;


	
	ChannelsInit();//инициализаци€ настроек каналов
	Protocol_Init();
	Timer0_Initialize();	
	Timer1_Initialize(); //таймер шедулера 200√ц	



	ADC_Initialize();
	EA=1;
	for(i=0;i<MID_NUM<<1;i++)
	{
		unsigned int delay=300;
		SCONV=1;
		while(delay)
		{
			delay--;
		}
	}

	ADC_MID_1=PHASE_1_RESULT;
	ADC_MID_2=PHASE_2_RESULT;

	UART_Init();
	Dol_Init();
	Timer2_Initialize();


//	WDT_Init(WDT_2000);//включить сторожевой таймер


//	RestoreCalibrate();

//	PT_INIT(&pt_i2c_read);
//	PT_INIT(&pt_freq_measure);
//	PT_INIT(&pt_sort);
	PT_INIT(&pt_out);

	

	while(1)
	{	
		ProtoProcess(&pt_proto);
		OutProcess(&pt_out);	    
	}
}
//-----------------------------------------------------------------------------
#pragma OT(0,Speed)

//-----------------------------------
void Timer1_Interrupt(void) interrupt 3  //таймер шедулера
{
//---------------------------------------
	TH1	= TH1_VAL; ///200 Hz;
	TL1 = TL1_VAL;//

	pt_proto.pt_time++;
	pt_out.pt_time++;
	return;	
}
//-----------------------------------------
PT_THREAD(OutProcess(struct pt *pt))
 {
  PT_BEGIN(pt);

  while(1) 
  {
  	 PT_DELAY(pt, 1);
	 //last_angle=angle;
	 angle=Get_Angle(PHASE_1_RESULT,PHASE_2_RESULT);//+turn_counter;
	 
    channels[0].channel_data=angle+turn_counter+0x80008000;//(angle-last_angle);//Get_Angle(PHASE_1_RESULT,PHASE_2_RESULT);

   channels[3].channel_data=turn_counter;
   channels[4].channel_data=ADC_MID_2;

  }
  PT_END(pt);
 }