
#include<stdio.h>
#include<stdlib.h>
#include "struct.h"
// 各数组都从下标1开始
//int dist[maxnum];     // 表示当前点到源点的最短路径长度
//int prev1[maxnum];     // 记录当前点的前一个结点
//int c[maxnum][maxnum];   // 记录图的两点间路径长度        // 图的结点数和路径数
// n -- n nodes
// v -- the source node
// dist[] -- the distance from the ith node to the source node
// prev[] -- the previous node of the ith node
// c[][] -- every two cross' distance
int* Dijkstra(int n, int src,   int c[MAXCROSS+1][MAXCROSS+1])
{
	int dist[MAXCROSS +1]; //the distance between current cross and source cross
	int* prev1;     // record the previous cross of current cross
    prev1=(int*)malloc((MAXCROSS+1)*sizeof(int));//虽然一条路径的prev1里面只有几个元素但是prev1的下标范围是1-MAXCROSS，所以分配的空间必须这么大
	bool s[MAXCROSS +1];    // 判断是否已存入该点到S集合中
	for (int i = 1; i <= n; ++i)//这里应该减36
	{
		dist[i] = c[src][i];
		s[i] = 0;     // 初始都未用过该点
		if (dist[i] == MAXINT)//初始时将所有的c[i][j]初始化为maxint
			prev1[i] = -1;//也就是暂时没有前驱
		else
			prev1[i] = src;//先将与源点相连节点的前驱置为源点，注意dist调整时有可能会变化前驱节点
	}
	dist[src] = 0;
	s[src] = 1;
	// 依次将未放入S集合的结点中，取dist[]最小值的结点，放入集合S中
	// 一旦S包含了所有V中顶点，dist就记录了从源点到所有其他顶点之间的最短路径长度
	// 注意是从第二个节点开始，第一个为源点
	//每进行一次下面的for循环，就有一个节点变为已知的假如集合S，由于源点已经在集合S，故这里i从1开始只进行路口数减1次循环即可
	for (int i = 1; i < n; ++i)
	{
		int tmp = MAXINT;
		int u = src;//这里的赋值感觉没有什么实际意义
		// 找出当前未使用的点j的dist[j]最小值
		for (int j = 1; j <= n; ++j)
			if ((!s[j]) && dist[j] < tmp)
			{
				u = j;              // u保存当前邻接点中距离最小的点的号码
				tmp = dist[j];
			}
		s[u] = 1;    //u变为已知u点已存入S集合中

		// 更新dist，这里也一定要写一写，所有未知的节点都会进行dist[u] + c[u][j]和dist[j]的比较，当然只有与u相连的才有可能newdist<dist[j]
		for (int j = 1; j <= n; ++j)//不与u相连的c[u][j]=MAXINT,怎么可能满足newdist<dist[j],如果满足newdist < dist[j]，那么j的前驱节点变为
			if ((!s[j]) && c[u][j] < MAXINT)//u,并且更新dist[j]的值为dist[u] + c[u][j]
			{
				int newdist = dist[u] + c[u][j];
				if (newdist < dist[j])
				{
					dist[j] = newdist;
					prev1[j] = u;
				}
			}
	}
	return prev1;
}

// 查找从源点v到终点u的路径，并输出
int* searchPath(int *prev1, int src, int des)
{
	int* lujing=NULL;//用来临时存储节点的编号
        lujing=(int*)malloc(sizeof(int)*(MAXCROSS+1));
	for (int i = 0; i < MAXCROSS; i++)
	{
		lujing[i] = -1;//将路径初始化为-1
	}
	int tot = 1;//注意tot是从1开始的
	//src = src - 1;//实际中路口的1节点对应程序中的0节点，因为数组是从0开始的，如果实际中路口的节点是从36开始的那么你若想以36为源节点那么
	//des = des - 1;//这里应该减36
	lujing[tot] = des;
	tot++;
	int tmp = prev1[des];
	while (tmp != src)
	{
		lujing[tot] = tmp;
		tot++;
		tmp = prev1[tmp];
	}
	lujing[tot] = src;
	/*for (int i = tot; i >= 1; --i)
		if (i != 1)
			//cout << lujing[i] << " -> ";
			printf("%d->", lujing[i]);
		else
			//cout << lujing[i] << endl;
			printf("%d", lujing[i]);*/
        return lujing;
}

