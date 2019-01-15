/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : logic.c
Description: 主要实现各个进程业务逻辑
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-07
Modify	   : 
Modify Time: 
******************************************************************************/
#include  <string.h>
#include "logic.h"
#include "fifo.h"
#include "memory.h"
#include "stdio.h"
#include "spi.h"
#include "Analysis.h"
#include "gpio.h"
#include "uart.h"
#include "Bluetooth.h"

_DATA	Data;//进行记录处理
_Pack	Pack;//协议包
/*
查询频率命令: 7e 06 01 2a a0 00 f4 34
查询  地址码：7e 06 01 2a a1 00 f5 a4
查询  速率  : 7e 06 01 2a a2 00 f5 54
查询  数据  : 7e 06 01 2a a3 01 35 04 ---->  7e 07 01 2a a3 01 01 35 04
*/
//接收标签信息
//接收查询radio配置信息
void CacheRxProcess()
{
	u8 len_temp;
	if(!fifo_empty(&CacheRx))//主要实现接收信息解析及打包功能
	{
		memset(Data.obuf,0,sizeof(Data.obuf));
		if(info_out_fifo(&CacheRx,&len_temp,&Data.obuf[0]))
		{
			Analysis_function(&Pack.cmdtype,&Pack.datatype,&Data.obuf[0],Data.obuf,&len_temp);
			if(Pack.cmdtype == Target)//标签信息
			{
				target_fun(Pack.datatype,Data.obuf);//解析命令并进行标签信息入队操作
			}
			else if(Pack.cmdtype == Sett)//查询到配置信息
			{
				;
			}
		}
	}
}
u8 target_fun(u8 datatype,u8 *data)
{
//	u8 temp;
//	Unpack_target(datatype,data,7);
	ble_target_unpack(datatype,data,7);
//	temp = datatype;
//	switch(temp)
//	{
//		case 0x01://通道一回应，进行数据打包功能
//			Unpack_target(temp,data,6); //入队操作UartCache
//			break;
//		case 0x02://通道二回应，进行数据打包功能
//			Unpack_target(temp,data,6);
//			break;
//		case 0x03://通道三回应，进行数据打包功能
//			break;
//		case 0x04://通道四回应，进行数据打包功能
//			break;
//		default://误会
//			break;
//	}
	return true;
}


void CacheTxProcess()//1754发送信息给51822查询是否有数据上报
{
	u8 tbuff[10];
	if(!fifo_empty(&CacheTx))
	{
		if(fifo_gets(&CacheTx,tbuff,8))//发送信息功能
		{
			memset(ucSPITxBuffer,0,sizeof(ucSPITxBuffer));
			memcpy(ucSPITxBuffer,tbuff,8);//发送命令
			usDataSended = 50;
//			printf("%s",ucSPITxBuffer);
		}
	}
}
void QueryProcess()
{
	static u8 buff[1] = {0};
	if(buff[0]++ >=4)
	{
		buff[0] = 1;
	}
	Unpack(0x2a,0xa3,buff,1);//进行命令打包功能
}
void Uart3Process()
{
	u8 temp,temp1;
	u8 tbuff[20];
	if(!fifo_empty(&UartCache))
	{
//		memset(tbuff,0,sizeof(tbuff));
//		if(info_out_fifo(&UartCache,&temp,&tbuff[0]))//标签信息处理
//		{
//			printf("%s",tbuff);
//		}
	}
//	if(!fifo_empty(&BleCache))//测试蓝牙连接fifo，如果蓝牙连接成功则重新初始化fifo
//	{
//		fifo_getc(&BleCache,&temp1);
//		printf("%c",temp1);
//	}
}










