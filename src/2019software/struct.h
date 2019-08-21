//#pragma once
#ifndef _INC_STRUCTURE
#define _INC_STRUCTURE
#include <stdio.h>
#define MAXCROSS 200//·�ڵ��������
#define MAXCAR   10400//�����������
#define MAXROAD  500//��·���������
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 200  //ͼ�еĽڵ�����Ҫ��ʵ�ʵĴ�һЩ,Ҳ����·�ڵ�����,�����300��֮������ջ�������400�����У������
#define MAXSIZE 60  //���еĳ��ȣ���BFS�����õ���
#define MAXINT 999999999 //dist�ĳ�ʼֵ����Ϊ�����
//��·��������
extern int c1, c2;//��·����ʼ·�ںź���ֹ·�ں�
extern int IDRoad[MAXCROSS+1][MAXCROSS+1];//ÿ����·�ڼ�ĵ�·���
extern int lenRoad[MAXCROSS+1][MAXCROSS+1];//����·�ڼ�ĵ�·����
extern int spdRoad[MAXCROSS][MAXCROSS];//��·����
extern int numpathRoad[MAXCROSS][MAXCROSS];//������Ŀ
extern int srcID[MAXCROSS];//ĳ����·����ʼ·��
extern int desID[MAXCROSS];//ĳ����·���յ�·��
extern int douRoad[MAXCROSS];//��·�Ƿ���˫�򳵵�,1��˫��,0������


//·�ڱ�������//
extern int IDCross[MAXCROSS][2];//ĳ��·��˳ʱ��ת�ĵ�һ�͵ڶ�����·��Ŷ�Ӧ��·�ںţ�ĳ��·�ڵ��Ϸ�����ҷ����·��ű��Ψһ��ȷ�����·�ڣ�
extern int IDCross1[MAXCROSS];//������ͼ����·����Ϣ
extern int IDroadCross[MAXCROSS][4];//·��������·�ı�ţ�ע��˳ʱ��洢��˳��
extern int numLine1 ;//road.txt�ļ������е�����(Ҳ���ǵ�·��)
extern int numLine2 ;//car.txt�ļ������е�������Ҳ���ǳ�������
extern int numLine3 ;//cross.txt�ļ������е�������Ҳ����·������

extern int tempcar;//��һ�����ı��


//////////ջ�Ľṹ������///////////////////
//typedef struct stack
//{
//	int *top;//������int��Ϊ����ʵ�����Ǹ���ջ�д�ŵ�Ԫ��������,ָ��ջ��
//	int *base;//ջ��ָ�룬ָ��ջ�ף��㷨�����϶�û����һ��
//	int stacksize;//ջ�Ĵ�С����ʼ��ջʱ�����
//}Stack;
//
//////����Ľṹ������/////////////////
//typedef struct List
//{
//	int key;//�������ʵ����������Ҫ��ŵ�����
//	struct List *prev;//prev��ָ�������ָ�������е�ǰԪ�ص���һ��Ԫ��
//	struct List *next;//next��ָ�������ָ�������е�ǰԪ�ص���һ��Ԫ��
//}List;
//
//////ͼ���ڽӾ���ṹ������///////////////////
typedef struct MGraph
{
	int  vex[MAXVEX]; // �����
	int  arc[MAXVEX][MAXVEX];//ÿ�����ϵ�Ȩ�أ�������Ȩͼ��˵������0��1����ʾ�Ƿ������������ڵ������ı�
	int  roadlen1[MAXVEX+1][MAXVEX+1];//ÿ��·�ĳ���
	int verNum;//ͼ�н����
	int edgeNum;//����
}MGraph;
//
/////////ͼ�б��Ͻڵ�Ľṹ������//////////////////
//typedef struct EdgeNode
//{
//	int adjvex;     // �洢�ö����Ӧ���±꣬the location of the vertex which was pointed by edge
//	int  info;    //���������洢�ýڵ��ֵ�������������е����
//	struct EdgeNode * next;  //�ʹ˽ڵ���������һ���ڵ�
//	struct EdgeNode * prev;  //�˽ڵ����������ͷ�ڵ�
//}EdgeNode;
//
/////////ͼ�ж���ڵ�Ľṹ������//////////////////
//typedef struct VertexNode
//{
//	// ͳ��ÿ����������
//	int in;
//	int data;
//	EdgeNode * firstedge;
//}VertexNode, AdjList[MAXVEX];
//
//////////ͼ���ڽ�����ṹ������///////////////////
//typedef struct LGraph
//{
//	int numNodes;//ͼ�нڵ���
//	int numEdges;//����
//	AdjList adjList;//����һ��AdjList���͵����飬ÿ������Ԫ�ض���һ����������Ԫ�صĸ���ΪMAXVEX
//}LGraph, *LGraphAdjListLink; // �����ڽӱ��ָ��
//
////////���еĽṹ������//////////////////////////
///**�����õ������ݽṹ����
//ʹ�õ���ѭ������ (�ж϶������ķ���Ϊ��һ��λ��)**/
//typedef struct Queue
//{
//	int data[MAXSIZE]; //������ű����ʵĽ��
//	int front; //��ͷ�±�
//	int rear;  //��β�±�
//}Queue;

//////////�����ṹ������//////////////////////////
typedef struct Car
{
	//������������//
	// int ID[MAXCROSS][MAXCROSS];//ʼ��·�ڶ�Ӧ�ĳ������
	 int carid;  //����ID
	 int srcCross;//������ʼ��·��
	 int desCross;//������Ŀ��·��
	 int maxspeed;//����������ٶ�
	 int curspeed;//������ǰ�ٶ�
	 int plantime;//�����ļƻ�����ʱ��
	 int actualtime;//������ʵ�ʳ���ʱ��
	 int runtime;//������ǰ��ʻʱ��
	 int curIDRoad;//������ǰ���ڵĵ�·���
	 int curIDpath;//������ǰ���ڳ������
	 int status ;//��ǰ������״̬
	 int dis; //С����ǰ����ʻ�ľ���
	 int startflag;//����������־
	// int cartimeid[11][MAXCAR];//ĳ��ʱ�̳��������г�����id
	 //int cartimenum[11];//ĳ��ʱ�̳���������
}Car;


///////////Int�;���ռ�(��ά����)��̬����//////////////////////
//int **matrixINT(int row, int column)
//{
//	int **m;
//	int i = 0;
//	m = (int **)malloc(row*sizeof(int*));
//	if (m == NULL)
//	{
//		printf("������䶯̬�ڴ�ռ�ʧ��");
//		return 0;
//	}
//	for (i = 0; i < row; i++)
//		m[i] = (int *)malloc(column*sizeof(int));
//	return m;
//}
#endif