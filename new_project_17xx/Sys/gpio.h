#ifndef _gpio_h
#define _gpio_h
#include "lpc17xx_gpio.h"
#include "base.h"

#define		LED2				1
#define		LED2_PIN			1<<24






#define		GPIO_OUT			1
#define		GPIO_IN				0

#define		SET_GPIO_OUT(x)		GPIO_SetDir(x,x##_PIN,GPIO_OUT)
#define		SET_GPIO_IN(x)		GPIO_SetDir(x,x##_PIN,GPIO_IN)
#define		SET_GPIO_H(x)		GPIO_SetValue(x,x##_PIN)
#define		SET_GPIO_L(x)		GPIO_ClearValue(x,x##_PIN)

#define		ReadGPIO(x)			GPIO_ReadValue(x)&(1<<x##_PIN)//���ܽž�Ȼ����


void LPC_GPIO_init(void);
void LED_toggle(void);


#endif

