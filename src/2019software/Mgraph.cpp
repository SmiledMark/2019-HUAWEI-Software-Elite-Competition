#include<stdio.h>
#include"struct.h"

/**ʹ���ڽӾ���Ĺ���ͼ**/
//�������ַ�ʽֻ������һ�֣�������Щarc[][]��ֵ������ʵ�δ��ݹ����ģ�����ǱȽ�ʵ�õķ�ʽ��
MGraph* CreateMGraph(MGraph *G)
{
	int i, j,k,m;
	G->edgeNum= numLine1;//�ߵ������ͽ���������ʵ��ʵ�δ��ݹ����ȽϺ�
	G->verNum = numLine3;
	// ���붥��Ľ�㣬ע��ͼ��������ݲ�һ������0��1��2��3....��Щ���ܶ��������A,B,C...�������������Ҫ����������д
	for (k = 0; k < G->verNum; k++)
	{
		G->vex[k] = IDCross1[k];
	}

	//// �ڽӾ����ʼ��
	//for (i = 0; i < G->verNum; i++){
	//	for (j = 0; j < G->verNum; j++) {
	//		G->arc[i][j] = 0;
	//	}
	//}

	// �ڽӾ����ʼ��,�����еĵ�·��Ŷ���ʼ��Ϊ0����һЩ
	for (i = 0; i < MAXCROSS; i++) {
		for (j = 0; j < MAXCROSS; j++) {
			G->arc[i][j] = MAXINT;
		}
	}
	
	//����ͼ�бߵ���Ϣ������ָ���ǵ�·���
	for (i = 0; i < G->verNum; i++) {
		for (j = 0; j < G->verNum; j++) {
			G->arc[i][j] = IDRoad[i + 1][j + 1];//����ط�ǣ����һ��ת����ϵ���ڵ��±궼�Ǵ�0��ʼ�ģ�����Ҫ��֤IDRoad[roadsrc][roaddes]
		}//��roadsrc��roaddes��һһ��Ӧ�Ĺ�ϵ��������ʵ��·���Ǵ�1��ʼ�Ĺ���ҪIDRoad[i+1][j+1]��������ͼ�е�ӳ���ʵ����ӳ����һ�µ�
	}

//��Ϊ������������ͼ�������ǶԳƵ�
	//for (i = 0; i < G->verNum; i++){
	//	for (j = i; j < G->verNum; j++)
	//		G->arc[j][i] = G->arc[i][j];
	//}
	return G;
	//int i, j;
	//G->edgeNum = 7;//�ߵ������ͽ���������ʵ��ʵ�δ��ݹ����ȽϺ�
	//G->verNum = 9;
	//// ���붥��Ľ�㣬ע��ͼ��������ݲ�һ������0��1��2��3....��Щ���ܶ��������A,B,C...�������������Ҫ����������д
	//G->vex[0] = 1;
	//G->vex[1] = 2;
	//G->vex[2] = 3;
	//G->vex[3] = 4;
	//G->vex[4] = 5;
	//G->vex[5] = 6;
	//G->vex[6] = 7;
	//G->vex[7] = 8;
	//G->vex[8] = 9;
	//G->vex[9] = 10;
	//G->vex[10] = 11;
	//// �ڽӾ����ʼ��
	//for (i = 0; i < MAXVEX; i++) {
	//	for (j = 0; j < MAXVEX; j++) {
	//		G->arc[i][j] = MAXINT;
	//	}
	//}
	//// �������ͼ
	//G->arc[0][2] = 1;
	//G->arc[0][1] = 1;
	//G->arc[2][5] = 1;
	//G->arc[1][3] = 1;
	//G->arc[1][4] = 1;
	//G->arc[6][3] = 1;
	//G->arc[4][7] = 100;
	//G->arc[5][8] = 1;
	//G->arc[7][9] = 1;
	//G->arc[10][9] = 1;
	//G->arc[8][10] = 1;
	////G->arc[7][8] = 1;
	///*G->arc[3][7] = 1;
	//G->arc[3][6] = 1;
	//G->arc[3][8] = 1;
	//G->arc[4][5] = 1;
	//G->arc[4][7] = 1;
	//G->arc[5][6] = 1;
	//G->arc[6][7] = 1;*/
	////��Ϊ������������ͼ�������ǶԳƵ�
	//	//for (i = 0; i < G->verNum; i++){
	//	//	for (j = i; j < G->verNum; j++)
	//	//		G->arc[j][i] = G->arc[i][j];
	//	//}
	//return G;
}