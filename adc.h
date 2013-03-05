#ifndef ADC_H
#define ADC_H

#include <ADuC841.h>
#include "preferences.h"
#include "eeprom/eeprom.h"
#include "proto_uso/channels.h"
#include "rtos/core.h"
#include "ulongsort.h"
#include <math.h>

//-----------------------------------------------------------
#define ADC_CHANNELS_NUM	2//���������� ���������� ������� �����������
#define MID_NUM				16



//-----------------------------------------------------------
void ADC_Initialize();
void ADC_Run();
void ADC_Stop();
void ADC_ISR(void);
void ADC_Set_Range(unsigned char range);   //40mV-2.56V
void ADC_Set_Mode(unsigned char mode);	   //
void ADC_Set_Input(unsigned char input);   //diff out
void ADC_Out_Freq(unsigned int freq);	   //DECIMATION
void ADC_Calibrate(char mode);//���������� ���

void ADC_Restore_Settings(void);//�������������� �������� ���

unsigned char Meaning_Process(void);//����������� �������, ���������� ������� �������� ��������
unsigned char Out_Task(void);//����� ������
//----------------------------------------------------------------------------------
extern struct Channel xdata channels[CHANNEL_NUMBER];
//---------------------
#endif