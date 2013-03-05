#include "adc.h"
#include "dol.h"


sbit PHASE_1=P3^4;
sbit PHASE_2=P3^5;


//-------------------global variables-----------------------------------
//volatile struct ADC_Channels xdata adc_channels[ADC_CHANNELS_NUM];
volatile unsigned char adc_mid_counter=MID_NUM;//������� ������ ����������
volatile unsigned long PHASE_1_VAL=0,PHASE_2_VAL=0;
volatile unsigned long PHASE_1_RESULT=0,PHASE_2_RESULT=0;
//volatile unsigned long PHASE_1_RESULT_LAST=0,PHASE_2_RESULT_LAST=0;	//���������� ���������
volatile long turn_counter=0;



volatile unsigned char sector_1=0, sector_4=0;//����� ��������, �� ������� ������������ ������
extern volatile unsigned int ADC_MID_1,ADC_MID_2;

//extern volatile unsigned char ANGLE_HANDLING_FLAG;//���������� ����
#pragma OT(6,Speed)
//-------------------------------------------
void ADC_Initialize() //using 0
{	
	ADCCON1=0xBC;//0xBC;//	  // �������� 4(0x9),8(0xA), ������� ������ 1, ���������� �������
	ADCCON2=0x00;	 // 0 �����, ����������� ��������������
	EADC=1;			 //���������� ����-� �� ADC
	return;
}
//-------------------------------------------
void ADC_ISR(void) interrupt 6 //using 1
{
	 if(CS0==0)
	 {
		PHASE_1_VAL+=(((ADCDATAH&0x0F)<<8)|ADCDATAL);//������� ���������
	 }
	 else
	 {
		PHASE_2_VAL+=(((ADCDATAH&0x0F)<<8)|ADCDATAL);//������� ���������
	 	adc_mid_counter--;
	 }

	 CS0^=1;		


	 if(adc_mid_counter==0)
	 {
	 	adc_mid_counter=MID_NUM;


	    PHASE_1_RESULT=PHASE_1_VAL>>6;
		PHASE_2_RESULT=PHASE_2_VAL>>6;	

		if(((long)PHASE_1_RESULT-ADC_MID_1)>0)
		{
			if(((long)PHASE_2_RESULT-ADC_MID_2)>=0)//1 ������
			{
				
				if(sector_4==1)
				{
					turn_counter+=1024;
				}
				sector_1=1;
				sector_4=0;
			}
			else								//4 ������
			{
				
				if(sector_1==1)
				{
					turn_counter-=1024;
				}
				sector_4=1;
				sector_1=0;
			}
		}
		else
		{
			sector_1=0;	
			sector_4=0;	
		}
		PHASE_1_VAL=PHASE_2_VAL=0;	
	 }
}
//--------------------------------------------------
