#include "QUEUE.h"
#include "USART.h"


//#include "Systicks.h"

char items[SIZE];
int front = -1, rear = -1;

// Check if the queue is full
int isFull() {
    if ((front == rear + 1) || (front == 0 && rear == SIZE - 1)) return 1;
    return 0;
}

// Check if the queue is empty
int isEmpty() {
    if (front == -1) return 1;
    return 0;
}

// Adding an element
void enQueue(int element) {
    char buffer[SIZE]={0};
		if (isFull())
				UR_Print("\n\r Queue is full!! \n\r");
        
    else {
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        items[rear] = element;
				UR_Print("\n\r Inserted -> ");
			
				//UR_Print(&items[rear]+0x30);
				//USART_SendData(USART1,items[rear]+0x30);
			
			  sprintf(buffer,"%d",element);
				UR_Print(buffer);
    }
}

// Removing an element
int deQueue() {
    char element;
    if (isEmpty()) {
      UR_Print("\n\r Queue is empty !! \n\r");  
			
        return (-1);
    } else {
        element = items[front];
        if (front == rear) {
            front = -1;
            rear = -1;
        }
        // Q has only one element, so we reset the
        // queue after dequeing it. ?
        else {
            front = (front + 1) % SIZE;
        }
        UR_Print("\r\n Deleted element ->  "); 
				//UR_Print(&element);
				USART_SendData(USART1,element+0x30);
				UR_Print("\r\n");
        return (element);
    }
}

// Display the queue
void display() {
    int i;
    if (isEmpty())
				UR_Print(" \r\n Empty Queue\r\n"); 
        
    else {
        UR_Print("\r\n Front ->  ");
				//UR_Print(&front);
				USART_SendData(USART1,front+0x30);
				//delay(1000);
			
				UR_Print("\r\n Items -> ");
        for (i = front; i != rear; i = (i + 1) % SIZE) {
            //UR_Print(&items[i]);
			
					while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==0);
					USART_SendData(USART1,items[i]+0x30);  
					//The data transmitted using USART, whether it is in the form of an int or char, will be decoded using the ASCII table.
					//In here, we want to send "1". According to ASCII code table, here we have to send "1+0X30".																	
					//delay(1000);
					
				}
				
        USART_SendData(USART1,items[i]+0x30);
				
				UR_Print("\r\n Rear ->  ");
				//UR_Print(&rear);
        USART_SendData(USART1,rear+0x30);
    }
}