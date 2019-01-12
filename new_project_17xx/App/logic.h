#ifndef _logic_h
#define _logic_h
#include "base.h"

#define			dlen				250
#define			Target				0x2a//表示标签信息
#define			Sett				0x5a//表示设置信息


#pragma pack(push,1)
typedef struct{
	u8 obuf[dlen];//带出数据
	u8 bbuf[dlen];//备份数据
}_DATA;
#pragma pack(pop)
extern _DATA	Data;



void CacheRxProcess(void);
void CacheTxProcess(void);
void BluetoothProcess(void);
void Uart3Process(void);
u8 target_fun(u8 datatype,u8 *data);


#endif

