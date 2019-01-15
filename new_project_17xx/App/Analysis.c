/************Copyright(C) Kaikai Technology 2018-05-14***********************
File name  : Analysis.c
Description: 主要实现命令解析和打包发送
Platform   : MDK V5.26.0.0
Version    : V1.0
Author	   : Jason
Create Time: 2019-01-07
Modify	   : 
Modify Time: 
******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "Analysis.h"
#include "crc.h"
#include "memory.h"

u8 Analysis_function(u8 *cmdtype,u8 *datatype,u8 *outdata,u8 *indata,u8 *len)
{
	_Pack *pbuff;
	u16 crc_temp;
	u16 *crc;
//	u8 *crc1,*crc2;
//	u8 temp1,temp2;
	pbuff = (_Pack *)indata;
	if((pbuff->head != HEAD)||(pbuff->softver != Soft_ver))
	{
		return false;
	}
	crc_temp = check_crc(&(pbuff->len),(pbuff->len-1),0xffff);
//	temp1 = crc_temp & 0xff;
//	temp2 = ((crc_temp >> 8) & 0xff);
	crc = (u16 *)((u8 *)pbuff+2+(pbuff->len-2));
//	crc1 = (u8 *)((u8 *)pbuff+2+(pbuff->len-2));
//	crc2 = (u8 *)((u8 *)pbuff+2+(pbuff->len-1));
//	if((*crc1 != temp1)||(*crc2 != temp2))
//	{
//		return false;
//	}
	if((*crc) != crc_temp)
	{
		return false;
	}
	*cmdtype = pbuff->cmdtype;
	*datatype = pbuff->datatype;
	memcpy(outdata,&(pbuff->dbuff),(pbuff->len - 5));
	return true;
}

u8 Unpack_target(u8 ch,u8 *data,u8 datalen)
{
	_Pack *pPack;
	u16 CRCValue;
	u16 *pCRCValueRegion;
	pPack = (_Pack *)malloc(datalen+7);
	pPack->cmdtype = 0x00;
	pPack->datatype = 0x00;
	if(pPack == NULL)
	{
		return false;
	}
	pPack->head = HEAD;
	pPack->len = 0x05+datalen;
	pPack->softver = Soft_ver;
	pPack->cmdtype = ch;//通道号
	pPack->datatype = ch;//通道号
	memcpy(&pPack->dbuff[0],data,datalen);
	CRCValue = check_crc(&(pPack->len),(pPack->len-1),0xffff);
	pCRCValueRegion = (u16 *)((u8 *)pPack + datalen + 5); 
	*pCRCValueRegion = CRCValue;
	if(!fifo_puts(&UartCache,(u8 *)pPack,datalen+7))//标签信息入队操作
	{
		free(pPack);
		return false;
	}
	free(pPack);
	return true;
}

u8 Unpack(u8 cmd,u8 cdata,u8 *data,u8 datalen)
{
	_Pack *pPack;
	u16 CRCValue;
	u16 *pCRCValueRegion;
	pPack = (_Pack *)malloc(datalen+7);
	if(pPack == NULL)
	{
		return false;
	}
	pPack->head = HEAD;
	pPack->len = 0x05+datalen;
	pPack->softver = Soft_ver;
	pPack->cmdtype = cmd;
	pPack->datatype = cdata;
	memcpy(&pPack->dbuff[0],data,datalen);
	CRCValue = check_crc(&(pPack->len),(pPack->len-1),0xffff);
	pCRCValueRegion = (u16 *)((u8 *)pPack + datalen + 5); 
	*pCRCValueRegion = CRCValue;
	if(!fifo_puts(&CacheTx,(u8 *)pPack,datalen+7))
	{
		free(pPack);
		return false;
	}
	free(pPack);
	return true;
}

u8 info_out_fifo(FIFO_t *fifoytpe,u8 *len,u8 *data)
{
	u8 length,head_temp;
	do{
		if (!fifo_getc(fifoytpe, &head_temp))
		{
			return false;
		}
	}while(head_temp != 0x7e);
	*data++ = head_temp;
	if(fifo_getc(fifoytpe, &length))
	{
		*data++ = length;
		if(!fifo_gets(fifoytpe,data,length))
		{
			return false;
		}
	}
	*len = length;
	return true;
}
















