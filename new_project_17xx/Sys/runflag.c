/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : runflag.c
Description: ��Ҫʵ�����й��������б�־
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-04
Modify	   : 
Modify Time: 
******************************************************************************/
#include "runflag.h"
#include "spi.h"
/**
******************************************************************************
* @file    runflag.c
* @author  Jason
* @date    2018/10/27
* @brief   ������ʱ��־λ
******************************************************************************
*/
#define TICK_FREQ       1000
#define TICK_CNT_FREQ   SYS_CLK
#define TICK_PERIOD     (TICK_CNT_FREQ/TICK_FREQ)

static uint8_t PriorityFlag;
static uint32_t RunTick;
RunFlag_Type RunFlag;
extern volatile unsigned long SysTickCnt;
#define FREQ_FLAG_INIT(freq) do{ \
									RunFlag.Hz##freq = 0; \
									RunFlag.Hz##freq##Tick = tick; \
								}while(0)

#define FREQ_FLAG(freq) FreqCalc(TICK_FREQ/freq, &(RunFlag.Hz##freq), &(RunFlag.Hz##freq##Tick))

void FreqCalc(uint32_t FreqFactor, uint8_t* pFlag, uint32_t* pTick)
{
	if(!PriorityFlag && RunTick - *pTick >= FreqFactor)
	{
		*pFlag = 1;
		(*pTick) += FreqFactor;
		PriorityFlag = 1;
	}
	else
	{
		*pFlag = 0;
	}
}




void RunFlagInit(void)
{
	uint32_t tick = SysTickCnt;
	FREQ_FLAG_INIT(1);//1hz
	FREQ_FLAG_INIT(4);
	FREQ_FLAG_INIT(10);
	FREQ_FLAG_INIT(20);
	FREQ_FLAG_INIT(50);
	FREQ_FLAG_INIT(100);
	FREQ_FLAG_INIT(250);
	FREQ_FLAG_INIT(500);
	FREQ_FLAG_INIT(1000);//
}

void RunFlagHandler(void)
{
	PriorityFlag = 0;
	RunTick = SysTickCnt;
	FREQ_FLAG(1000);
	FREQ_FLAG(500);//
	FREQ_FLAG(250);//
	FREQ_FLAG(100);//
	FREQ_FLAG(50);//
	FREQ_FLAG(20);//
	FREQ_FLAG(10);//
	FREQ_FLAG(4);//
	FREQ_FLAG(1);//
}

