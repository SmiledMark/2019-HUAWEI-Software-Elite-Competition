#include<stdio.h>
#include "struct.h"

/////////////���г�ʼ��//////////////
void InitQueue(Queue * q)
{
	q->front = 0;
	q->rear = 0;
}

/////�ж϶����Ƿ�Ϊ�գ���1���ǿ�0////
int  QueueEmpty(Queue q){
	if (q.front == q.rear)
		return TRUE;
	else
		return FALSE;
}

///////////////���eΪ���Ԫ��//////////////////
int  EnQueue(Queue * Q, int e)
{
	// ������������
	if ((Q->rear + 1) % MAXSIZE == Q->front) 
	   return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

///////////////����eΪ����Ԫ��//////////////////
int DeQueue(Queue *q, int *e){

	// ���пյ������ж�

	if (q->front == q->rear)
		return ERROR;

	*e = q->data[q->front];

	q->front = (q->front + 1) % MAXSIZE;

	return OK;
}
