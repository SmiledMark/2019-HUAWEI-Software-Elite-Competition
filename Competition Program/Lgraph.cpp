#include<stdio.h>
#include<stdlib.h>
#include"struct.h"

LGraph* CreateALGraph(MGraph G, LGraph*  GL){

	int i, j;

	EdgeNode * e;
	//GL = (LGraphAdjListLink)malloc(sizeof(LGraph));


	 GL = (LGraph*)malloc(sizeof(LGraph));
	(GL)->numEdges = G.edgeNum; 
	(GL)->numNodes = G.verNum;

	// ���ɶ����
	for (i = 0; i <G.verNum; i++) /* ���붥����Ϣ,��������� */
	{
		(GL)->adjList[i].in = 0;
		(GL)->adjList[i].data = G.vex[i];
		(GL)->adjList[i].firstedge = NULL;   //��ÿ�������ͷ�ڵ��ַ��ΪNULL//
	}


	// �������ڽӱ������ݸ���е��Ʊʼǡ���д�ʼǡ�
	for (i = 0; i < G.verNum; i++){
		for (j = 0; j < G.verNum; j++) {
			if (G.arc[i][j] != 0&& G.arc[i][j] != MAXINT){

				e = (EdgeNode *)malloc(sizeof(EdgeNode));

				e->adjvex = j;

				e->next = (GL)->adjList[i].firstedge;


				(GL)->adjList[i].firstedge = e;
				(GL)->adjList[j].in++; // ������ȼ�1

			}
		}
	}
	return GL;
}
