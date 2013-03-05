#include "dol.h"
#include "sin_cos_table.h"

#define DOL_CHANNELS	1
#define FIRST_DOL_CHN	0
sbit PHASE_1=P3^4;
sbit PHASE_2=P3^5;

sbit PIN_1=P3^2;
sbit PIN_2=P3^3;

#define ADC_MID 2048
#define QUADRANT_WEIGHT	128

#define SHR	3
//-------------------------------------------------------- debug
// long volatile idata counter_32; //счетчик дола

//--------------------------------------------------------
void Dol_Init(void) //инициализация частотных каналов
{
//	counter_32=0x80008000;
//	channels[FIRST_DOL_CHN].channel_data=counter_32;
    //P3=0x10;
	PHASE_1=0;
	PHASE_2=1;
//	return;
}
//--------------------------------------------------------
void _TR0_ (void) interrupt 1  // задержка перед работой АЦП
{
	SCONV=1;
	TR0=0;
}
//--------------------------------------------------------
void _TR2_ (void) interrupt 5
{
	P3=P3^0x30;

	if(PHASE_1)
	{
		TH0=TH0_VAL;
		TL0=TL0_VAL;
		TR0=1;
//		CS0=0;
	}
//	else
//	{
////		CS0=1;
//		SCONV=1;
//	}

	TF2=0;
}
//---------------------------------------------------------
int Get_Angle(unsigned long PH_1,unsigned long PH_2)
{
	int temp_phase_1=0,temp_phase_2=0;

	channels[1].channel_data=PH_1;
	channels[2].channel_data=PH_2;

	PH_1=NORM1(PH_1);
	PH_2=NORM2(PH_2);


	
	temp_phase_1=(long)PH_1-ADC_MID;
	temp_phase_2=(long)PH_2-ADC_MID;
   //------------------------------------------------
	if(temp_phase_1>=0 && temp_phase_2>=0)//I quadrant
	{
	//	PIN_1=0;
	//	PIN_2=0;
		if(temp_phase_1<temp_phase_2)
		{
			return 	sin_angle[((PH_1-ADC_MID)>>1)&0x3FF]>>SHR;
		}
		else
		{
			return 	cos_angle[((PH_2-ADC_MID)>>1)&0x3FF]>>SHR;
		}
	}
	//------------------------------------------------
	if(temp_phase_1>=0 && temp_phase_2<0)//II quadrant
	{
	//	PIN_1=1;
	//	PIN_2=0;
		if((temp_phase_1+temp_phase_2)>=0)
		{
			return 	(sin_angle[((ADC_MID-PH_2)>>1)&0x3FF]>>SHR)+QUADRANT_WEIGHT;
		}
		else
		{
			return 	(cos_angle[((PH_1-ADC_MID)>>1)&0x3FF]>>SHR)+QUADRANT_WEIGHT;
		}	
	}
   //------------------------------------------------
	if(temp_phase_1<0 && temp_phase_2<0) //III quadrant
	{
	//	PIN_1=0;
	//	PIN_2=1;
		if(temp_phase_1>=temp_phase_2)
		{
			return 	(sin_angle[((ADC_MID-PH_1)>>1)&0x3FF]>>SHR)+QUADRANT_WEIGHT*2;
		}
		else
		{
			return 	(cos_angle[((ADC_MID-PH_2)>>1)&0x3FF]>>SHR)+QUADRANT_WEIGHT*2;
		}
	}
   //------------------------------------------------
	if(temp_phase_1<0 && temp_phase_2>=0) //IV quadrant
	{
	//	PIN_1=1;
	//	PIN_2=1;
		if((temp_phase_1-temp_phase_2)>=0)
		{
			return 	(sin_angle[((PH_1-ADC_MID)>>1)&0x3FF]>>SHR)+3*QUADRANT_WEIGHT;
		}
		else
		{
			return 	(cos_angle[((ADC_MID-PH_2)>>1)&0x3FF]>>SHR)+3*QUADRANT_WEIGHT;
		}
	}
	//------------------------------------------------
}