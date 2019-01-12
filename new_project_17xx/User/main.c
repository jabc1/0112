/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : main.c
Description: 实现mcu外设初始化
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-04
Modify	   : 
Modify Time: 
******************************************************************************/
#include "LPC17xx.h"
#include "system_LPC17xx.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_pinsel.h"
#include "stdio.h"
#include "gpio.h"
#include "spi.h"
#include "runflag.h"
#include "time.h"
#include "Thread.h"
#include "fifo.h"
#include "memory.h"
#include "Analysis.h"
#include "logic.h"
#include "uart.h"
#include "delay.h"

int main(void)
{
	SystemInit();
	SysTickInit();
//	Timer_Timer0Init(25,1000);//1ms
	LPC_GPIO_init();
	uart_config0(115200);
	uart_config3(115200);
	Init_fifo();
	RunFlagInit();
	Thread_Init();
	Thread_Login(FOREVER, 0, 100, &CacheRxProcess);//缓存接收进程
	Thread_Login(FOREVER, 0, 180, &CacheTxProcess);//缓存发送进程
	Thread_Login(FOREVER, 0, 200, &BluetoothProcess);//蓝牙进程
	Thread_Login(FOREVER, 0, 150, &Uart3Process);//蓝牙进程
	printf("System start!!!");
	while(1)
	{
		LPC17XXSPI_Process();//主进程
		RunFlagHandler();
		Thread_Process();
		if(RunFlag.Hz4)
		{
			static u8 flag = 0;
			flag = !flag;
			(flag ? SET_GPIO_H(LED2):SET_GPIO_L(LED2));
			//printf("uart3test");
		}
	}
	return 1;
}





