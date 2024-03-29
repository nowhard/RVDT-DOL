#ifndef DOL_H
#define DOL_H
#include "rtos/core.h"
#include "proto_uso/channels.h"
#include "preferences.h"
#include "watchdog.h"

#define MIN1	463
#define MAX1	3540

#define MIN2	465
#define MAX2	3547

#define ADC_MID 2010
#define QUADRANT_WEIGHT	128

#define SHR	3

#define NORM1(val) ((((val)-MIN1)<<12)/((MAX1)-(MIN1))) 
#define NORM2(val) ((((val)-MIN2)<<12)/((MAX2)-(MIN2))) 
//----------------------------------------------------
void Dol_Init(void);//������������� ��������� �������
//unsigned char Dol_Measure_Process(void);//����������� ������� ��������� �������
unsigned char Sec_Task(void);//��������� ������ ��� ����������� ������� �������
void INT0_ISR(void);//���������� �������� ���������� 0
int Get_Angle(unsigned long PH_1,unsigned long PH_2);
int Get_Delta_Angle(unsigned long PH_1,unsigned long PH_2,unsigned long PH_1_LAST,unsigned long PH_2_LAST);
int arctan(long V1, long V2);
//----------------------------------------------------
extern struct Channel xdata channels[CHANNEL_NUMBER];
//----------------------------------------------------
#endif