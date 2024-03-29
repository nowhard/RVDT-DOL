#ifndef CORE_H
#define CORE_H
#include <ADuC841.h>                 // SFR declarations

#include "timer0.h"
#include "preferences.h"

#define maxHandlers 	8
#define maxMessages 	8
#define maxTimers  		4




#define FREQ_TASK		5
//#define ADC_MEAN_TASK   1
//#define SEC_TASK	    2
#define CYCLE_TASK		2

#define I2C_IS_READ_MSG		3
#define I2C_IS_WRITE_MSG	4



typedef unsigned char msg_num; // ��� �������� - ��� ���� ������� ������ �����
typedef int msg_par; // ��� ��������� �������
typedef unsigned char (*handler)(msg_par); // �������� �������-�����������
//---------���������-------------------------------------------------------
void setHandler(msg_num msg, handler hnd);
//void killHandler(msg_num msg, handler hnd);
void sendMessage(msg_num msg, msg_par par);
void dispatchMessage(void);
void setTimer(msg_num msg, msg_par par, unsigned int time);
//void killTimer(msg_num msg);
void dispatchTimer(void);
void Timer1_Interrupt(void);//���������� 1����

#endif