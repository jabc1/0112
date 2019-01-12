#ifndef _setting_h
#define _setting_h
#include "base.h"

//0x0000-0x31fff----->用于运行程序
//0x3200-0x40000----->用于保存设置
//200k开始---256k结束
#define			setferadd			((0xc8+0)*1024)//设置频率
#define			setmacadd			((0xc8+1)*1024)//设置地址码
#define			setspeedadd			((0xc8+2)*1024)//设置速度
#define			setchadd			((0xc8+3)*1024)//设置通道

#define			setsendchadd		((0xc8+4)*1024)//设置发送通道
#define			setsendpowadd		((0xc8+5)*1024)//设置发送功率



u8 set_fun(u8 datatype,u8 *data);
u8 sel_fun(u8 datatype,u8 *data);
u8 set_fer(u8 *data);
u8 set_mac(u8 *data);
u8 set_speed(u8 *data);
u8 set_ch(u8 *data);
u8 sel_data(u8 *data);





#endif















