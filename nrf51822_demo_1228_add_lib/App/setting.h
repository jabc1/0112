#ifndef _setting_h
#define _setting_h
#include "base.h"

//0x0000-0x31fff----->�������г���
//0x3200-0x40000----->���ڱ�������
//200k��ʼ---256k����
#define			setferadd			((0xc8+0)*1024)//����Ƶ��
#define			setmacadd			((0xc8+1)*1024)//���õ�ַ��
#define			setspeedadd			((0xc8+2)*1024)//�����ٶ�
#define			setchadd			((0xc8+3)*1024)//����ͨ��

#define			setsendchadd		((0xc8+4)*1024)//���÷���ͨ��
#define			setsendpowadd		((0xc8+5)*1024)//���÷��͹���



u8 set_fun(u8 datatype,u8 *data);
u8 sel_fun(u8 datatype,u8 *data);
u8 set_fer(u8 *data);
u8 set_mac(u8 *data);
u8 set_speed(u8 *data);
u8 set_ch(u8 *data);
u8 sel_data(u8 *data);





#endif















