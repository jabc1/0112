/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : logic.c
Description: ��Ҫʵ�ָ�������ҵ���߼�
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

_DATA	Data;//���м�¼����
_Pack	Pack;//Э���
/*
��ѯƵ������: 7e 06 01 2a a0 00 f4 34
��ѯ  ��ַ�룺7e 06 01 2a a1 00 f5 a4
��ѯ  ����  : 7e 06 01 2a a2 00 f5 54
��ѯ  ����  : 7e 06 01 2a a3 01 35 04 ---->  7e 07 01 2a a3 01 01 35 04
*/
//���ձ�ǩ��Ϣ
//���ղ�ѯradio������Ϣ
void CacheRxProcess()
{
	u8 len_temp;
	if(!fifo_empty(&CacheRx))//��Ҫʵ�ֽ�����Ϣ�������������
	{
		memset(Data.obuf,0,sizeof(Data.obuf));
		if(info_out_fifo(&CacheRx,&len_temp,&Data.obuf[0]))
		{
			Analysis_function(&Pack.cmdtype,&Pack.datatype,&Data.obuf[0],Data.obuf,&len_temp);
			if(Pack.cmdtype == Target)//��ǩ��Ϣ
			{
				target_fun(Pack.datatype,Data.obuf);//����������б�ǩ��Ϣ��Ӳ���
			}
			else if(Pack.cmdtype == Sett)//��ѯ��������Ϣ
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
//		case 0x01://ͨ��һ��Ӧ���������ݴ������
//			Unpack_target(temp,data,6); //��Ӳ���UartCache
//			break;
//		case 0x02://ͨ������Ӧ���������ݴ������
//			Unpack_target(temp,data,6);
//			break;
//		case 0x03://ͨ������Ӧ���������ݴ������
//			break;
//		case 0x04://ͨ���Ļ�Ӧ���������ݴ������
//			break;
//		default://���
//			break;
//	}
	return true;
}


void CacheTxProcess()//1754������Ϣ��51822��ѯ�Ƿ��������ϱ�
{
	u8 tbuff[10];
	if(!fifo_empty(&CacheTx))
	{
		if(fifo_gets(&CacheTx,tbuff,8))//������Ϣ����
		{
			memset(ucSPITxBuffer,0,sizeof(ucSPITxBuffer));
			memcpy(ucSPITxBuffer,tbuff,8);//��������
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
	Unpack(0x2a,0xa3,buff,1);//��������������
}
void Uart3Process()
{
	u8 temp,temp1;
	u8 tbuff[20];
	if(!fifo_empty(&UartCache))
	{
//		memset(tbuff,0,sizeof(tbuff));
//		if(info_out_fifo(&UartCache,&temp,&tbuff[0]))//��ǩ��Ϣ����
//		{
//			printf("%s",tbuff);
//		}
	}
//	if(!fifo_empty(&BleCache))//������������fifo������������ӳɹ������³�ʼ��fifo
//	{
//		fifo_getc(&BleCache,&temp1);
//		printf("%c",temp1);
//	}
}










