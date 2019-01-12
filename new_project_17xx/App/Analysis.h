#ifndef _analysis_h
#define _analysis_h
#include "fifo.h"
#define			HEAD			0x7e
#define			Soft_ver		0x01//软件版本

#define			settype			0x1a//设置命令类型
#define			seltype			0x2a//查询命令类型

#define			setfer			0xa0//设置频率
#define			setmac			0xa1//设置地址码
#define			setspeed		0xa2//设置速度
#define			setch			0xa3//设置通道

#define			setsendch		0xb0//设置发送通道
#define			setsendpow		0xb1//设置发送功率

#define			selinfo			0xc0//查询标签信息

#pragma pack(push,1)
typedef struct{
	u8 head;
	u8 len;
	u8 softver;
	u8 cmdtype;
	u8 datatype;
	u8 dbuff[240];//命令内容最大支持240byte
}_Pack;
#pragma pack(pop)


u8 Analysis_function(u8 *cmdtype,u8 *datatype,u8 *outdata,u8 *indata,u8 *len);
u8 Unpack(u8 cmdtype,u8 datatype,u8 *data,u8 datalen);
u8 Unpack_target(u8 ch,u8 *data,u8 datalen);
u8 info_out_fifo(FIFO_t *fifoytpe,u8 *len,u8 *data);



#endif



