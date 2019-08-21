#include<stdio.h>
#include"struct.h"

/**使用邻接矩阵的构建图**/
//下面这种方式只是其中一种，比如那些arc[][]的值都是由实参传递过来的，这才是比较实用的方式。
MGraph* CreateMGraph(MGraph *G)
{
	int i, j,k,m;
	G->edgeNum= numLine1;//边的数量和结点的数量其实由实参传递过来比较好
	G->verNum = numLine3;
	// 输入顶点的结点，注意图顶点的内容不一定就是0，1，2，3....这些，很多情况下是A,B,C...这种情况，所以要按下面那样写
	for (k = 0; k < G->verNum; k++)
	{
		G->vex[k] = IDCross1[k];
	}

	//// 邻接矩阵初始化
	//for (i = 0; i < G->verNum; i++){
	//	for (j = 0; j < G->verNum; j++) {
	//		G->arc[i][j] = 0;
	//	}
	//}

	// 邻接矩阵初始化,将所有的道路编号都初始化为0更好一些
	for (i = 0; i < MAXCROSS; i++) {
		for (j = 0; j < MAXCROSS; j++) {
			G->arc[i][j] = MAXINT;
		}
	}
	
	//读入图中边的信息在这里指的是道路编号
	for (i = 0; i < G->verNum; i++) {
		for (j = 0; j < G->verNum; j++) {
			G->arc[i][j] = IDRoad[i + 1][j + 1];//这个地方牵扯到一个转换关系，节点下标都是从0开始的，我们要保证IDRoad[roadsrc][roaddes]
		}//中roadsrc和roaddes有一一对应的关系，在这里实际路口是从1开始的故需要IDRoad[i+1][j+1]才能满足图中的映射和实际中映射是一致的
	}

//因为构建的是无向图，所以是对称的
	//for (i = 0; i < G->verNum; i++){
	//	for (j = i; j < G->verNum; j++)
	//		G->arc[j][i] = G->arc[i][j];
	//}
	return G;
	//int i, j;
	//G->edgeNum = 7;//边的数量和结点的数量其实由实参传递过来比较好
	//G->verNum = 9;
	//// 输入顶点的结点，注意图顶点的内容不一定就是0，1，2，3....这些，很多情况下是A,B,C...这种情况，所以要按下面那样写
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
	//// 邻接矩阵初始化
	//for (i = 0; i < MAXVEX; i++) {
	//	for (j = 0; j < MAXVEX; j++) {
	//		G->arc[i][j] = MAXINT;
	//	}
	//}
	//// 随机生成图
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
	////因为构建的是无向图，所以是对称的
	//	//for (i = 0; i < G->verNum; i++){
	//	//	for (j = i; j < G->verNum; j++)
	//	//		G->arc[j][i] = G->arc[i][j];
	//	//}
	//return G;
}
