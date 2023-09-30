#include"LED.h"

void GREEN(void){

	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
}

void BLUE(void){

	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
}


void RED(void){

	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_1);
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
}
