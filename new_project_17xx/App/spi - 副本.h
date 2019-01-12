#ifndef _psi_h
#define _psi_h

#define		SPI_CHILDNUM				 4


#define		CS_PORT_NUM1				0
#define		CS_PIN_NUM1					6
#define		CS_PORT_NUM2				2
#define		CS_PIN_NUM2					2
#define		CS_PORT_NUM3				2
#define		CS_PIN_NUM3					3
#define		CS_PORT_NUM4				2
#define		CS_PIN_NUM4					6

#define		SCK_PIN_NUM					7
#define		MISO_PIN_NUM				8
#define		MOSI_PIN_NUM				9


#define		SPI_DATABIT_SIZE			8

#define		SPI_RATE 					(2000000*2)

void LPC17XXSPI_Init();
void LPC17XXSPI_Process();

#endif





