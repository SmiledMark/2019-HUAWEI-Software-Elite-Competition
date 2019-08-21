#include <stdio.h>
#include "struct.h"

/** ���������� �������н��**/
/** ����:
1. ���α���������ÿ�����㣬��ֹ����ͨͼ�ĳ���
2. ����ö���û�з��ʣ�����ʸö��㣬
3. �ҵ���ö��������ĵ�һ���ٽ�㣬���еݹ飬���������� p ���ٽ��Ϊ��
4. �����ӵ�һ������ĵڶ����ڽӵ���б���
**/

//bool visited[MAXSIZE];
int visited[MAXSIZE];

void DFS(LGraphAdjListLink GL, int pos){

	EdgeNode *p;

	visited[pos] = TRUE;

	//cout << GL->adjList[pos].data << endl;
	printf("%d\n", GL->adjList[pos].data);
	p = GL->adjList[pos].firstedge;

	while (p) {

		if (!visited[p->adjvex])
			DFS(GL, p->adjvex);

		p = p->next;
	}
}

void DFSTraverse(LGraphAdjListLink GL){
	int i;
	for (i = 0; i < (GL)->numEdges; i++)
		visited[i] = FALSE;
	for (i = 0; i < GL->numNodes; i++) {
		if (visited[i] == FALSE){
			DFS(GL, i);
		}
	}

}
