#include "stm32f10x.h"
#include "GPIO_STM32F10x.h"
#include <stdio.h>
#include "LED.h"
#include "USART.h"
#include "QUEUE.h"

//#include ""


void LED_config(){
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

volatile uint32_t msTicks = 0;

/**
 * @brief Interrupt handler function
 * 
 */
void SysTick_Handler(void)
{
	msTicks++;
}

/**
 * @brief Add blocking delay
 *
 * @param ms delay in milliseconds
 */
void delay(int ms)
{
	uint32_t expected_ticks = msTicks + ms;
	while (msTicks < expected_ticks)
	{
		__asm("nop");
	}
}

void Systicks_Init(){
	int ret = SysTick_Config(SystemCoreClock / 1000);
	if (ret < 0){
		while (1);
	}

}
int main(void)
{ 
  int k=1;
	LED_config();
	UR_config();
	
	UR_Print("12345");
	
	while(k);
	/*Systicks_Init();
	
	while(1){
	
	delay(1000);
	RED();
	delay(1000);
	BLUE();
	delay(1000);
	}*/
	// Fails because front = -1
  deQueue();
  GREEN();
	
  enQueue(1);
  enQueue(2);
  enQueue(3);
  enQueue(4);
  enQueue(5);

  // Fails to enqueue because front == 0 && rear == SIZE - 1
  enQueue(6);

  display();
  deQueue();

  display();

  enQueue(7);
  display();

  // Fails to enqueue because front == rear + 1
  enQueue(8);
	GREEN();
  return 0;
 
}



