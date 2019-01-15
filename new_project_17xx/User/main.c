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
#include "wdt.h"
#include "Thread.h"
#include "fifo.h"
#include "memory.h"
#include "Analysis.h"
#include "logic.h"
#include "uart.h"
#include "delay.h"
#include "Bluetooth.h"

int main(void)
{
	SystemInit();
	SysTickInit();
	Timer_Timer0Init(25,1000);//1ms
	LPC_GPIO_init();
	uart_config0(115200);
	uart_config3(115200);
	Init_fifo();
	RunFlagInit();
	Thread_Init();
	Bluetooth_init();
	Thread_Login(FOREVER, 0, 10, &CacheRxProcess);//缓存接收进程
	Thread_Login(FOREVER, 0, 20, &CacheTxProcess);//缓存发送进程
	Thread_Login(FOREVER, 0, 30, &QueryProcess);//询问进程
//	Thread_Login(FOREVER, 0, 40, &Uart3Process);//蓝牙发送进程
	wdt_config();//超市不喂狗系统重启
	printf("System start!!!");
	//USART3_Printf("uart0 printf");
	while(1)
	{
		LPC17XXSPI_Process();//主进程
		Thread_Process();
		RunFlagHandler();
		ble_function();
		get_ble_status();
		if(RunFlag.Hz10)
		{
			LED_toggle();
			//USART3_Printf("uart0 printf");
		}
		WDT_Feed();
	}
}





