#ifndef _analysis_h
#define _analysis_h
#include "fifo.h"
#define			HEAD			0x7e
#define			Soft_ver		0x01//����汾

#define			settype			0x1a//������������
#define			seltype			0x2a//��ѯ��������

#define			setfer			0xa0//����Ƶ��
#define			setmac			0xa1//���õ�ַ��
#define			setspeed		0xa2//�����ٶ�
#define			setch			0xa3//����ͨ��

#define			setsendch		0xb0//���÷���ͨ��
#define			setsendpow		0xb1//���÷��͹���

#define			selinfo			0xc0//��ѯ��ǩ��Ϣ

#pragma pack(push,1)
typedef struct{
	u8 head;
	u8 len;
	u8 softver;
	u8 cmdtype;
	u8 datatype;
	u8 dbuff[240];//�����������֧��240byte
}_Pack;
#pragma pack(pop)


u8 Analysis_function(u8 *cmdtype,u8 *datatype,u8 *outdata,u8 *indata,u8 *len);
u8 Unpack(u8 cmdtype,u8 datatype,u8 *data,u8 datalen);
u8 Unpack_target(u8 ch,u8 *data,u8 datalen);
u8 info_out_fifo(FIFO_t *fifoytpe,u8 *len,u8 *data);



#endif



