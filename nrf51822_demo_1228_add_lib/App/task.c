/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : task.c
Description: ʵ�ָ�����������
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2018-12-3
Modify	   : 
Modify Time: 
******************************************************************************/
#include "task.h"
#include "stdio.h"
#include "string.h"
#include "memory.h"
#include "decrypt.h"
#include "runflag.h"
#include "Analysis.h"
#include "setting.h"
#include "spi.h"

static u8 rfdata[7];
_DATA		dtemp;
_CMD		ctemp;

void setting_radio()
{
//	printf("setting_radio\r\n");
}

void RF_function()
{
	u8 temp[7]={0,},i;
	if(!fifo_empty(&Radiofifo))
	{
		fifo_gets(&Radiofifo,temp,7);//����
		data_decrypt(temp,&rfdata[0]);//�������
		rfdata[6] = temp[6];
		fifo_puts(&Uart0Tx,rfdata,7);//��Ӳ���
//		for(i=0;i<7;i++)
//		{
//			printf("%02x",rfdata[i]);
//		}
	}
}
void send_function()
{
//	u8 temp[7]={0,},i;
//	if(!fifo_empty(&Uart0Tx))
//	{
//		fifo_gets(&Uart0Tx,temp,7);
//		for(i=1;i<6;i++)
//		{
//			printf("%02X",temp[i]);
//		}
//		printf("-%03d",temp[6]);
//	}
}
void main_task()
{
	u8 len_temp=0;
	if(!fifo_empty(&SPIRxfifo))
	{
		memset(dtemp.fbuff,0,sizeof(dtemp.fbuff));
		if(info_out_fifo(&SPIRxfifo,&len_temp,&dtemp.fbuff[0]))
		{
			Analysis_function(&ctemp.cmdtype,&ctemp.datatype,&dtemp.bbuff[0],dtemp.fbuff,&len_temp);
			if(ctemp.cmdtype == settype)
			{
				set_fun(ctemp.datatype,dtemp.bbuff);
			}
			else if(ctemp.cmdtype == seltype)
			{
				sel_fun(ctemp.datatype,dtemp.bbuff);
			}
		}
	}
}
void spi_test()
{
	u8 buff2[50],i;
	if(!fifo_empty(&Uart0Tx))//�������ϱ�
	{
		fifo_gets(&Uart0Tx,buff2,7);
		for(i=0;i<7;i++)
		{
			if(buff2[i] == 0x00)
			{
				buff2[i] = 0xff;
			}
			//printf("%02x",buff2[i]);
		}
		Unpack_function(0x2a,0x01,buff2,7);//��ʾ�����ݽ��б�ǩ��Ϣ���Ӽ����
	}
}
void spi_function()
{
	u8 len_temp=0;
	u8 buff[20];
	if(!fifo_empty(&SPITxfifo))
	{
		memset(buff,0,sizeof(buff));
		if(info_out_fifo(&SPITxfifo,&len_temp,buff))//���͸�������Ϣ
		{
			memcpy(m_tx_buf,buff,(len_temp+2));//���ͱ�ǩ��Ϣ������
			printf("%s",buff);
		}
	}
}













