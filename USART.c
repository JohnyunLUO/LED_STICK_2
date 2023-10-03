#include "USART.h"
#include "LED.h"
#include "QUEUE.h"

void UR_config(){	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,  ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,  ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;             

  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;  

  GPIO_InitStruct.GPIO_Mode= GPIO_Mode_AF_PP;    
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;             

  GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IN_FLOATING;    
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	USART_InitTypeDef USART_InitStruct;

	USART_InitStruct.USART_BaudRate=115200 ;            /*!< This member configures the USART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

  USART_InitStruct.USART_WordLength=USART_WordLength_8b ;          /*!< Specifies the number of data bits transmitted or received in a frame.
																																	This parameter can be a value of @ref USART_Word_Length */

  USART_InitStruct.USART_StopBits=USART_StopBits_1;            /*!< Specifies the number of stop bits transmitted.
																															This parameter can be a value of @ref USART_Stop_Bits */

  USART_InitStruct.USART_Parity=USART_Parity_No;              /*!< Specifies the parity mode.
																													This parameter can be a value of @ref USART_Parity
																													@note When parity is enabled, the computed parity is inserted
																												 at the MSB position of the transmitted data (9th bit when
																												 the word length is set to 9 data bits; 8th bit when the
																												 word length is set to 8 data bits). */
 
  USART_InitStruct.USART_Mode=USART_Mode_Rx |USART_Mode_Tx ;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
																																						This parameter can be a value of @ref USART_Mode */

	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None; /*!< Specifies wether the hardware flow control mode is enabled
																						 or disabled.
																						 This parameter can be a value of @ref USART_Hardware_Flow_Control */
	
	
	USART_Init(USART1,&USART_InitStruct);
	
	//USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	//USART_ClearFlag(USART1,USART_FLAG_ORE);
	
	USART_Cmd(USART1,  ENABLE);
	
	
}

void UR_NVIC_config(){
	
	NVIC_InitTypeDef NVIC_InitStruct;
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_SetPriority(SysTick_IRQn, 0);
	
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn ;                    /*!< Specifies the IRQ channel to be enabled or disabled.
                                                   This parameter can be a value of @ref IRQn_Type 
                                                   (For the complete STM32 Devices IRQ Channels list, please
                                                    refer to stm32f10x.h file) */

  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1 ;  /*!< Specifies the pre-emption priority for the IRQ channel
                                                   specified in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15 as described in the table @ref NVIC_Priority_Table */

  /*NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;        !< Specifies the subpriority level for the IRQ channel specified
                                                   //in NVIC_IRQChannel. This parameter can be a value
                                                   between 0 and 15 as described in the table @ref NVIC_Priority_Table */

  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;         /*!< Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                                   will be enabled or disabled. 
                                                   This parameter can be set either to ENABLE or DISABLE */  

	NVIC_Init(&NVIC_InitStruct);
}

void UR_Print(const char *Data){
	
	
	while(*Data!='\0'){
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==0);
	USART_SendData(USART1,*Data);
	
	Data++;
	}
}
char receive[128]="0";

char* UR_receive(void){
	
	int i=0;
			
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)){
		
		receive[i]=(char)(USART_ReceiveData(USART1));
		USART_SendData(USART1,receive[i]);
		i++;
	return receive;	
	}
	return 0;
}

void USART1_IRQHandler(void)
{	int i=0;
	char *enter="\n\r";
	uint16_t c=0;
	LedGreenToggle();
	if(USART_GetITStatus(USART1, USART_IT_RXNE)){
		c = USART_ReceiveData(USART1);
		USART_SendData(USART1,c);
		if(c!='\r'){
			 enQueue(c);
		}
		else{
			for(i=0;i<2;i++){
				 enQueue(enter[i]);
			}
			
		}
		
	}
}