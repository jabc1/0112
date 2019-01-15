//void wwdg_init(void)
//{
//	LPC_SC->PCLKSEL0 |= (3<<0);//分频数为八分频
//	LPC_WDT->WDCLKSEL &= ~(3<<0);
//	LPC_WDT->WDCLKSEL |= (1<<0);//设置wdt时钟为apb
//	LPC_WDT->WDCLKSEL |= (1<<31);//锁定时钟源
//	LPC_WDT->WDTC = 0xffff;//设定重载值
//	LPC_WDT->WDMOD |= (1<<0)|(1<<1);//看门狗使能并设定引发复位
//}
////关闭系统总中断
//__asm void NVIC_SETPRIMASK(void)
//{
//	CPSID i
//	BX r14
//}
////打开系统总中断
//__asm void NVIC_RESETPRIMASK(void)
//{
//	CPSIE i
//	BX r14
//}
//void wwdg_feed(void)
//{
//	NVIC_SETPRIMASK();//禁用中断
//	LPC_WDT->WDFEED = 0xaa;
//	LPC_WDT->WDFEED = 0x55;
//	NVIC_RESETPRIMASK();//重新打开中断
//}
//void WDT_IRQHandler(void) 
//{
//	NVIC_SystemReset();
//}