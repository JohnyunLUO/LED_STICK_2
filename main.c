#include "stm32f10x.h"
#include "GPIO_STM32F10x.h"
#include <stdio.h>
#include "LED.h"
#include "USART.h"
#include "QUEUE.h"
#include "Systicks.h"

void LED_config(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5;             /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */

  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;  /*!< Specifies the speed for the selected pins.
                                      This parameter can be a value of @ref GPIOSpeed_TypeDef */

  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;    /*!< Specifies the operating mode for the selected pins.
                                      This parameter can be a value of @ref GPIOMode_TypeDef */
	
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_Write(GPIOB, 0xFF);

} 


  int a=0;
  int k=1,l=1;

int main(void)
{
	LED_config();
	Systicks_Init();
	
	UR_config();

	//UR_Print("12345\n\r");
	
	
	/*
	
	while(1){
	
	delay(1000);
	RED();
	delay(1000);
	BLUE();
	delay(1000);
	}*/
	//deQueue();
	//while(k);
	while(1){
		
	RED();
	delay(1000);	
	
	// Fails because front = -1
  
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1){
		a=1;
		BLUE();
		delay(3000);
	
	}
  if(a==1){
		a=0;
		
		deQueue();
		delay(1000);
		enQueue(1);
		delay(1000);
		enQueue(2);
		delay(1000);
		enQueue(3);
		delay(1000);
		enQueue(4);
		delay(1000);
		enQueue(5);
		delay(1000);
		// Fails to enqueue because front == 0 && rear == SIZE - 1
		enQueue(6);
		delay(1000);
		
		
		display();
		delay(1000);
		
		deQueue();
		delay(1000);
		
		display();
		delay(1000);
		
		
		enQueue(7);
		delay(1000);
		
		display();
		delay(1000);
		
		// Fails to enqueue because front == rear + 1
		enQueue(8);
	

	}
	
	
	GREEN();
	delay(1000);
	}
	while(1);
  return 0;
 
}



