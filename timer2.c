#include "timer2.h"
//-------------------------------------------------------
void Timer2_Initialize(void) //using 0// ������������� ������� 2-�������� ������� ��� �����������
{
    ET2 = 1;
	T2CON=0x00;
   	TL2 = 0xAD;
	TH2 = 0xFB;
	RCAP2L = 0x66;//0xAD;
    RCAP2H = 0xEA;//0xFB; //10000Hz
	TR2=1;
	PT2=1;	// ��������� ��������� � 2 �������
	return;
}
//-------------------------------------------------------