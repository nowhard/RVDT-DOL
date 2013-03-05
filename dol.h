#ifndef DOL_H
#define DOL_H
#include "rtos/core.h"
#include "proto_uso/channels.h"
#include "preferences.h"
#include "watchdog.h"

#define MIN1	656
#define MAX1	3345

#define MIN2	654
#define MAX2	3345

#define NORM1(val) ((((val)-MIN1)<<12)/((MAX1)-(MIN1))) 
#define NORM2(val) ((((val)-MIN2)<<12)/((MAX2)-(MIN2))) 
//----------------------------------------------------
void Dol_Init(void);//������������� ��������� �������
//unsigned char Dol_Measure_Process(void);//����������� ������� ��������� �������
unsigned char Sec_Task(void);//��������� ������ ��� ����������� ������� �������
void INT0_ISR(void);//���������� �������� ���������� 0
int Get_Angle(unsigned long PH_1,unsigned long PH_2);
//----------------------------------------------------
extern struct Channel xdata channels[CHANNEL_NUMBER];
//----------------------------------------------------
#endif