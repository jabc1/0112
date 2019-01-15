/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : setting.c
Description: 实现设置radio功能
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-23
Modify	   : 
Modify Time: 
******************************************************************************/
#include <string.h>
#include "setting.h"
#include "fifo.h"
#include "task.h"
#include "stdio.h"
#include "Flash.h"
#include "uart.h"
#include "memory.h"
#include "Analysis.h"

/*
设置    频率：7e 06 01 1a a0 10 F5 F7
设置    频率：7e 06 01 1a a0 20 F5 E3
设置  地址码：7e 0a 01 1a a1 10 11 12 13 14 7e e9
设置    速率：7e 06 01 1a a2 01 34 9b
设置接收通道：7e 06 01 1a a3 00 f4 cb

查询频率命令: 7e 06 01 2a a0 00 f4 34
查询  地址码：7e 06 01 2a a1 00 f5 a4
查询  速率  : 7e 06 01 2a a2 00 f5 54
查询  数据  : 7e 06 01 2a a3 01 35 04 ---->  7e 07 01 2a a3 01 01 35 04
*/
u8 set_fun(u8 datatype,u8 *data)
{
	switch(datatype)
	{
		case setfer:
			set_fer(data);
			break;
		case setmac:
			set_mac(data);
			break;
		case setspeed:
			set_speed(data);
			break;
		case setch:
			set_ch(data);
			break;
		case setsendch:
			break;
		case setsendpow:
			break;
		default:
			break;
	}
	return 1;
}
u8 sel_fun(u8 datatype,u8 *data)
{
	switch(datatype)
	{
		case seldata:
			sel_data(data);
			break;
		case selrf:
			break;
		default:
			break;
	}
	return 1;
}

u8 set_fer(u8 *data)
{
	u32 temp1,temp2;
	u8 temp;
	temp = *data;
	switch(temp)
	{
		case 0x10:
			temp2= 0x10;
			break;
		case 0x20:
			temp2= 0x20;
			break;
		default:
			break;
	}
#if 0
	flash_page_erase(0xc8);
	flash_page_write(0xc8,&temp2);
	flash_read(0xc8*1024,&temp1,1);
#else
	flash_page_erase_1((u32 *)setferadd);//擦除
	flash_word_write((u32 *)setferadd,temp2);//进行写操作
	temp1 = (u8)(*(u32 *)(setferadd));//读操作
#endif
	printf("setting succ=0x%02X!!!\r\n",temp1);
	return 1;
}
u8 set_mac(u8 *data)
{
	u8 tbuff[5]={0,};
	u8 ttbuf[5] = {0,};
	memcpy(tbuff,data,5);
	flash_page_erase_1((u32 *)setmacadd);//擦除
	flash_write_buff((u32 *)setmacadd,tbuff,2);//进行写操作
	ttbuf[0] = (u8)(*(u32 *)(setmacadd+(0)));//读操作
	ttbuf[1] = (u8)(*(u32 *)(setmacadd+(1)));//读操作
	ttbuf[2] = (u8)(*(u32 *)(setmacadd+(2)));//读操作
	ttbuf[3] = (u8)(*(u32 *)(setmacadd+(3)));//读操作
	ttbuf[4] = (u8)(*(u32 *)(setmacadd+(4)));//读操作
	printf("mac test %s\r\n",ttbuf);
	return 1;
}
u8 set_speed(u8 *data)
{
	u8 temp;
	temp = *data;
	printf("speed=%02d\r\n",temp);
	return 1;
}
u8 set_ch(u8 *data)
{
	u8 temp;
	temp = *data;
	printf("ch = %02d\r\n",temp);
	return 1;
}

u8 sel_data(u8 *data)
{
	//7e 07 01 2a a3 01 01 35 04
	u8 temp,i;
	u8 buff2[7];
	temp = *data;
	if(temp == 0x01)//表示第几通道
	{
		if(!fifo_empty(&Uart0Tx))//有数据上报
		{
			fifo_gets(&Uart0Tx,buff2,7);
			for(i=0;i<7;i++)
			{
				if(buff2[i] == 0x00)
				{
					buff2[i] = 0xff;
				}
			}
			Unpack_function(0x2a,temp,buff2,7);//表示有数据进行标签信息出队及打包
		}
		else
		{
			printf("no data!!!!");//回应无数据
		}
	}
	return 1;
}


















