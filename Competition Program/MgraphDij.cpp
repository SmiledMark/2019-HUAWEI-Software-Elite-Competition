#include <stdio.h>
#include "struct.h"
MGraph* MgraphDij(MGraph* GDij)
{
	//读入图中边的信息在这里指的是道路编号
	int i, j, k, m;
	//GDij->edgeNum = numLine1;//边的数量和结点的数量其实由实参传递过来比较好
	//GDij->verNum = numLine3;
	for (i = 1; i <= MAXCROSS; i++) {
		for (j = 1; j <= MAXCROSS; j++) {
			GDij->roadlen1[i][j] = lenRoad[i][j];//注意最开始时lenRoad初始化为MAXINT,然后才去读取文件.
		}
	}
	return GDij;


}