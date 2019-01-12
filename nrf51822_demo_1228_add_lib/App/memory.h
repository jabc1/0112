#ifndef _memroy_h
#define _memroy_h
#include "fifo.h"
#define			Uart0Tx_len				1024*2+1//Uart0 memory 4k
#define			Uart0Rx_len				512*1+1//Uart0 memory 1k
#define			Radiofifo_len			1024*2+1//radio memory 4k
#define			SPIRxlen				512*4+1//
#define			SPITxlen				512*4+1//

extern FIFO_t	Uart0Tx;
extern FIFO_t	Uart0Rx;
extern FIFO_t	Radiofifo;
extern FIFO_t	SPITxfifo;
extern FIFO_t	SPIRxfifo;

void Init_fifo(void);




#endif






