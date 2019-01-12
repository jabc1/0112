#ifndef _logic_h
#define _logic_h
#include "base.h"

#define			dlen				250
#define			Target				0x2a//��ʾ��ǩ��Ϣ
#define			Sett				0x5a//��ʾ������Ϣ


#pragma pack(push,1)
typedef struct{
	u8 obuf[dlen];//��������
	u8 bbuf[dlen];//��������
}_DATA;
#pragma pack(pop)
extern _DATA	Data;



void CacheRxProcess(void);
void CacheTxProcess(void);
void BluetoothProcess(void);
void Uart3Process(void);
u8 target_fun(u8 datatype,u8 *data);


#endif

