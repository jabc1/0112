/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : delay.c
Description: ֻҪʵ�������ʱ���Ǻܾ�ȷ��ϣ�������ʹ��ϵͳ�δ�ʱ����ʵ�־�ȷ��ʱ
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-09
Modify	   : 
Modify Time: 
******************************************************************************/
#include "delay.h"
extern u32 Systick11;
void delay_50us(u16 n)
{
	u16 i,j;
	for(i=n;i>0;i--)
	{
		for(j=1000;j>0;j--)
		{
			;
		}
	}
}

void Delay_ms(u16 n)
{
	u16 i,j;
	for(i=n;i>0;i--)
	{
		for(j=20;j>0;j--)
		{
			delay_50us(1);
		}
	}

}
/*****************************************************************************
������:void Tick_delay_ms (u16 tick) 
��������:������ʱ����
����:�������// ��λms
����ֵ:��
******************************************************************************/
void Tick_delay_ms(u16 tick) 
{
	u16 systickcnt;
	systickcnt = Systick11;
	while ((Systick11 - systickcnt) < tick);
}






