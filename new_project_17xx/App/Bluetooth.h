#ifndef _bluetooth_h
#define _bluetooth_h
#include "gpio.h"
#include "base.h"
#include "fifo.h"

#define		BLE_RST							1
#define		BLE_RST_PIN						1<<18
#define		BLE_WAKEUP						1
#define		BLE_WAKEUP_PIN					1<<26
#define		BLE_STATUS						1
#define		BLE_STATUS_PIN					1<<19
#define		GET_BT_STATUS()					(LPC_GPIO1->FIOPIN&BLE_STATUS_PIN)
#define		ACK								"+OK"
#define		BT_NAME							"AT+NAMEzydBLE111"

#define		BLESOF							0xa5



#pragma pack(push,1)
typedef struct
{
	u8 linkf;
	u8 buff[20];
	u8 pass[6];
	u8 ValidCode;//连接蓝牙标志位
	u32 status;
}_BLE;
typedef struct
{
	u8 SOF;
	u8 Addr;
	u8 Len;
	u8 Cmd;
	u8 Parameters[120];
}_Cmd_Frame;
typedef struct
{
	u8 SOF;
	u8 Addr;
	u8 Len;
	u8 Status;
	u8 Response[120];
}_Response_Frame;
#pragma pack(pop)

extern _BLE Parameter_Ble;

void BluetoothProcess(void);
void ble_start(void);
void ble_function(void);
void get_ble_status(void);
void Bluetooth_init(void);
void ble_failed(void);
void send_str(u8 *str);
void send_str_len(u8 *str,u8 len);
u8* ble_check_cmd(u8 *str);
u8 ble_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
u8 ble_target_unpack(u8 ch,u8 *data,u8 len);
u8 out_fifo_data(FIFO_t *fifoytpe,u8 *len,u8 *data);
#endif







