#include "QUEUE.h"

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
    if (isFull())
				UR_Print("\n Queue is full!! \n");
        
    else {
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        items[rear] = element;
				UR_Print("\n Inserted ->");
				UR_Print(&items[rear]);
       
    }
}

// Removing an element
int deQueue() {
    char element;
    if (isEmpty()) {
      UR_Print("\n Queue is empty !! \n");  
			
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
        UR_Print("\n Deleted element ->"); 
				UR_Print(&element);
				
        return (element);
    }
}

// Display the queue
void display() {
    int i;
    if (isEmpty())
				UR_Print(" \n Empty Queue\n"); 
        
    else {
        UR_Print("\n Front ->");
				UR_Print(&front);
				
        for (i = front; i != rear; i = (i + 1) % SIZE) {
            UR_Print(&items[i]);
						
        }
        UR_Print(&items[i]);
				UR_Print("\n Rear ->");
				UR_Print(&rear);
        
    }
}