#ifndef _uart_h
#define _uart_h
#include "lpc17xx_uart.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_pinsel.h"
#include "base.h"
#define UART3SEL	((2)|(2<<2))					//p0.0,p0.1
#define IER_RBR		0x01
#define IER_THRE	0x02
#define IER_RLS		0x04


#define IIR_PEND	0x01
#define IIR_RLS		0x03
#define IIR_RDA		0x02
#define IIR_CTI		0x06
#define IIR_THRE	0x01

#define LSR_RDR		0x01
#define LSR_OE		0x02
#define LSR_PE		0x04
#define LSR_FE		0x08
#define LSR_BI		0x10
#define LSR_THRE	0x20
#define LSR_TEMT	0x40
#define LSR_RXFE	0x80



void EnableIrq(void);
void DisableIrq(void);
void uart_config0(uint32_t Baud_rate);
void uart_config3(uint32_t Baud_rate);
void USART3_Printf(const char *fmt, ...);

#endif


