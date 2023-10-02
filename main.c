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

void ddlay(uint32_t sec){

	
	while(sec){
		int Z=9;
		while(Z){
			Z--;
		}
		sec--;
	}
}
  
  int a=1;
  int k=1,l=1;

int main(void)
{
	LED_config();
	Systicks_Init();
	
	UR_config();

	//UR_Print("12345\n\r");
	
	//
	/*Systicks_Init();
	
	while(1){
	
	delay(1000);
	RED();
	delay(1000);
	BLUE();
	delay(1000);
	}*/
	//deQueue();
	while(k);
	while(1){
		
	RED();
	delay(1000);	
	
	// Fails because front = -1
  
	
  if(a==1){
		a=0;	
	ddlay(0xFFFF);
	ddlay(0xFFFF);
	ddlay(0xFFFF);
	ddlay(0xFFFF);
	ddlay(0xFFFF);
	ddlay(0xFFFF);
	ddlay(0xFFFF);
	ddlay(0xFFFF);
	ddlay(0xFFFF);
	ddlay(0xFFFF);
	ddlay(0xFFFF);
	ddlay(0xFFFF);	
	deQueue();
	ddlay(0x03);
  enQueue(1);
	ddlay(0x03);
  enQueue(2);
	ddlay(0x03);
  enQueue(3);
	ddlay(0x03);
  enQueue(4);
	ddlay(0x03);
  enQueue(5);
	ddlay(0x03);
  // Fails to enqueue because front == 0 && rear == SIZE - 1
  enQueue(6);
	ddlay(0x03);
  
	
  display();
	ddlay(0x03);
	
  deQueue();
	ddlay(0x03);
  
	display();
	ddlay(0x03);
	
	
  enQueue(7);
	ddlay(0x03);
	
  display();
	ddlay(0x03);
  
	// Fails to enqueue because front == rear + 1
  enQueue(8);
	}
	
	
	GREEN();
	ddlay(0xFFFF);
	}
	while(1);
  return 0;
 
}



