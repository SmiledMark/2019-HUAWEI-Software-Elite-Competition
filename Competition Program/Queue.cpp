#include<stdio.h>
#include "struct.h"

/////////////队列初始化//////////////
void InitQueue(Queue * q)
{
	q->front = 0;
	q->rear = 0;
}

/////判断队列是否为空，空1，非空0////
int  QueueEmpty(Queue q){
	if (q.front == q.rear)
		return TRUE;
	else
		return FALSE;
}

///////////////入队e为入队元素//////////////////
int  EnQueue(Queue * Q, int e)
{
	// 队列满的条件
	if ((Q->rear + 1) % MAXSIZE == Q->front) 
	   return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

///////////////出队e为出队元素//////////////////
int DeQueue(Queue *q, int *e){

	// 队列空的条件判断

	if (q->front == q->rear)
		return ERROR;

	*e = q->data[q->front];

	q->front = (q->front + 1) % MAXSIZE;

	return OK;
}
