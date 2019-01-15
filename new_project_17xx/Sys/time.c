/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : time.c
Description: ��Ҫʵ��ϵͳ��ʱ����ʼ��,ʹ�ÿ⺯���㲻��������һ�μĴ���
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-04
Modify	   : 
Modify Time: 
******************************************************************************/
#include "time.h"
#include "gpio.h"
#include "Thread.h"
extern volatile uint16_t usDelayms;
volatile unsigned long SysTickCnt;
u16 Systick_delay;
/******************************************************************************
 * ��������:   void Timer_Timer0Init()
 * ��������:   1ms��ʱ��
 * ǰ������:   ��
 * ����:       ��
 * ���:       ��
 * ����        
 * ע��:       
 *****************************************************************************/
void Timer_Timer0Init(uint32_t clk, uint32_t howtime)//������ʱ�����ӵ��������ʾ��������1s��������0109
{
	LPC_SC->PCONP|=(1<<1);//��TIMER0����ʱ��
	LPC_TIM0->CTCR &=(~0x03);//�������ƼĴ���
	LPC_TIM0->CTCR |=0x00;//��ʱ��ģʽ
	//----PC=PR-----TC++
	LPC_TIM0->TC =0;//��ʱ������
	LPC_TIM0->PR =0;//Ԥ��Ƶ�Ĵ���
	LPC_TIM0->PC =0;//Ԥ��Ƶ������
	LPC_TIM0->TCR |=(1<<1);//��ʱ�����ƼĴ���--��λ��ʱ��
	LPC_TIM0->TCR &=~(1<<1);//�����λ
	LPC_TIM0->PR =clk-1;
	LPC_TIM0->IR=0xFFFFFFFF;   //����ж�
	//--------------------
	LPC_TIM0->MR0=howtime;//ƥ��Ĵ���---���ٸ�1us��ƥ��
	LPC_TIM0->MCR &=~(0x07);  //ƥ����ƼĴ���--��ֹƥ��-��λ-ֹͣ�������ж�
	LPC_TIM0->MCR |=(1<<0); //����ƥ���ж�
	LPC_TIM0->MCR |=(1<<1); //����λ�ж�--ƥ��ʱTC��λ-���¼���
	NVIC_SetPriority(TIMER0_IRQn, ((0x01<<3)|0x01));  //���ö�ʱ���ж����ȼ�
	NVIC_EnableIRQ(TIMER0_IRQn);   //��ʱ���ж�ʹ��
	LPC_TIM0->TCR |=(1<<0);  //������ʱ��
}
void TIMER0_IRQHandler(void)
{
	if(TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)== SET)
	{
		;//LED_toggle();
	}
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}



void SysTickInit(void)
{
	SYSTICK_InternalInit(1);//ϵͳʱ�ӳ�ʼ��,1����һ���ж�
	SYSTICK_IntCmd(ENABLE);//ʹ���ж�
	SYSTICK_Cmd(ENABLE);//ʹ��
}
void SysTick_Handler(void)//1ms
{
	SysTickCnt++;
	Systick_delay++;
	Thread_RunCheck();
	if(usDelayms) 
	{
		usDelayms--;
	}
}















