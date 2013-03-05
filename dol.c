#include "dol.h"
#include "sin_cos_table.h"

#define DOL_CHANNELS	1
#define FIRST_DOL_CHN	0
sbit PHASE_1=P3^4;
sbit PHASE_2=P3^5;

sbit PIN_1=P3^2;
sbit PIN_2=P3^3;

volatile unsigned int ADC_MID_1=0,ADC_MID_2=0;


volatile unsigned char ANGLE_HANDLING_FLAG=0;//обработать угол
//-------------------------------------------------------- debug

//--------------------------------------------------------
void Dol_Init(void) //инициализация частотных каналов
{
	PHASE_1=0;
	PHASE_2=1;
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
	}

	TF2=0;
}
//----------------------------------------------------------------------------
int arctan(long V1, long V2) {
  //Handle the quadrants explicitly
  if (V1 < 0)
  {
    if (V2 < 0)
    {
      if (V1 < V2) // 180-225
      {
        return 512 + (arctan256[(V2<<8) / V1]);
      }
      else // 225-270
      {
        return 768-(arctan256[(V1<<8) / V2]);
      }
    }
    else // V2 => 0	   //errors
    {
      if (-V1 < V2) // 90-135
      {
        return 256 + (arctan256[(-V1<<8) / V2]);
      }
      else // 135-180
      {
        return 512 - (arctan256[(V2<<8) / (-V1)]);
      }
    }
  }
  else // V1 => 0
  {
    if (V2 < 0)		 //errors
    {
      if (V1 < -V2) // 270-315
      {
        return 768 + (arctan256[(V1<<8) / (-V2)]);
      }
      else // 315-360
      {
         return 1024 - (arctan256[(-V2<<8) / V1]);
      }      
    }
    else // V2 => 0
    {
      if (V1 < V2) // 45-90
      {
        return 256 - (arctan256[(V1<<8) / V2]);
      }
      else // 0-45
      {  
        return (arctan256[(V2<<8) / V1]);
      }      
    }  
  }
}