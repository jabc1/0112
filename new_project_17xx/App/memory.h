#ifndef _memory_h
#define _memory_h
#include "base.h"
#include "fifo.h"

#define		CacheLen		4*1024+1
#define		BleLen			512+1
#define		UartLen			2*1024+1
extern FIFO_t	CacheRx;
extern FIFO_t	CacheTx;
extern FIFO_t	BleCache;
extern FIFO_t	UartCache;


void Init_fifo(void);


#endif



