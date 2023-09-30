#ifndef USART_H
#define USART_H

#include "stm32f10x.h"
#include "GPIO_STM32F10x.h"


#endif

void UR_config(void);
void UR_NVIC_config(void);
void UR_Print(const char *Data);
char* UR_receive(void);
