//#pragma once
#ifndef _INC_STRUCTURE
#define _INC_STRUCTURE
#include <stdio.h>
#define MAXCROSS 200//路口的最大数量
#define MAXCAR   10400//车的最大数量
#define MAXROAD  500//道路的最大数量
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 200  //图中的节点数，要比实际的大一些,也就是路口的数量,这个比300大之后会出现栈溢出错误，400都不行，解决。
#define MAXSIZE 60  //队列的长度，在BFS中有用到。
#define MAXINT 999999999 //dist的初始值假设为无穷大
//道路变量设置
extern int c1, c2;//道路的起始路口号和终止路口号
extern int IDRoad[MAXCROSS+1][MAXCROSS+1];//每两个路口间的道路编号
extern int lenRoad[MAXCROSS+1][MAXCROSS+1];//两个路口间的道路长度
extern int spdRoad[MAXCROSS][MAXCROSS];//道路限速
extern int numpathRoad[MAXCROSS][MAXCROSS];//车道数目
extern int srcID[MAXCROSS];//某条道路的起始路口
extern int desID[MAXCROSS];//某条道路的终点路口
extern int douRoad[MAXCROSS];//道路是否是双向车道,1：双向,0：单向


//路口变量设置//
extern int IDCross[MAXCROSS][2];//某个路口顺时针转的第一和第二个道路编号对应的路口号（某个路口的上方向和右方向道路编号便可唯一的确定这个路口）
extern int IDCross1[MAXCROSS];//用来给图输入路口信息
extern int IDroadCross[MAXCROSS][4];//路口四条道路的编号，注意顺时针存储的顺序
extern int numLine1 ;//road.txt文件数据行的行数(也就是道路数)
extern int numLine2 ;//car.txt文件数据行的行数（也就是车辆数）
extern int numLine3 ;//cross.txt文件数据行的行数（也就是路口数）

extern int tempcar;//第一辆车的编号


//////////栈的结构体类型///////////////////
//typedef struct stack
//{
//	int *top;//这里以int型为例，实际上是根据栈中存放的元素来定的,指向栈顶
//	int *base;//栈底指针，指向栈底，算法导论上都没有这一个
//	int stacksize;//栈的大小，初始化栈时会给定
//}Stack;
//
//////链表的结构体类型/////////////////
//typedef struct List
//{
//	int key;//用来存放实际链表中需要存放的数据
//	struct List *prev;//prev是指针变量，指向链表中当前元素的下一个元素
//	struct List *next;//next是指针变量，指向链表中当前元素的下一个元素
//}List;
//
//////图的邻接矩阵结构体类型///////////////////
typedef struct MGraph
{
	int  vex[MAXVEX]; // 顶点表
	int  arc[MAXVEX][MAXVEX];//每条边上的权重，对于无权图来说可以用0，1来表示是否有由这两个节点相连的边
	int  roadlen1[MAXVEX+1][MAXVEX+1];//每条路的长度
	int verNum;//图中结点数
	int edgeNum;//边数
}MGraph;
//
/////////图中边上节点的结构体类型//////////////////
//typedef struct EdgeNode
//{
//	int adjvex;     // 存储该顶点对应的下标，the location of the vertex which was pointed by edge
//	int  info;    //可以用来存储该节点的值，和上面那行有点混淆
//	struct EdgeNode * next;  //和此节点相连的下一个节点
//	struct EdgeNode * prev;  //此节点所在链表的头节点
//}EdgeNode;
//
/////////图中顶点节点的结构体类型//////////////////
//typedef struct VertexNode
//{
//	// 统计每个顶点的入度
//	int in;
//	int data;
//	EdgeNode * firstedge;
//}VertexNode, AdjList[MAXVEX];
//
//////////图的邻接链表结构体类型///////////////////
//typedef struct LGraph
//{
//	int numNodes;//图中节点数
//	int numEdges;//边数
//	AdjList adjList;//定义一个AdjList类型的数组，每个数组元素都是一个链表，数组元素的个数为MAXVEX
//}LGraph, *LGraphAdjListLink; // 定义邻接表的指针
//
////////队列的结构体类型//////////////////////////
///**定义用到的数据结构队列
//使用的是循环队列 (判断队列满的方法为差一个位置)**/
//typedef struct Queue
//{
//	int data[MAXSIZE]; //用来存放被访问的结点
//	int front; //队头下标
//	int rear;  //队尾下标
//}Queue;

//////////车辆结构体类型//////////////////////////
typedef struct Car
{
	//车辆变量设置//
	// int ID[MAXCROSS][MAXCROSS];//始发路口对应的车辆编号
	 int carid;  //车辆ID
	 int srcCross;//车辆的始发路口
	 int desCross;//车辆的目的路口
	 int maxspeed;//车辆的最高速度
	 int curspeed;//车辆当前速度
	 int plantime;//车辆的计划出发时间
	 int actualtime;//车辆的实际出发时间
	 int runtime;//车辆当前行驶时间
	 int curIDRoad;//车辆当前所在的道路编号
	 int curIDpath;//车辆当前所在车道编号
	 int status ;//当前车辆的状态
	 int dis; //小车当前所行驶的距离
	 int startflag;//车辆出发标志
	// int cartimeid[11][MAXCAR];//某个时刻出发的所有车辆的id
	 //int cartimenum[11];//某个时刻车辆的总数
}Car;


///////////Int型矩阵空间(二维数组)动态分配//////////////////////
//int **matrixINT(int row, int column)
//{
//	int **m;
//	int i = 0;
//	m = (int **)malloc(row*sizeof(int*));
//	if (m == NULL)
//	{
//		printf("矩阵分配动态内存空间失败");
//		return 0;
//	}
//	for (i = 0; i < row; i++)
//		m[i] = (int *)malloc(column*sizeof(int));
//	return m;
//}
#endif