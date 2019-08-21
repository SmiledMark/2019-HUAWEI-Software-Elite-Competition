#include <stdio.h>
#include <stdlib.h>
#include"struct.h"
int* searchPath(int *prev1, int src, int des);
int* Dijkstra(int n, int src, int c[MAXVEX + 1][MAXVEX + 1]);
MGraph* MgraphDij(MGraph* GDij);
void write(int carid, int cartime, int *lujing, FILE* fp4);
void maopaosortdown(int* a, int length, int* b);
void maopaosortup(int* a, int length, int* b);
int* Dijdis(int n, int src, int c[MAXCROSS + 1][MAXCROSS + 1]);
int **matrixINT(int row, int column);
void LuJing(Car* car, FILE *fp4)

{
	int carnum = numLine2;//numline2 is the total num of car 
	int* lujing1 = NULL;
	lujing1 = (int *)malloc((MAXCROSS + 1)*sizeof(int));
	int* prev2 = NULL;
	int j = 1;
	int carid, cartime;
	MGraph GDij;
	MGraph* GDij1 = MgraphDij(&GDij);
	//FILE *fp4=NULL;
	//fp4 = fopen(argv[4], "wb");
	if (fp4 == NULL)
	{
		printf("the file is not open!");
	}
	fprintf(fp4, "#(carId,StartTime,RoadId...)");
	fprintf(fp4, "\r");
	fputs("\n", fp4);//to huanhang

	////////////////将源点到终点的最短距离输出////////////////
	int distance[MAXCROSS + 1][MAXCROSS + 1];//任意两个节点之间的最短距离
	int* dijdis = NULL;
	dijdis = (int*)malloc((MAXCROSS + 1)*sizeof(int));
	for (int i = 1; i <= numLine3; i++)
	{
		dijdis = Dijdis(MAXCROSS, i, GDij1->roadlen1);
		for (int j = 1; j <= numLine3; j++)
		{
			distance[i][j] = dijdis[j];
		}
	}


	/////////////////给各个时刻的车辆赋予车辆编号//////////////
	//int cartimeid[11][MAXCAR / 5];//某个时刻出发的所有车辆的id
	//int cartimenum[11];//某个时刻车辆的总数，这里的数组大小11要根据实际有多少个时刻来定，由于是从1开始故要比实际的时刻数加1
	//for (int i = 1; i <= 10; i++)//注意上面的11一定要根据实际地图进行更改必须是时刻数加1
	//{
	//	cartimenum[i] = 0;
	//}
	//for (int i = 0; i < numLine2; i++)
	//{
	//	cartimeid[car[i].plantime][cartimenum[car[i].plantime]++] = i;
	//}
	////////输出某个计划出发时间的所有车辆ID////////
	//for (int num = 0; num < cartimenum[3]; num++)
	//{
	//	printf("%d\n", cartimeid[3][num]);
	//}


	/////////////////给各个速度的车辆赋予车辆编号////////////////
	int carspeedid[9][MAXCAR / 3];//记录已某个速度出发的车辆的ID号
	int carspeednum[9];//当前速度车辆的数量，其实训练赛地图车的速度只有1-8，设置数组大小为9即可
	for (int i = 1; i <= 8; i++)//注意上面的9必须根据实际地图来进行更改必须是速度数加1
	{
		carspeednum[i] = 0;
	}
	for (int i = 0; i < numLine2; i++)
	{
		carspeedid[car[i].maxspeed][carspeednum[car[i].maxspeed]++] = i;
	}
	//////////////////输出某个速度所有车辆的ID///////////////////////
	//for (int num = 0; num < carspeednum[6]; num++)
	//{
	//	printf("%d\n", carspeedid[6][num]);
	//}   

	//////////////根据各个速度对应车辆最短行驶距离进行升序排序////////////////
	/////////////////速度为8///////////////
	int* cardis8;//速度为8的车辆的最短行驶距离
	cardis8 = (int *)malloc(sizeof(int)*(carspeednum[8] + 1));
	int* index8;//速度为8的车辆排序后的下标也就是对应的车辆号
	index8 = (int*)malloc(sizeof(int)*(carspeednum[8] + 1));
	int* spd8crossnum = NULL;
	spd8crossnum = (int*)malloc(sizeof(int)*(numLine3 + 1));
	int** carcrossid8 = matrixINT(numLine3 + 1, MAXCAR / 100);//记录当前速度下某个路口的车辆ID
	//int carcrossid[65][MAXCAR / 6];//记录当前速度下某几个路口的车辆ID
	int** spd8crossid = matrixINT(numLine3/8+1, MAXCAR / 20);//当前速度竖着的8个路口为一组，对应的车辆ID
	int* spd8crosscnt = NULL;
	spd8crosscnt = (int*)malloc(sizeof(int)*(numLine3/3 + 1));
	for (int i = 0; i < carspeednum[8]; i++)
	{
		cardis8[i] = distance[car[carspeedid[8][i]].srcCross][car[carspeedid[8][i]].desCross];
		index8[i] = i;
	}
	maopaosortup(cardis8, carspeednum[8], index8);
	
	////////////将当前速度下各个路口车辆数初始化为0////////////////
	for (int i = 0; i < carspeednum[8]; i++)
	{
		spd8crossnum[car[carspeedid[8][index8[i]]].srcCross] = 0;//将当前速度下各个路口车辆数初始化为0
	}

	///////////将当前速度下一到八路口车辆数初始化为0////////////////
	for (int i = 0; i < 9; i++)
	{
		spd8crosscnt[i] = 0;//将当前速度下一到八路口车辆数初始化为0
	}


	///////////将当前速度下一到八路口对应车辆的ID设置为0/////////////
	for (int i = 0; i < numLine3/8+1; i++)
	{
		for (int j = 0; j < MAXCAR / 20; j++)
			spd8crossid[i][j] = 0;
	}

	///////////将当前速度下各个路口对应车辆的ID设置为0/////////////
	for (int i = 0; i <= numLine3; i++)
	{
		for (int j = 0; j < MAXCAR / 100; j++)
			carcrossid8[i][j] = 0;
	}


	////////////将当前速度下各个路口车辆的ID赋给carcrossid////////////
	for (int i = 0; i < carspeednum[8]; i++)//将当前速度下各个路口车辆的ID赋给carcrossid
	{
		carcrossid8[car[carspeedid[8][index8[i]]].srcCross][spd8crossnum[car[carspeedid[8][index8[i]]].srcCross]++] = i;
		
		/////////将25-32路口设成一路口，也就是最中间那些路口/////////
		if (car[carspeedid[8][index8[i]]].srcCross == 25 || car[carspeedid[8][index8[i]]].srcCross == 26
			|| car[carspeedid[8][index8[i]]].srcCross == 27 || car[carspeedid[8][index8[i]]].srcCross == 28
			|| car[carspeedid[8][index8[i]]].srcCross == 29 || car[carspeedid[8][index8[i]]].srcCross == 30
			|| car[carspeedid[8][index8[i]]].srcCross == 31 || car[carspeedid[8][index8[i]]].srcCross == 32)
		{
			spd8crossid[1][spd8crosscnt[1]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////将1-8路口设成二路口，也就是最左边那些路口/////////
		if (car[carspeedid[8][index8[i]]].srcCross == 1 || car[carspeedid[8][index8[i]]].srcCross == 2
			|| car[carspeedid[8][index8[i]]].srcCross == 3 || car[carspeedid[8][index8[i]]].srcCross == 4
			|| car[carspeedid[8][index8[i]]].srcCross == 5 || car[carspeedid[8][index8[i]]].srcCross == 6
			|| car[carspeedid[8][index8[i]]].srcCross == 7 || car[carspeedid[8][index8[i]]].srcCross == 8)
		{
			spd8crossid[2][spd8crosscnt[2]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////将57-64路口设成三路口，也就是最右边那些路口/////////
		if (car[carspeedid[8][index8[i]]].srcCross == 57 || car[carspeedid[8][index8[i]]].srcCross == 58
			|| car[carspeedid[8][index8[i]]].srcCross == 59 || car[carspeedid[8][index8[i]]].srcCross == 60
			|| car[carspeedid[8][index8[i]]].srcCross == 61 || car[carspeedid[8][index8[i]]].srcCross == 62
			|| car[carspeedid[8][index8[i]]].srcCross == 63 || car[carspeedid[8][index8[i]]].srcCross == 64)
		{
			spd8crossid[3][spd8crosscnt[3]++] = i;//记录当前速度下一路口的车辆ID
		}
		//////////////////////将33-40路口设成四路口////////////////////
		if (car[carspeedid[8][index8[i]]].srcCross == 33 || car[carspeedid[8][index8[i]]].srcCross == 34
			|| car[carspeedid[8][index8[i]]].srcCross == 35 || car[carspeedid[8][index8[i]]].srcCross == 36
			|| car[carspeedid[8][index8[i]]].srcCross == 37 || car[carspeedid[8][index8[i]]].srcCross == 38
			|| car[carspeedid[8][index8[i]]].srcCross == 39 || car[carspeedid[8][index8[i]]].srcCross == 40)
		{
			spd8crossid[4][spd8crosscnt[4]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将9-16路口设成五路口//////////////////////
		if (car[carspeedid[8][index8[i]]].srcCross == 9 || car[carspeedid[8][index8[i]]].srcCross == 10
			|| car[carspeedid[8][index8[i]]].srcCross == 11 || car[carspeedid[8][index8[i]]].srcCross == 12
			|| car[carspeedid[8][index8[i]]].srcCross == 13 || car[carspeedid[8][index8[i]]].srcCross == 14
			|| car[carspeedid[8][index8[i]]].srcCross == 15 || car[carspeedid[8][index8[i]]].srcCross == 16)
		{
			spd8crossid[5][spd8crosscnt[5]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将49-56路口设成六路口//////////////////////
		if (car[carspeedid[8][index8[i]]].srcCross == 49 || car[carspeedid[8][index8[i]]].srcCross == 50
			|| car[carspeedid[8][index8[i]]].srcCross == 51 || car[carspeedid[8][index8[i]]].srcCross == 52
			|| car[carspeedid[8][index8[i]]].srcCross == 53 || car[carspeedid[8][index8[i]]].srcCross == 54
			|| car[carspeedid[8][index8[i]]].srcCross == 55 || car[carspeedid[8][index8[i]]].srcCross == 56)
		{
			spd8crossid[6][spd8crosscnt[6]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将17-24路口设成七路口//////////////////////
		if (car[carspeedid[8][index8[i]]].srcCross == 17 || car[carspeedid[8][index8[i]]].srcCross == 18
			|| car[carspeedid[8][index8[i]]].srcCross == 19 || car[carspeedid[8][index8[i]]].srcCross == 20
			|| car[carspeedid[8][index8[i]]].srcCross == 21 || car[carspeedid[8][index8[i]]].srcCross == 22
			|| car[carspeedid[8][index8[i]]].srcCross == 23 || car[carspeedid[8][index8[i]]].srcCross == 24)
		{
			spd8crossid[7][spd8crosscnt[7]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将41-48路口设成八路口//////////////////////
		if (car[carspeedid[8][index8[i]]].srcCross == 41 || car[carspeedid[8][index8[i]]].srcCross == 42
			|| car[carspeedid[8][index8[i]]].srcCross == 43 || car[carspeedid[8][index8[i]]].srcCross == 44
			|| car[carspeedid[8][index8[i]]].srcCross == 45 || car[carspeedid[8][index8[i]]].srcCross == 46
			|| car[carspeedid[8][index8[i]]].srcCross == 47 || car[carspeedid[8][index8[i]]].srcCross == 48)
		{
			spd8crossid[8][spd8crosscnt[8]++] = i;//记录当前速度下一路口的车辆ID
		}

	}

	/////////////////速度为6///////////////////
	int* cardis6;//速度为6的车辆的最短行驶距离
	cardis6 = (int *)malloc(sizeof(int)*(carspeednum[6] + 1));
	int* index6;//速度为6的车辆排序后的下标也就是对应的车辆号
	index6 = (int*)malloc(sizeof(int)*(carspeednum[6] + 1));
	int* spd6crossnum = NULL;
	spd6crossnum = (int*)malloc(sizeof(int)*(numLine3 + 1));
	int** carcrossid6 = matrixINT(numLine3 + 1, MAXCAR / 100);//记录当前速度下某个路口的车辆ID
	int** spd6crossid = matrixINT(numLine3 / 8 + 1, MAXCAR / 20);//当前速度竖着的8个路口为一组，对应的车辆ID
	int* spd6crosscnt = NULL;
	spd6crosscnt = (int*)malloc(sizeof(int)*(numLine3 / 3 + 1));
	for (int i = 0; i < carspeednum[6]; i++)
	{
		cardis6[i] = distance[car[carspeedid[6][i]].srcCross][car[carspeedid[6][i]].desCross];
		index6[i] = i;
	}
	maopaosortup(cardis6, carspeednum[6], index6);

	////////////将当前速度下各个路口车辆数初始化为0////////////////
	for (int i = 0; i < carspeednum[6]; i++)
	{
		spd6crossnum[car[carspeedid[6][index6[i]]].srcCross] = 0;//将当前速度下各个路口车辆数初始化为0
	}

	///////////将当前速度下一到八路口车辆数初始化为0////////////////
	for (int i = 0; i < 9; i++)
	{
		spd6crosscnt[i] = 0;//将当前速度下一到八路口车辆数初始化为0
	}

	///////////将当前速度下一到八路口对应车辆的ID设置为0/////////////
	for (int i = 0; i < numLine3 / 8 + 1; i++)
	{
		for (int j = 0; j < MAXCAR / 20; j++)
			spd6crossid[i][j] = 0;
	}

	///////////将当前速度下各个路口对应车辆的ID设置为0/////////////
	for (int i = 0; i <= numLine3; i++)
	{
		for (int j = 0; j < MAXCAR / 100; j++)
			carcrossid6[i][j] = 0;
	}
	////////////将当前速度下各个路口车辆的ID赋给carcrossid////////////
	for (int i = 0; i < carspeednum[6]; i++)//将当前速度下各个路口车辆的ID赋给carcrossid
	{
		carcrossid6[car[carspeedid[6][index6[i]]].srcCross][spd6crossnum[car[carspeedid[6][index6[i]]].srcCross]++] = i;

		/////////将25-32路口设成一路口，也就是最中间那些路口/////////
		if (car[carspeedid[6][index6[i]]].srcCross == 25 || car[carspeedid[6][index6[i]]].srcCross == 26
			|| car[carspeedid[6][index6[i]]].srcCross == 27 || car[carspeedid[6][index6[i]]].srcCross == 28
			|| car[carspeedid[6][index6[i]]].srcCross == 29 || car[carspeedid[6][index6[i]]].srcCross == 30
			|| car[carspeedid[6][index6[i]]].srcCross == 31 || car[carspeedid[6][index6[i]]].srcCross == 32)
		{
			spd6crossid[1][spd6crosscnt[1]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////将1-8路口设成二路口，也就是最左边那些路口/////////
		if (car[carspeedid[6][index6[i]]].srcCross == 1 || car[carspeedid[6][index6[i]]].srcCross == 2
			|| car[carspeedid[6][index6[i]]].srcCross == 3 || car[carspeedid[6][index6[i]]].srcCross == 4
			|| car[carspeedid[6][index6[i]]].srcCross == 5 || car[carspeedid[6][index6[i]]].srcCross == 6
			|| car[carspeedid[6][index6[i]]].srcCross == 7 || car[carspeedid[6][index6[i]]].srcCross == 8)
		{
			spd6crossid[2][spd6crosscnt[2]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////将57-64路口设成三路口，也就是最右边那些路口/////////
		if (car[carspeedid[6][index6[i]]].srcCross == 57 || car[carspeedid[6][index6[i]]].srcCross == 58
			|| car[carspeedid[6][index6[i]]].srcCross == 59 || car[carspeedid[6][index6[i]]].srcCross == 60
			|| car[carspeedid[6][index6[i]]].srcCross == 61 || car[carspeedid[6][index6[i]]].srcCross == 62
			|| car[carspeedid[6][index6[i]]].srcCross == 63 || car[carspeedid[6][index6[i]]].srcCross == 64)
		{
			spd6crossid[3][spd6crosscnt[3]++] = i;//记录当前速度下一路口的车辆ID
		}
		//////////////////////将33-40路口设成四路口////////////////////
		if (car[carspeedid[6][index6[i]]].srcCross == 33 || car[carspeedid[6][index6[i]]].srcCross == 34
			|| car[carspeedid[6][index6[i]]].srcCross == 35 || car[carspeedid[6][index6[i]]].srcCross == 36
			|| car[carspeedid[6][index6[i]]].srcCross == 37 || car[carspeedid[6][index6[i]]].srcCross == 38
			|| car[carspeedid[6][index6[i]]].srcCross == 39 || car[carspeedid[6][index6[i]]].srcCross == 40)
		{
			spd6crossid[4][spd6crosscnt[4]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将9-16路口设成五路口//////////////////////
		if (car[carspeedid[6][index6[i]]].srcCross == 9 || car[carspeedid[6][index6[i]]].srcCross == 10
			|| car[carspeedid[6][index6[i]]].srcCross == 11 || car[carspeedid[6][index6[i]]].srcCross == 12
			|| car[carspeedid[6][index6[i]]].srcCross == 13 || car[carspeedid[6][index6[i]]].srcCross == 14
			|| car[carspeedid[6][index6[i]]].srcCross == 15 || car[carspeedid[6][index6[i]]].srcCross == 16)
		{
			spd6crossid[5][spd6crosscnt[5]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将49-56路口设成六路口//////////////////////
		if (car[carspeedid[6][index6[i]]].srcCross == 49 || car[carspeedid[6][index6[i]]].srcCross == 50
			|| car[carspeedid[6][index6[i]]].srcCross == 51 || car[carspeedid[6][index6[i]]].srcCross == 52
			|| car[carspeedid[6][index6[i]]].srcCross == 53 || car[carspeedid[6][index6[i]]].srcCross == 54
			|| car[carspeedid[6][index6[i]]].srcCross == 55 || car[carspeedid[6][index6[i]]].srcCross == 56)
		{
			spd6crossid[6][spd6crosscnt[6]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将17-24路口设成七路口//////////////////////
		if (car[carspeedid[6][index6[i]]].srcCross == 17 || car[carspeedid[6][index6[i]]].srcCross == 18
			|| car[carspeedid[6][index6[i]]].srcCross == 19 || car[carspeedid[6][index6[i]]].srcCross == 20
			|| car[carspeedid[6][index6[i]]].srcCross == 21 || car[carspeedid[6][index6[i]]].srcCross == 22
			|| car[carspeedid[6][index6[i]]].srcCross == 23 || car[carspeedid[6][index6[i]]].srcCross == 24)
		{
			spd6crossid[7][spd6crosscnt[7]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将41-48路口设成八路口//////////////////////
		if (car[carspeedid[6][index6[i]]].srcCross == 41 || car[carspeedid[6][index6[i]]].srcCross == 42
			|| car[carspeedid[6][index6[i]]].srcCross == 43 || car[carspeedid[6][index6[i]]].srcCross == 44
			|| car[carspeedid[6][index6[i]]].srcCross == 45 || car[carspeedid[6][index6[i]]].srcCross == 46
			|| car[carspeedid[6][index6[i]]].srcCross == 47 || car[carspeedid[6][index6[i]]].srcCross == 48)
		{
			spd6crossid[8][spd6crosscnt[8]++] = i;//记录当前速度下一路口的车辆ID
		}

	}

	/////////////////速度为4///////////////////
	int* cardis4;//速度为4的车辆的最短行驶距离
	cardis4 = (int *)malloc(sizeof(int)*(carspeednum[4] + 1));
	int* index4;//速度为4的车辆排序后的下标也就是对应的车辆号
	index4 = (int*)malloc(sizeof(int)*(carspeednum[4] + 1));
	int* spd4crossnum = NULL;
	spd4crossnum = (int*)malloc(sizeof(int)*(numLine3 + 1));
	int** carcrossid4 = matrixINT(numLine3 + 1, MAXCAR / 100);//记录当前速度下某个路口的车辆ID
	int** spd4crossid = matrixINT(numLine3 / 8 + 1, MAXCAR / 20);//当前速度竖着的8个路口为一组，对应的车辆ID
	int* spd4crosscnt = NULL;
	spd4crosscnt = (int*)malloc(sizeof(int)*(numLine3 / 3 + 1));

	for (int i = 0; i < carspeednum[4]; i++)
	{
		cardis4[i] = distance[car[carspeedid[4][i]].srcCross][car[carspeedid[4][i]].desCross];
		index4[i] = i;
	}
	maopaosortup(cardis4, carspeednum[4], index4);

	////////////将当前速度下各个路口车辆数初始化为0////////////////
	for (int i = 0; i < carspeednum[4]; i++)
	{
		spd4crossnum[car[carspeedid[4][index4[i]]].srcCross] = 0;//将当前速度下各个路口车辆数初始化为0
	}

	///////////将当前速度下一到八路口车辆数初始化为0////////////////
	for (int i = 0; i < 9; i++)
	{
		spd4crosscnt[i] = 0;//将当前速度下一到八路口车辆数初始化为0
	}

	///////////将当前速度下一到八路口对应车辆的ID设置为0/////////////
	for (int i = 0; i < numLine3 / 8 + 1; i++)
	{
		for (int j = 0; j < MAXCAR / 20; j++)
			spd4crossid[i][j] = 0;
	}

	///////////将当前速度下各个路口对应车辆的ID设置为0/////////////
	for (int i = 0; i <= numLine3; i++)
	{
		for (int j = 0; j < MAXCAR / 100; j++)
			carcrossid4[i][j] = 0;
	}
	////////////将当前速度下各个路口车辆的ID赋给carcrossid////////////
	for (int i = 0; i < carspeednum[4]; i++)//将当前速度下各个路口车辆的ID赋给carcrossid
	{
		carcrossid4[car[carspeedid[4][index4[i]]].srcCross][spd4crossnum[car[carspeedid[4][index4[i]]].srcCross]++] = i;

		/////////将25-32路口设成一路口，也就是最中间那些路口/////////
		if (car[carspeedid[4][index4[i]]].srcCross == 25 || car[carspeedid[4][index4[i]]].srcCross == 26
			|| car[carspeedid[4][index4[i]]].srcCross == 27 || car[carspeedid[4][index4[i]]].srcCross == 28
			|| car[carspeedid[4][index4[i]]].srcCross == 29 || car[carspeedid[4][index4[i]]].srcCross == 30
			|| car[carspeedid[4][index4[i]]].srcCross == 31 || car[carspeedid[4][index4[i]]].srcCross == 32)
		{
			spd4crossid[1][spd4crosscnt[1]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////将1-8路口设成二路口，也就是最左边那些路口/////////
		if (car[carspeedid[4][index4[i]]].srcCross == 1 || car[carspeedid[4][index4[i]]].srcCross == 2
			|| car[carspeedid[4][index4[i]]].srcCross == 3 || car[carspeedid[4][index4[i]]].srcCross == 4
			|| car[carspeedid[4][index4[i]]].srcCross == 5 || car[carspeedid[4][index4[i]]].srcCross == 6
			|| car[carspeedid[4][index4[i]]].srcCross == 7 || car[carspeedid[4][index4[i]]].srcCross == 8)
		{
			spd4crossid[2][spd4crosscnt[2]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////将57-64路口设成三路口，也就是最右边那些路口/////////
		if (car[carspeedid[4][index4[i]]].srcCross == 57 || car[carspeedid[4][index4[i]]].srcCross == 58
			|| car[carspeedid[4][index4[i]]].srcCross == 59 || car[carspeedid[4][index4[i]]].srcCross == 60
			|| car[carspeedid[4][index4[i]]].srcCross == 61 || car[carspeedid[4][index4[i]]].srcCross == 62
			|| car[carspeedid[4][index4[i]]].srcCross == 63 || car[carspeedid[4][index4[i]]].srcCross == 64)
		{
			spd4crossid[3][spd4crosscnt[3]++] = i;//记录当前速度下一路口的车辆ID
		}
		//////////////////////将33-40路口设成四路口////////////////////
		if (car[carspeedid[4][index4[i]]].srcCross == 33 || car[carspeedid[4][index4[i]]].srcCross == 34
			|| car[carspeedid[4][index4[i]]].srcCross == 35 || car[carspeedid[4][index4[i]]].srcCross == 36
			|| car[carspeedid[4][index4[i]]].srcCross == 37 || car[carspeedid[4][index4[i]]].srcCross == 38
			|| car[carspeedid[4][index4[i]]].srcCross == 39 || car[carspeedid[4][index4[i]]].srcCross == 40)
		{
			spd4crossid[4][spd4crosscnt[4]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将9-16路口设成五路口//////////////////////
		if (car[carspeedid[4][index4[i]]].srcCross == 9 || car[carspeedid[4][index4[i]]].srcCross == 10
			|| car[carspeedid[4][index4[i]]].srcCross == 11 || car[carspeedid[4][index4[i]]].srcCross == 12
			|| car[carspeedid[4][index4[i]]].srcCross == 13 || car[carspeedid[4][index4[i]]].srcCross == 14
			|| car[carspeedid[4][index4[i]]].srcCross == 15 || car[carspeedid[4][index4[i]]].srcCross == 16)
		{
			spd4crossid[5][spd4crosscnt[5]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将49-56路口设成六路口//////////////////////
		if (car[carspeedid[4][index4[i]]].srcCross == 49 || car[carspeedid[4][index4[i]]].srcCross == 50
			|| car[carspeedid[4][index4[i]]].srcCross == 51 || car[carspeedid[4][index4[i]]].srcCross == 52
			|| car[carspeedid[4][index4[i]]].srcCross == 53 || car[carspeedid[4][index4[i]]].srcCross == 54
			|| car[carspeedid[4][index4[i]]].srcCross == 55 || car[carspeedid[4][index4[i]]].srcCross == 56)
		{
			spd4crossid[6][spd4crosscnt[6]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将17-24路口设成七路口//////////////////////
		if (car[carspeedid[4][index4[i]]].srcCross == 17 || car[carspeedid[4][index4[i]]].srcCross == 18
			|| car[carspeedid[4][index4[i]]].srcCross == 19 || car[carspeedid[4][index4[i]]].srcCross == 20
			|| car[carspeedid[4][index4[i]]].srcCross == 21 || car[carspeedid[4][index4[i]]].srcCross == 22
			|| car[carspeedid[4][index4[i]]].srcCross == 23 || car[carspeedid[4][index4[i]]].srcCross == 24)
		{
			spd4crossid[7][spd4crosscnt[7]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将41-48路口设成八路口//////////////////////
		if (car[carspeedid[4][index4[i]]].srcCross == 41 || car[carspeedid[4][index4[i]]].srcCross == 42
			|| car[carspeedid[4][index4[i]]].srcCross == 43 || car[carspeedid[4][index4[i]]].srcCross == 44
			|| car[carspeedid[4][index4[i]]].srcCross == 45 || car[carspeedid[4][index4[i]]].srcCross == 46
			|| car[carspeedid[4][index4[i]]].srcCross == 47 || car[carspeedid[4][index4[i]]].srcCross == 48)
		{
			spd4crossid[8][spd4crosscnt[8]++] = i;//记录当前速度下一路口的车辆ID
		}

	}

////////////////////////////////速度为2//////////////////////////////////////////////////////////////////////
	int* cardis2;//速度为2的车辆的最短行驶距离
	cardis2 = (int *)malloc(sizeof(int)*(carspeednum[2] + 1));
	int* index2;//速度为2的车辆排序后的下标也就是对应的车辆号
	index2 = (int*)malloc(sizeof(int)*(carspeednum[2] + 1));
	int* spd2crossnum = NULL;
	spd2crossnum = (int*)malloc(sizeof(int)*(numLine3 + 1));
	int** carcrossid2 = matrixINT(numLine3 + 1, MAXCAR / 100);//记录当前速度下某个路口的车辆ID
	int** spd2crossid = matrixINT(numLine3 / 8 + 1, MAXCAR / 20);//当前速度竖着的8个路口为一组，对应的车辆ID
	int* spd2crosscnt = NULL;
	spd2crosscnt = (int*)malloc(sizeof(int)*(numLine3 / 3 + 1));

	for (int i = 0; i < carspeednum[2]; i++)
	{
		cardis2[i] = distance[car[carspeedid[2][i]].srcCross][car[carspeedid[2][i]].desCross];
		index2[i] = i;
	}
	maopaosortup(cardis2, carspeednum[2], index2);

	////////////将当前速度下各个路口车辆数初始化为0////////////////
	for (int i = 0; i < carspeednum[2]; i++)
	{
		spd2crossnum[car[carspeedid[2][index2[i]]].srcCross] = 0;//将当前速度下各个路口车辆数初始化为0
	}

	///////////将当前速度下一到八路口车辆数初始化为0////////////////
	for (int i = 0; i < 9; i++)
	{
		spd2crosscnt[i] = 0;//将当前速度下一到八路口车辆数初始化为0
	}

	///////////将当前速度下一到八路口对应车辆的ID设置为0/////////////
	for (int i = 0; i < numLine3 / 8 + 1; i++)
	{
		for (int j = 0; j < MAXCAR / 20; j++)
			spd2crossid[i][j] = 0;
	}


	///////////将当前速度下各个路口对应车辆的ID设置为0/////////////
	for (int i = 0; i <= numLine3; i++)
	{
		for (int j = 0; j < MAXCAR / 100; j++)
			carcrossid2[i][j] = 0;
	}
	////////////将当前速度下各个路口车辆的ID赋给carcrossid////////////
	for (int i = 0; i < carspeednum[2]; i++)//将当前速度下各个路口车辆的ID赋给carcrossid
	{
		carcrossid2[car[carspeedid[2][index2[i]]].srcCross][spd2crossnum[car[carspeedid[2][index2[i]]].srcCross]++] = i;

		/////////将25-32路口设成一路口，也就是最中间那些路口/////////
		if (car[carspeedid[2][index2[i]]].srcCross == 25 || car[carspeedid[2][index2[i]]].srcCross == 26
			|| car[carspeedid[2][index2[i]]].srcCross == 27 || car[carspeedid[2][index2[i]]].srcCross == 28
			|| car[carspeedid[2][index2[i]]].srcCross == 29 || car[carspeedid[2][index2[i]]].srcCross == 30
			|| car[carspeedid[2][index2[i]]].srcCross == 31 || car[carspeedid[2][index2[i]]].srcCross == 32)
		{
			spd2crossid[1][spd2crosscnt[1]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////将1-8路口设成二路口，也就是最左边那些路口/////////
		if (car[carspeedid[2][index2[i]]].srcCross == 1 || car[carspeedid[2][index2[i]]].srcCross == 2
			|| car[carspeedid[2][index2[i]]].srcCross == 3 || car[carspeedid[2][index2[i]]].srcCross == 4
			|| car[carspeedid[2][index2[i]]].srcCross == 5 || car[carspeedid[2][index2[i]]].srcCross == 6
			|| car[carspeedid[2][index2[i]]].srcCross == 7 || car[carspeedid[2][index2[i]]].srcCross == 8)
		{
			spd2crossid[2][spd2crosscnt[2]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////将57-64路口设成三路口，也就是最右边那些路口/////////
		if (car[carspeedid[2][index2[i]]].srcCross == 57 || car[carspeedid[2][index2[i]]].srcCross == 58
			|| car[carspeedid[2][index2[i]]].srcCross == 59 || car[carspeedid[2][index2[i]]].srcCross == 60
			|| car[carspeedid[2][index2[i]]].srcCross == 61 || car[carspeedid[2][index2[i]]].srcCross == 62
			|| car[carspeedid[2][index2[i]]].srcCross == 63 || car[carspeedid[2][index2[i]]].srcCross == 64)
		{
			spd2crossid[3][spd2crosscnt[3]++] = i;//记录当前速度下一路口的车辆ID
		}
		//////////////////////将33-40路口设成四路口////////////////////
		if (car[carspeedid[2][index2[i]]].srcCross == 33 || car[carspeedid[2][index2[i]]].srcCross == 34
			|| car[carspeedid[2][index2[i]]].srcCross == 35 || car[carspeedid[2][index2[i]]].srcCross == 36
			|| car[carspeedid[2][index2[i]]].srcCross == 37 || car[carspeedid[2][index2[i]]].srcCross == 38
			|| car[carspeedid[2][index2[i]]].srcCross == 39 || car[carspeedid[2][index2[i]]].srcCross == 40)
		{
			spd2crossid[4][spd2crosscnt[4]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将9-16路口设成五路口//////////////////////
		if (car[carspeedid[2][index2[i]]].srcCross == 9 || car[carspeedid[2][index2[i]]].srcCross == 10
			|| car[carspeedid[2][index2[i]]].srcCross == 11 || car[carspeedid[2][index2[i]]].srcCross == 12
			|| car[carspeedid[2][index2[i]]].srcCross == 13 || car[carspeedid[2][index2[i]]].srcCross == 14
			|| car[carspeedid[2][index2[i]]].srcCross == 15 || car[carspeedid[2][index2[i]]].srcCross == 16)
		{
			spd2crossid[5][spd2crosscnt[5]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将49-56路口设成六路口//////////////////////
		if (car[carspeedid[2][index2[i]]].srcCross == 49 || car[carspeedid[2][index2[i]]].srcCross == 50
			|| car[carspeedid[2][index2[i]]].srcCross == 51 || car[carspeedid[2][index2[i]]].srcCross == 52
			|| car[carspeedid[2][index2[i]]].srcCross == 53 || car[carspeedid[2][index2[i]]].srcCross == 54
			|| car[carspeedid[2][index2[i]]].srcCross == 55 || car[carspeedid[2][index2[i]]].srcCross == 56)
		{
			spd2crossid[6][spd2crosscnt[6]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将17-24路口设成七路口//////////////////////
		if (car[carspeedid[2][index2[i]]].srcCross == 17 || car[carspeedid[2][index2[i]]].srcCross == 18
			|| car[carspeedid[2][index2[i]]].srcCross == 19 || car[carspeedid[2][index2[i]]].srcCross == 20
			|| car[carspeedid[2][index2[i]]].srcCross == 21 || car[carspeedid[2][index2[i]]].srcCross == 22
			|| car[carspeedid[2][index2[i]]].srcCross == 23 || car[carspeedid[2][index2[i]]].srcCross == 24)
		{
			spd2crossid[7][spd2crosscnt[7]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////////////////将41-48路口设成八路口//////////////////////
		if (car[carspeedid[2][index2[i]]].srcCross == 41 || car[carspeedid[2][index2[i]]].srcCross == 42
			|| car[carspeedid[2][index2[i]]].srcCross == 43 || car[carspeedid[2][index2[i]]].srcCross == 44
			|| car[carspeedid[2][index2[i]]].srcCross == 45 || car[carspeedid[2][index2[i]]].srcCross == 46
			|| car[carspeedid[2][index2[i]]].srcCross == 47 || car[carspeedid[2][index2[i]]].srcCross == 48)
		{
			spd2crossid[8][spd2crosscnt[8]++] = i;//记录当前速度下一路口的车辆ID
		}
	}

	////////////////最原始一辆一辆的发车/////////////////////
	//for (int i = 0; i < carnum; i++)
	//{
	//	prev2 = Dijkstra(MAXCROSS, car[i].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
	//	lujing1 = searchPath(prev2, car[i].srcCross, car[i].desCross);
	//	carid = i + tempcar;
	//	cartime = car[i].plantime + i;
	//       j=j+3;
	//	write(carid,cartime,lujing1,fp4);
	//       }



	///////////对所有的速度进行排序/////////////////////////
	//int* xiabiao = NULL;
	//xiabiao = (int*)malloc(MAXCAR*sizeof(int));
	//int* carspeed = NULL;
	//carspeed = (int*)malloc(MAXCAR*sizeof(int));
	//if (carspeed == NULL || xiabiao == NULL)
	//{
	//	printf("carspeed is NULL");
	//}
	//for (int i = 0; i < numLine2; i++)
	//{
	//	carspeed[i] = car[i].maxspeed;
	//	xiabiao[i] = i;
	//}
	//maopaosortdown(carspeed, numLine2, xiabiao);

	/////////////每次发多少辆车（不事先对速度进行排序）///////////////
	//int k = 0, m= 0,temptime=0;
	//for (int time = 1; time <= 10; time++)
	//{
	//	for (int i = 0; i < cartimenum[time]; i++)
	//	{
	//		if (i >=m && i < m + 5)
	//		{
	//			cartime = temptime + car[cartimeid[time][i]].plantime + k;
	//			prev2 = Dijkstra(MAXCROSS, car[cartimeid[time][i]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
	//			lujing1 = searchPath(prev2, car[cartimeid[time][i]].srcCross, car[cartimeid[time][i]].desCross);
	//			carid = cartimeid[time][i] + tempcar;
	//			write(carid, cartime, lujing1, fp4);
	//		}else
	//		{
	//			cartime =temptime + car[cartimeid[time][i]].plantime + k;
	//			prev2 = Dijkstra(MAXCROSS, car[cartimeid[time][i]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
	//			lujing1 = searchPath(prev2, car[cartimeid[time][i]].srcCross, car[cartimeid[time][i]].desCross);
	//			carid = cartimeid[time][i] + tempcar;
	//			write(carid, cartime, lujing1, fp4);
	//			m = m + 5;
	//			k=k+1;
	//		}
	//	}
	//	temptime = cartime;
	//	m = 0;
	//	k = 0;
	//}


	////////////////每次发多少辆车（事先对速度进行排序）//////////////////////////
	//int k1 = 0;
	//int m1 = 0;
	//int temptime1 = 10;//车辆第一次的发车时间，注意这个处理中用不到文件中给出的计划出发时间了
	//int startcarnum1=15;
	//for (int i = 0; i < numLine2; i++)
	//{
	//	if (i >= m1 && i < m1 + startcarnum1)
	//	{
	//		cartime = temptime1 + k1;
	//		prev2 = Dijkstra(MAXCROSS, car[xiabiao[i]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
	//		lujing1 = searchPath(prev2, car[xiabiao[i]].srcCross, car[xiabiao[i]].desCross);
	//		carid = xiabiao[i] + tempcar;
	//		write(carid, cartime, lujing1, fp4);
	//	}
	//	else
	//	{
	//		cartime = temptime1 + k1;
	//		prev2 = Dijkstra(MAXCROSS, car[xiabiao[i]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
	//		lujing1 = searchPath(prev2, car[xiabiao[i]].srcCross, car[xiabiao[i]].desCross);
	//		carid = xiabiao[i] + tempcar;
	//		write(carid, cartime, lujing1, fp4);
	//		m1 = m1 + startcarnum1;
	//		k1++;
	//	}
	//}


	/////////////////每次发车数不定(按速度从大往小发)/////////////////////
	int startnum[9];//各个速度每次的发车数量
	int i;
	int m2 = 0;
	int temptime2 = 10;
	int k2 = 0;
	int timeadd2 = 1;//每次发车的时间间隔

	///////////////speed=8发车数量设置////////////////////
	int a1, a2, a3, a4, a5, a6, a7, spd8;
	spd8 = 8;//速度设置，这里的最后一个printf有用到
	a1 = 50;//第一次发车数，发1次
	a2 = 70;//第二次发车数，发2次
	a3 = 50;//第三次发车数，发2次
	a4 = 40;//第四次发车数，发2次
	a5 = 40;//第五次发车数，发2次
	a6 = 30;//第六次发车数，发2次
	a7 = 25;//第七次发车数
	printf("/////////////////////////////////////////////\n");
	printf("speed=%d\n", spd8);
	printf("first car num: %d\n", a1);
	printf("first car scope: 0--%d\n", a1);
	printf("second car num: %d\n", a2);
	printf("second car scope: %d--%d\n", a1, a1 + 2 * a2);
	printf("third car num: %d\n", a3);
	printf("third car scope:%d--%d\n", a1 + 2 * a2, a1 + 2 * a2 + 2 * a3);
	printf("fourth car num: %d\n", a4);
	printf("fourth car scope: %d--%d\n", a1 + 2 * a2 + 2 * a3, a1 + 2 * a2 + 2 * a3 + 2 * a4);
	printf("fifth car num: %d\n", a5);
	printf("fifth car scope: %d--%d\n", a1 + 2 * a2 + 2 * a3 + 2 * a4, a1 + 2 * a2 + 2 * a3 + 2 * a4 + 2 * a5);
	printf("sixth car num: %d\n", a6);
	printf("sixth car scope: %d--%d\n", a1 + 2 * a2 + 2 * a3 + 2 * a4 + 2 * a5, a1 + 2 * a2 + 2 * a3 + 2 * a4 + 2 * a5 + 2 * a6);
	printf("seventh car num: %d\n", a7);
	printf("seventh car scope: %d--%d\n", a1 + 2 * a2 + 2 * a3 + 2 * a4 + 2 * a5 + 2 * a6, carspeednum[spd8]);

	///////////////////////speed=6发车数量设置////////////////////
	int b1, b2, b3, b4, b5, b6, b7, spd6;
	spd6 = 6;//速度设置，这里的最后一个printf有用到
	b1 = 65;//第一次发车数，发1次
	b2 = 55;//第二次发车数，发2次
	b3 = 45;//第三次发车数，发2次
	b4 = 40;//第四次发车数，发2次
	b5 = 35;//第五次发车数，发2次
	b6 = 30;//第六次发车数，发2次
	b7 = 18;//第七次发车数
	printf("/////////////////////////////////////////////\n");
	printf("speed=%d\n", spd6);
	printf("first car num: %d\n", b1);
	printf("first car scope: 0--%d\n", b1);
	printf("second car num: %d\n", b2);
	printf("second car scope: %d--%d\n", b1, b1 + 2 * b2);
	printf("third car num: %d\n", b3);
	printf("third car scope:%d--%d\n", b1 + 2 * b2, b1 + 2 * b2 + 2 * b3);
	printf("fourth car num: %d\n", b4);
	printf("fourth car scope: %d--%d\n", b1 + 2 * b2 + 2 * b3, b1 + 2 * b2 + 2 * b3 + 2 * b4);
	printf("fifth car num: %d\n", b5);
	printf("fifth car scope: %d--%d\n", b1 + 2 * b2 + 2 * b3 + 2 * b4, b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5);
	printf("sixth car num: %d\n", b6);
	printf("sixth car scope: %d--%d\n", b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5, b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5 + 2 * b6);
	printf("seventh car num: %d\n", b7);
	printf("seventh car scope: %d--%d\n", b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5 + 2 * b6, carspeednum[6]);

	///////////////speed=4发车数量设置////////////////////
	int c1, c2, c3, c4, c5, c6, c7, spd4;
	spd4 = 4;
	c1 = 55;//第一次发车数，发1次
	c2 = 50;//第二次发车数，发2次
	c3 = 45;//第三次发车数，发2次
	c4 = 40;//第四次发车数，发2次
	c5 = 35;//第五次发车数，发2次
	c6 = 30;//第六次发车数，发2次
	c7 = 25;//第七次发车数
	printf("/////////////////////////////////////////////\n");
	printf("speed=%d\n", spd4);
	printf("first car num: %d\n", c1);
	printf("first car scope: 0--%d\n", c1);
	printf("second car num: %d\n", c2);
	printf("second car scope: %d--%d\n", c1, c1 + 2 * c2);
	printf("third car num: %d\n", c3);
	printf("third car scope:%d--%d\n", c1 + 2 * c2, c1 + 2 * c2 + 2 * c3);
	printf("fourth car num: %d\n", c4);
	printf("fourth car scope: %d--%d\n", c1 + 2 * c2 + 2 * c3, c1 + 2 * c2 + 2 * c3 + 2 * c4);
	printf("fifth car num: %d\n", c5);
	printf("fifth car scope: %d--%d\n", c1 + 2 * c2 + 2 * c3 + 2 * c4, c1 + 2 * c2 + 2 * c3 + 2 * c4 + 2 * c5);
	printf("sixth car num: %d\n", c6);
	printf("sixth car scope: %d--%d\n", c1 + 2 * c2 + 2 * c3 + 2 * c4 + 2 * c5, c1 + 2 * c2 + 2 * c3 + 2 * c4 + 2 * c5 + 2 * c6);
	printf("seventh car num: %d\n", c7);
	printf("seventh car scope: %d--%d\n", c1 + 2 * c2 + 2 * c3 + 2 * c4 + 2 * c5 + 2 * c6, carspeednum[spd4]);


	///////////////speed=2发车数量设置////////////////////
	int d1, d2, d3, d4, d5, d6, d7, spd2;
	spd2 = 2;
	d1 = 45;//第一次发车数，发1次
	d2 = 40;//第二次发车数，发10次
	d3 = 35;//第三次发车数，发10次
	d4 = 30;//第四次发车数，发10次
	d5 = 30;//第五次发车数，发10次
	d6 = 25;//第六次发车数，发10次
	d7 = 15;//第七次发车数，发10次
	printf("/////////////////////////////////////////////\n");
	printf("speed=%d\n", spd2);
	printf("first car num: %d\n", d1);
	printf("first car scope: 0--%d\n", d1);
	printf("second car num: %d\n", d2);
	printf("second car scope: %d--%d\n", d1, d1 + 2 * d2);
	printf("third car num: %d\n", d3);
	printf("third car scope:%d--%d\n", d1 + 2 * d2, d1 + 2 * d2 + 2 * d3);
	printf("fourth car num: %d\n", d4);
	printf("fourth car scope: %d--%d\n", d1 + 2 * d2 + 2 * d3, d1 + 2 * d2 + 2 * d3 + 2 * d4);
	printf("fifth car num: %d\n", d5);
	printf("fifth car scope: %d--%d\n", d1 + 2 * d2 + 2 * d3 + 2 * d4, d1 + 2 * d2 + 2 * d3 + 2 * d4 + 2 * d5);
	printf("sixth car num: %d\n", d6);
	printf("sixth car scope: %d--%d\n", d1 + 2 * d2 + 2 * d3 + 2 * d4 + 2 * d5, d1 + 2 * d2 + 2 * d3 + 2 * d4 + 2 * d5 + 2 * d6);
	printf("seventh car num: %d\n", d7);
	printf("seventh car scope: %d--%d\n", d1 + 2 * d2 + 2 * d3 + 2 * d4 + 2 * d5 + 2 * d6, carspeednum[spd2]);


	for (int speed = 8; speed >= 1; speed--)
	{
		///////////////////////////////////////////////////////////////////////
		if (speed == 8)
		{
			for (int cross = 1; cross <= 8; cross++)
			{
				for (int i = 0; i < spd8crosscnt[cross]; i++)
				{
					if (i <= a1)
						startnum[speed] = a1;//当前速度第一次发车数
					else if (i > a1 && i <= a1 + 2 * a2)
						startnum[speed] = a2;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > a1 + 2 * a2 && i <= a1 + 2 * a2 + 2 * a3)
						startnum[speed] = a3;//当前速度车辆号为360-560的车一次发多少辆发10次
					else if (i > a1 + 2 * a2 + 10 * a3 && i <= a1 + 2 * a2 + 2 * a3 + 2 * a4)
						startnum[speed] = a4;//当前速度车辆号为560-960的车一次发多少辆发10次
					else if (i > a1 + 2 * a2 + 2 * a3 + 2 * a4 && i <= a1 + 2 * a2 + 2 * a3 + 2 * a4 + 2 * a5)
						startnum[speed] = a5;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > a1 + 2 * a2 + 2 * a3 + 2 * a4 + 2 * a5 && i <= a1 + 2 * a2 + 2 * a3 + 2 * a4 + 2 * a5 + 2 * a6)
						startnum[speed] = a6;//当前速度车辆号为1260-1510的车一次发多少辆发10次
					else if (i > a1 + 2 * a2 + 2 * a3 + 2 * a4 + 2 * a5 + 2 * a6 && i <= carspeednum[speed])
						startnum[speed] = a7;//当前速度剩余车辆的发车数

					if (i >= m2 && i < m2 + startnum[speed])
					{
					/*	if (i == a1 + 1
							|| i == a1 + 10 * a2 + 1
							|| i == a1 + 10 * a2 + 10 * a3 + 1
							|| i == a1 + 10 * a2 + 10 * a3 + 10 * a4 + 1
							|| i == a1 + 10 * a2 + 10 * a3 + 10 * a4 + 10 * a5 + 1
							|| i == a1 + 10 * a2 + 10 * a3 + 10 * a4 + 10 * a5 + 10 * a6 + 1
							)
						{
							temptime2 = temptime2 + 1;
						}*/
						cartime = temptime2 + k2;
						if (i < a1)
						{
							cartime = car[carspeedid[speed][index8[spd8crossid[cross][i]]]].plantime;//每个路口的前a1辆车以计划时间出发
						}

////////////////////////////////////个别路口按计划时间发车////////////////////////////////////////////
/////////////////////////////////////1路口按计划时间发车//////////////////////////////////////////////
//						for (int crossnum = 0; crossnum < spd8crossnum[1]; crossnum++)
//						{
//							if (carcrossid8[1][crossnum] == spd8crossid[cross][i])
//							{
//								cartime = car[carspeedid[speed][index8[spd8crossid[cross][i]]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
//							}
//						}
/////////////////////////////////////64路口按计划时间发车//////////////////////////////////////////////
//						for (int crossnum = 0; crossnum < spd8crossnum[64]; crossnum++)
//						{
//							if (carcrossid8[64][crossnum] == spd8crossid[cross][i])
//							{
//								cartime = car[carspeedid[speed][index8[spd8crossid[cross][i]]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
//							}
//						}
/////////////////////////////////////8路口按计划时间发车//////////////////////////////////////////////
//						for (int crossnum = 0; crossnum < spd8crossnum[8]; crossnum++)
//						{
//							if (carcrossid8[8][crossnum] == spd8crossid[cross][i])
//							{
//								cartime = car[carspeedid[speed][index8[spd8crossid[cross][i]]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
//							}
//						}
/////////////////////////////////////57路口按计划时间发车//////////////////////////////////////////////
//						for (int crossnum = 0; crossnum < spd8crossnum[57]; crossnum++)
//						{
//							if (carcrossid8[57][crossnum] == spd8crossid[cross][i])
//							{
//								cartime = car[carspeedid[speed][index8[spd8crossid[cross][i]]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
//							}
//						}
/////////////////////////////////////2路口按计划时间发车//////////////////////////////////////////////
//						for (int crossnum = 0; crossnum < spd8crossnum[2]; crossnum++)
//						{
//							if (carcrossid8[2][crossnum] == spd8crossid[cross][i])
//							{
//								cartime = car[carspeedid[speed][index8[spd8crossid[cross][i]]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
//							}
//						}
/////////////////////////////////////7路口按计划时间发车//////////////////////////////////////////////
//						for (int crossnum = 0; crossnum < spd8crossnum[7]; crossnum++)
//						{
//							if (carcrossid8[7][crossnum] == spd8crossid[cross][i])
//							{
//								cartime = car[carspeedid[speed][index8[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
//							}
//						}
/////////////////////////////////////个别路口计划时间发车结束///////////////////////////////////////////

						prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index8[spd8crossid[cross][i]]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
						lujing1 = searchPath(prev2, car[carspeedid[speed][index8[spd8crossid[cross][i]]]].srcCross, car[carspeedid[speed][index8[spd8crossid[cross][i]]]].desCross);
						carid = carspeedid[speed][index8[spd8crossid[cross][i]]] + tempcar;
						write(carid, cartime, lujing1, fp4);

					}
					else
					{
						cartime = temptime2 + k2;
						prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index8[spd8crossid[cross][i]]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
						lujing1 = searchPath(prev2, car[carspeedid[speed][index8[spd8crossid[cross][i]]]].srcCross, car[carspeedid[speed][index8[spd8crossid[cross][i]]]].desCross);
						carid = carspeedid[speed][index8[spd8crossid[cross][i]]] + tempcar;
						write(carid, cartime, lujing1, fp4);
						k2 = k2 + timeadd2;
						m2 = m2 + startnum[speed];
					}
				}
				m2 = 0;//注意要将m2再置为0
				temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
				k2 = 1;//让前后两个速度的车间隔为2
			}
			m2 = 0;//注意要将m2再置为0
			temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
			k2 = 8;//让前后两个速度的车间隔为2

		}
//
//			for (i = 0; i < carspeednum[speed]; i++)
//			{
//				if (i <= a1)
//					startnum[speed] = a1;//当前速度第一次发车数
//				else if (i > a1 && i <= a1 + 10 * a2)
//					startnum[speed] = a2;//当前速度车辆号为60-360的车一次发多少辆发10次
//				else if (i > a1 + 10 * a2 && i <= a1 + 10 * a2 + 10 * a3)
//					startnum[speed] = a3;//当前速度车辆号为360-560的车一次发多少辆发10次
//				else if (i > a1 + 10 * a2 + 10 * a3 && i <= a1 + 10 * a2 + 10 * a3 + 10 * a4)
//					startnum[speed] = a4;//当前速度车辆号为560-960的车一次发多少辆发10次
//				else if (i > a1 + 10 * a2 + 10 * a3 + 10 * a4 && i <= a1 + 10 * a2 + 10 * a3 + 10 * a4 + 10 * a5)
//					startnum[speed] = a5;//当前速度车辆号为60-360的车一次发多少辆发10次
//				else if (i > a1 + 10 * a2 + 10 * a3 + 10 * a4 + 10 * a5 && i <= a1 + 10 * a2 + 10 * a3 + 10 * a4 + 10 * a5 + 10 * a6)
//					startnum[speed] = a6;//当前速度车辆号为1260-1510的车一次发多少辆发10次
//				else if (i > a1 + 10 * a2 + 10 * a3 + 10 * a4 + 10 * a5 + 10 * a6 && i <= carspeednum[speed])
//					startnum[speed] = a7;//当前速度剩余车辆的发车数
//
//
//				if (i >= m2 && i < m2 + startnum[speed])
//				{
//					if ( i == a1 + 1 
//						|| i == a1 + 10 * a2 + 1 
//						|| i == a1 + 10 * a2 + 10 * a3 + 1 
//						|| i == a1 + 10 * a2 + 10 * a3 + 10 * a4 + 1
//						|| i == a1 + 10 * a2 + 10 * a3 + 10 * a4 + 10 * a5 + 1
//						|| i == a1 + 10 * a2 + 10 * a3 + 10 * a4 + 10 * a5 + 10 * a6 + 1
//						)
//					{
//						temptime2 = temptime2 + 1;
//					}
//					
///////////////////////////////////////个别路口适当延时发车/////////////////////////////////////////////
////
///////////////////////////////////////30路口适当延时发车//////////////////////////////////////////////
////					for (int crossnum = spd8crossnum[30]-20; crossnum < spd8crossnum[30]; crossnum++)
////					{
////						if (carcrossid8[30][crossnum] == i)
////						{
////							temptime2 = temptime2 + 1;
////							break;
////						}
////					}
////		
////////////////////////////////////个别路口适当延时发车结束///////////////////////////////////////////
//
//					cartime = temptime2 + k2;//实际发车时间
//
//////////////////////////////////让0-a1的车可以从1时刻出发///////////////////////////////////////////
//					if (i < a1)
//					{
//						cartime = car[carspeedid[speed][index8[i]]].plantime;//让车可以从1时刻出发
//					}
//
////////////////////////////////////个别路口按计划时间发车////////////////////////////////////////////
/////////////////////////////////////1路口按计划时间发车//////////////////////////////////////////////
//					for (int crossnum = 0; crossnum < spd8crossnum[1]-20; crossnum++)
//					{
//						if (carcrossid8[1][crossnum] == i)
//						{
//							cartime = car[carspeedid[speed][index8[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
//						}
//					}
/////////////////////////////////////64路口按计划时间发车//////////////////////////////////////////////
//					for (int crossnum = 0; crossnum < spd8crossnum[64]-20; crossnum++)
//					{
//						if (carcrossid8[64][crossnum] == i)
//						{
//							cartime = car[carspeedid[speed][index8[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
//						}
//					}
/////////////////////////////////////8路口按计划时间发车//////////////////////////////////////////////
//					for (int crossnum = 0; crossnum < spd8crossnum[8]-20; crossnum++)
//					{
//						if (carcrossid8[8][crossnum] == i)
//						{
//							cartime = car[carspeedid[speed][index8[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
//						}
//					}
/////////////////////////////////////57路口按计划时间发车//////////////////////////////////////////////
//					for (int crossnum = 0; crossnum < spd8crossnum[57]-20; crossnum++)
//					{
//						if (carcrossid8[57][crossnum] == i)
//						{
//							cartime = car[carspeedid[speed][index8[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
//						}
//					}
/////////////////////////////////////2路口按计划时间发车//////////////////////////////////////////////
//					for (int crossnum = 0; crossnum < spd8crossnum[2] - 20; crossnum++)
//					{
//						if (carcrossid8[2][crossnum] == i)
//						{
//							cartime = car[carspeedid[speed][index8[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
//						}
//					}
/////////////////////////////////////2路口按计划时间发车//////////////////////////////////////////////
//					for (int crossnum = 0; crossnum < spd8crossnum[7] - 20; crossnum++)
//					{
//						if (carcrossid8[7][crossnum] == i)
//						{
//							cartime = car[carspeedid[speed][index8[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
//						}
//					}
/////////////////////////////////////个别路口计划时间发车结束///////////////////////////////////////////
//
//					prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index8[i]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
//					lujing1 = searchPath(prev2, car[carspeedid[speed][index8[i]]].srcCross, car[carspeedid[speed][index8[i]]].desCross);
//					carid = carspeedid[speed][index8[i]] + tempcar;
//					write(carid, cartime, lujing1, fp4);
//
//				}
//				else
//				{
//					cartime = temptime2 + k2;
//					prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index8[i]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
//					lujing1 = searchPath(prev2, car[carspeedid[speed][index8[i]]].srcCross, car[carspeedid[speed][index8[i]]].desCross);
//					carid = carspeedid[speed][index8[i]] + tempcar;
//					write(carid, cartime, lujing1, fp4);
//					k2 = k2 + timeadd2;
//					m2 = m2 + startnum[speed];
//				}
//
//			}
//			m2 = 0;//注意要将m2再置为0
//			temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
//			k2 = 8;//让前后两个速度的车间隔为2
//		}
	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (speed == 6)
		{
			for (int cross = 1; cross <= 8; cross++)
			{
				for (int i = 0; i < spd6crosscnt[cross]; i++)
				{
					if (i <= b1)
                  	startnum[speed] = b1;//当前速度第一次发车数
					else if (i > b1 && i <= b1 + 2 * b2)
					startnum[speed] = b2;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > b1 + 2 * b2 && i <= b1 + 2 * b2 + 2 * b3)
					startnum[speed] = b3;//当前速度车辆号为360-560的车一次发多少辆发10次
					else if (i > b1 + 2 * b2 + 2 * b3 && i <= b1 + 2 * b2 + 2 * b3 + 2 * b4)
					startnum[speed] = b4;//当前速度车辆号为560-960的车一次发多少辆发10次
					else if (i > b1 + 2 * b2 + 2 * b3 + 2 * b4 && i <= b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5)
					startnum[speed] = b5;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5 && i <= b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5 + 2 * b6)
					startnum[speed] = b6;//当前速度车辆号为1260-1510的车一次发多少辆发10次
					else if (i > b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5 + 2 * b6 && i <= carspeednum[speed])
					startnum[speed] = b7;//当前速度剩余车辆的发车数

					if (i >= m2 && i < m2 + startnum[speed])
					{
					/*if (i == b1 + 1
						|| i == b1 + 2 * b2 + 1 
						|| i == b1 + 2 * b2 + 2 * b3 + 1
						|| i == b1 + 2 * b2 + 2 * b3 + 2 * b4 + 1
						|| i == b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5 + 1
						|| i == b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5 + 2 * b6 + 1 
						)
					{
						temptime2 = temptime2 + 1;
					}*/
						cartime = temptime2 + k2;
						if (i < 10)
						{
							cartime = car[carspeedid[speed][index6[spd6crossid[cross][i]]]].plantime;//让路径特别短的按计划时间出发
						}


						prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index6[spd6crossid[cross][i]]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
						lujing1 = searchPath(prev2, car[carspeedid[speed][index6[spd6crossid[cross][i]]]].srcCross, car[carspeedid[speed][index6[spd6crossid[cross][i]]]].desCross);
						carid = carspeedid[speed][index6[spd6crossid[cross][i]]] + tempcar;
						write(carid, cartime, lujing1, fp4);

					}
					else
					{
						cartime = temptime2 + k2;
						prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index6[spd6crossid[cross][i]]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
						lujing1 = searchPath(prev2, car[carspeedid[speed][index6[spd6crossid[cross][i]]]].srcCross, car[carspeedid[speed][index6[spd6crossid[cross][i]]]].desCross);
						carid = carspeedid[speed][index6[spd6crossid[cross][i]]] + tempcar;
						write(carid, cartime, lujing1, fp4);
						k2 = k2 + timeadd2;
						m2 = m2 + startnum[speed];
					}
				}
				m2 = 0;//注意要将m2再置为0
				temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
				k2 = 1;//让前后两个速度的车间隔为2
			}
			m2 = 0;//注意要将m2再置为0
			temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
			k2 = 8;//让前后两个速度的车间隔为8
		}
			
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
//			for (i = 0; i < carspeednum[speed]; i++)
//			{
//
//				if (i <= b1)
//					startnum[speed] = b1;//当前速度第一次发车数
//				else if (i > b1 && i <= b1 + 10 * b2)
//					startnum[speed] = b2;//当前速度车辆号为60-360的车一次发多少辆发10次
//				else if (i > b1 + 10 * b2 && i <= b1 + 10 * b2 + 10 * b3)
//					startnum[speed] = b3;//当前速度车辆号为360-560的车一次发多少辆发10次
//				else if (i > b1 + 10 * b2 + 10 * b3 && i <= b1 + 10 * b2 + 10 * b3 + 10 * b4)
//					startnum[speed] = b4;//当前速度车辆号为560-960的车一次发多少辆发10次
//				else if (i > b1 + 10 * b2 + 10 * b3 + 10 * b4 && i <= b1 + 10 * b2 + 10 * b3 + 10 * b4 + 10 * b5)
//					startnum[speed] = b5;//当前速度车辆号为60-360的车一次发多少辆发10次
//				else if (i > b1 + 10 * b2 + 10 * b3 + 10 * b4 + 10 * b5 && i <= b1 + 10 * b2 + 10 * b3 + 10 * b4 + 10 * b5 + 10 * b6)
//					startnum[speed] = b6;//当前速度车辆号为1260-1510的车一次发多少辆发10次
//				else if (i > b1 + 10 * b2 + 10 * b3 + 10 * b4 + 10 * b5 + 10 * b6 && i <= carspeednum[speed])
//					startnum[speed] = b7;//当前速度剩余车辆的发车数
//
//				if (i >= m2 && i < m2 + startnum[speed])
//				{
//
//					if (i == b1 + 1
//						|| i == b1 + 10 * b2 + 1 
//						|| i == b1 + 10 * b2 + 10 * b3 + 1
//						|| i == b1 + 10 * b2 + 10 * b3 + 10 * b4 + 1
//						|| i == b1 + 10 * b2 + 10 * b3 + 10 * b4 + 10 * b5 + 1
//						|| i == b1 + 10 * b2 + 10 * b3 + 10 * b4 + 10 * b5 + 10 * b6 + 1 
//						)
//					{
//						temptime2 = temptime2 + 1;
//					}
//
///////////////////////////////////////个别路口适当延时发车/////////////////////////////////////////////
////
///////////////////////////////////////30路口适当延时发车//////////////////////////////////////////////
////					
////					for (int crossnum = spd6crossnum[30] - 20; crossnum < spd6crossnum[30]; crossnum++)
////					{
////						if (carcrossid6[30][crossnum] == i)
////						{
////							temptime2 = temptime2 + 1;
////							break;
////						}
////					}
////
////
////////////////////////////////////个别路口适当延时发车结束///////////////////////////////////////////
//
//					cartime = temptime2 + k2;//实际发车时间
////
////////////////////////////////////////////个别路口按计划时间发车////////////////////////////////////////////
////////////////////////////////////////////1路口按计划时间发车//////////////////////////////////////////////
////					for (int crossnum = 0; crossnum < spd6crossnum[1] - 25; crossnum++)
////					{
////						if (carcrossid6[1][crossnum] == i)
////						{
////							cartime = car[carspeedid[speed][index6[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
////						}
////					}
///////////////////////////////////////64路口按计划时间发车//////////////////////////////////////////////
////					for (int crossnum = 0; crossnum < spd6crossnum[64] - 25; crossnum++)
////					{
////						if (carcrossid6[64][crossnum] == i)
////						{
////							cartime = car[carspeedid[speed][index6[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
////						}
////					}
///////////////////////////////////////8路口按计划时间发车//////////////////////////////////////////////
////					for (int crossnum = 0; crossnum < spd6crossnum[8] - 25; crossnum++)
////					{
////						if (carcrossid6[8][crossnum] == i)
////						{
////							cartime = car[carspeedid[speed][index6[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
////						}
////					}
///////////////////////////////////////57路口按计划时间发车//////////////////////////////////////////////
////					for (int crossnum = 0; crossnum < spd6crossnum[57] - 25; crossnum++)
////					{
////						if (carcrossid6[57][crossnum] == i)
////						{
////							cartime = car[carspeedid[speed][index6[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
////						}
////					}
///////////////////////////////////////2路口按计划时间发车//////////////////////////////////////////////
////					for (int crossnum = 0; crossnum < spd6crossnum[2] - 25; crossnum++)
////					{
////						if (carcrossid6[2][crossnum] == i)
////						{
////							cartime = car[carspeedid[speed][index6[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
////						}
////					}
///////////////////////////////////////个别路口计划时间发车结束///////////////////////////////////////////
//
//					prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index6[i]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
//					lujing1 = searchPath(prev2, car[carspeedid[speed][index6[i]]].srcCross, car[carspeedid[speed][index6[i]]].desCross);
//					carid = carspeedid[speed][index6[i]] + tempcar;
//					write(carid, cartime, lujing1, fp4);
//				}
//				else
//				{
//					cartime = temptime2 + k2;
//					prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index6[i]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
//					lujing1 = searchPath(prev2, car[carspeedid[speed][index6[i]]].srcCross, car[carspeedid[speed][index6[i]]].desCross);
//					carid = carspeedid[speed][index6[i]] + tempcar;
//					write(carid, cartime, lujing1, fp4);
//					k2 = k2 + timeadd2;
//					m2 = m2 + startnum[speed];
//				}
//
//			}
//			m2 = 0;//注意要将m2再置为0
//			temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
//			k2 = 6;//让前后两个速度的车间隔为2
//		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (speed == 4)
		{

			for (int cross = 1; cross <= 8; cross++)
			{
				for (int i = 0; i < spd4crosscnt[cross]; i++)
				{
					if (i <= c1)
						startnum[speed] = c1;//当前速度第一次发车数
					else if (i > c1 && i <= c1 + 2 * c2)
						startnum[speed] = c2;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > c1 + 2 * c2 && i <= c1 + 2 * c2 + 2 * c3)
						startnum[speed] = c3;//当前速度车辆号为360-560的车一次发多少辆发10次
					else if (i > c1 + 2 * c2 + 2 * c3 && i <= c1 + 2 * c2 + 2 * c3 + 2 * c4)
						startnum[speed] = c4;//当前速度车辆号为560-960的车一次发多少辆发10次
					else if (i > c1 + 2 * c2 + 2 * c3 + 2 * c4 && i <= c1 + 2 * c2 + 2 * c3 + 2 * c4 + 2 * c5)
						startnum[speed] = c5;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > c1 + 2 * c2 + 2 * c3 + 2 * c4 + 2 * c5 && i <= c1 + 2 * c2 + 2 * c3 + 2 * c4 + 2 * c5 + 2 * c6)
						startnum[speed] = c6;//当前速度车辆号为1260-1510的车一次发多少辆发10次
					else if (i > c1 + 2 * c2 + 2 * c3 + 2 * c4 + 2 * c5 + 10 * c6 && i <= carspeednum[speed])
						startnum[speed] = c7;//当前速度剩余车辆的发车数

					if (i >= m2 && i < m2 + startnum[speed])
					{
						/*if (i == b1 + 1
						|| i == b1 + 2 * b2 + 1
						|| i == b1 + 2 * b2 + 2 * b3 + 1
						|| i == b1 + 2 * b2 + 2 * b3 + 2 * b4 + 1
						|| i == b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5 + 1
						|| i == b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5 + 2 * b6 + 1
						)
						{
						temptime2 = temptime2 + 1;
						}*/
						cartime = temptime2 + k2;
						if (i < 5)
						{
							cartime = car[carspeedid[speed][index4[spd4crossid[cross][i]]]].plantime;//让路径特别短的按计划时间出发
						}


						prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index4[spd4crossid[cross][i]]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
						lujing1 = searchPath(prev2, car[carspeedid[speed][index4[spd4crossid[cross][i]]]].srcCross, car[carspeedid[speed][index4[spd4crossid[cross][i]]]].desCross);
						carid = carspeedid[speed][index4[spd4crossid[cross][i]]] + tempcar;
						write(carid, cartime, lujing1, fp4);

					}
					else
					{
						cartime = temptime2 + k2;
						prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index4[spd4crossid[cross][i]]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
						lujing1 = searchPath(prev2, car[carspeedid[speed][index4[spd4crossid[cross][i]]]].srcCross, car[carspeedid[speed][index4[spd4crossid[cross][i]]]].desCross);
						carid = carspeedid[speed][index4[spd4crossid[cross][i]]] + tempcar;
						write(carid, cartime, lujing1, fp4);
						k2 = k2 + timeadd2;
						m2 = m2 + startnum[speed];
					}
				}
				m2 = 0;//注意要将m2再置为0
				temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
				k2 = 1;//让前后两个速度的车间隔为2
			}
			m2 = 0;//注意要将m2再置为0
			temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
			k2 = 8;//让前后两个速度的车间隔为8
		}








/*			for (i = 0; i < carspeednum[speed]; i++)
			{
				if (i <= c1)
					startnum[speed] = c1;//当前速度第一次发车数
				else if (i > c1 && i <= c1 + 10 * c2)
					startnum[speed] = c2;//当前速度车辆号为60-360的车一次发多少辆发10次
				else if (i > c1 + 10 * c2 && i <= c1 + 10 * c2 + 10 * c3)
					startnum[speed] = c3;//当前速度车辆号为360-560的车一次发多少辆发10次
				else if (i > c1 + 10 * c2 + 10 * c3 && i <= c1 + 10 * c2 + 10 * c3 + 10 * c4)
					startnum[speed] = c4;//当前速度车辆号为560-960的车一次发多少辆发10次
				else if (i > c1 + 10 * c2 + 10 * c3 + 10 * c4 && i <= c1 + 10 * c2 + 10 * c3 + 10 * c4 + 10 * c5)
					startnum[speed] = c5;//当前速度车辆号为60-360的车一次发多少辆发10次
				else if (i > c1 + 10 * c2 + 10 * c3 + 10 * c4 + 10 * c5 && i <= c1 + 10 * c2 + 10 * c3 + 10 * c4 + 10 * c5 + 10 * c6)
					startnum[speed] = c6;//当前速度车辆号为1260-1510的车一次发多少辆发10次
				else if (i > c1 + 10 * c2 + 10 * c3 + 10 * c4 + 10 * c5 + 10 * c6 && i <= carspeednum[speed])
					startnum[speed] = c7;//当前速度剩余车辆的发车数

				if (i >= m2 && i < m2 + startnum[speed])
				{
					if (i == c1 + 1
						|| i == c1 + 10 * c2 + 1 
						|| i == c1 + 10 * c2 + 10 * c3 + 1 
						|| i == c1 + 10 * c2 + 10 * c3 + 10 * c4 + 1
						|| i == c1 + 10 * c2 + 10 * c3 + 10 * c4 + 10 * c5 + 1
						|| i == c1 + 10 * c2 + 10 * c3 + 10 * c4 + 10 * c5 + 10 * c6 + 1
						)
					{
						temptime2 = temptime2 + 1;//上述车辆数时间间隔+1
					}
					cartime = temptime2 + k2;

					/////////////////////////////////////1路口按计划时间发车//////////////////////////////////////////////
					//for (int crossnum = 0; crossnum < spd4crossnum[1] - 25; crossnum++)
					//{
					//	if (carcrossid4[1][crossnum] == i)
					//	{
					//		cartime = car[carspeedid[speed][index4[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
					//	}
					//}

					/////////////////////////////////////64路口按计划时间发车//////////////////////////////////////////////
					//for (int crossnum = 0; crossnum < spd4crossnum[64] - 25; crossnum++)
					//{
					//	if (carcrossid4[64][crossnum] == i)
					//	{
					//		cartime = car[carspeedid[speed][index4[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
					//	}
					//}
					/////////////////////////////////////8路口按计划时间发车//////////////////////////////////////////////
					//for (int crossnum = 0; crossnum < spd4crossnum[8] - 25; crossnum++)
					//{
					//	if (carcrossid4[8][crossnum] == i)
					//	{
					//		cartime = car[carspeedid[speed][index4[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
					//	}
					//}
					/////////////////////////////////////57路口按计划时间发车//////////////////////////////////////////////
					//for (int crossnum = 0; crossnum < spd4crossnum[57] - 25; crossnum++)
					//{
					//	if (carcrossid4[57][crossnum] == i)
					//	{
					//		cartime = car[carspeedid[speed][index4[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
					//	}
					//}
					prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index4[i]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
					lujing1 = searchPath(prev2, car[carspeedid[speed][index4[i]]].srcCross, car[carspeedid[speed][index4[i]]].desCross);
					carid = carspeedid[speed][index4[i]] + tempcar;
					write(carid, cartime, lujing1, fp4);
				}
				else
				{
					cartime = temptime2 + k2;
					prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index4[i]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
					lujing1 = searchPath(prev2, car[carspeedid[speed][index4[i]]].srcCross, car[carspeedid[speed][index4[i]]].desCross);
					carid = carspeedid[speed][index4[i]] + tempcar;
					write(carid, cartime, lujing1, fp4);
					k2 = k2 + timeadd2;
					m2 = m2 + startnum[speed];
				}
			}
			m2 = 0;//注意要将m2再置为0
			temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
			k2 = 10;//让前后两个速度的车间隔为2
		}*/

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (speed == 2)
		{

			for (int cross = 1; cross <= 8; cross++)
			{
				for (int i = 0; i < spd2crosscnt[cross]; i++)
				{
					if (i <= d1)
						startnum[speed] = d1;//当前速度第一次发车数
					else if (i > d1 && i <= d1 + 2 * d2)
						startnum[speed] = d2;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > d1 + 2 * d2 && i <= d1 + 2 * d2 + 2 * d3)
						startnum[speed] = d3;//当前速度车辆号为360-560的车一次发多少辆发10次
					else if (i > d1 + 2 * d2 + 2 * d3 && i <= d1 + 2 * d2 + 2 * d3 + 2 * d4)
						startnum[speed] = d4;//当前速度车辆号为560-960的车一次发多少辆发10次
					else if (i > d1 + 2 * d2 + 2 * d3 + 2 * d4 && i <= d1 + 2 * d2 + 2 * d3 + 2 * d4 + 2 * d5)
						startnum[speed] = d5;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > d1 + 2 * d2 + 2 * d3 + 2 * d4 + 2 * d5 && i <= d1 + 2 * d2 + 2 * d3 + 2 * d4 + 2 * d5 + 2 * d6)
						startnum[speed] = d6;//当前速度车辆号为1260-1510的车一次发多少辆发10次
					else if (i > d1 + 2 * d2 + 2 * d3 + 2 * d4 + 2 * d5 + 2 * d6 && i <= carspeednum[speed])
						startnum[speed] = d7;//当前速度剩余车辆的发车数

					if (i >= m2 && i < m2 + startnum[speed])
					{
						/*if (i == b1 + 1
						|| i == b1 + 2 * b2 + 1
						|| i == b1 + 2 * b2 + 2 * b3 + 1
						|| i == b1 + 2 * b2 + 2 * b3 + 2 * b4 + 1
						|| i == b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5 + 1
						|| i == b1 + 2 * b2 + 2 * b3 + 2 * b4 + 2 * b5 + 2 * b6 + 1
						)
						{
						temptime2 = temptime2 + 1;
						}*/
						cartime = temptime2 + k2;
						//if (i < 5)
						//{
						//	cartime = car[carspeedid[speed][index4[spd4crossid[cross][i]]]].plantime;//让路径特别短的按计划时间出发
						//}


						prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index2[spd2crossid[cross][i]]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
						lujing1 = searchPath(prev2, car[carspeedid[speed][index2[spd2crossid[cross][i]]]].srcCross, car[carspeedid[speed][index2[spd2crossid[cross][i]]]].desCross);
						carid = carspeedid[speed][index2[spd2crossid[cross][i]]] + tempcar;
						write(carid, cartime, lujing1, fp4);

					}
					else
					{
						cartime = temptime2 + k2;
						prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index2[spd2crossid[cross][i]]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
						lujing1 = searchPath(prev2, car[carspeedid[speed][index2[spd2crossid[cross][i]]]].srcCross, car[carspeedid[speed][index2[spd2crossid[cross][i]]]].desCross);
						carid = carspeedid[speed][index2[spd2crossid[cross][i]]] + tempcar;
						write(carid, cartime, lujing1, fp4);
						k2 = k2 + timeadd2;
						m2 = m2 + startnum[speed];
					}
				}
				m2 = 0;//注意要将m2再置为0
				temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
				k2 = 1;//让前后两个速度的车间隔为2
			}
		}




//			for (i = 0; i < carspeednum[speed]; i++)
//			{
//				if (i <= d1)
//					startnum[speed] = d1;//当前速度第一次发车数
//				else if (i > d1 && i <= d1 + 10 * d2)
//					startnum[speed] = d2;//当前速度车辆号为60-360的车一次发多少辆发10次
//				else if (i > d1 + 10 * d2 && i <= d1 + 10 * d2 + 10 * d3)
//					startnum[speed] = d3;//当前速度车辆号为360-560的车一次发多少辆发10次
//				else if (i > d1 + 10 * d2 + 10 * d3 && i <= d1 + 10 * d2 + 10 * d3 + 10 * d4)
//					startnum[speed] = d4;//当前速度车辆号为560-960的车一次发多少辆发10次
//				else if (i > d1 + 10 * d2 + 10 * d3 + 10 * d4 && i <= d1 + 10 * d2 + 10 * d3 + 10 * d4 + 10 * d5)
//					startnum[speed] = d5;//当前速度车辆号为60-360的车一次发多少辆发10次
//				else if (i > d1 + 10 * d2 + 10 * d3 + 10 * d4 + 10 * d5 && i <= d1 + 10 * d2 + 10 * d3 + 10 * d4 + 10 * d5 + 10 * d6)
//					startnum[speed] = d6;//当前速度车辆号为1260-1510的车一次发多少辆发10次
//				else if (i > d1 + 10 * d2 + 10 * d3 + 10 * d4 + 10 * d5 + 10 * d6 && i <= carspeednum[speed])
//					startnum[speed] = d7;//当前速度剩余车辆的发车数
//
//
//				if (i >= m2 && i < m2 + startnum[speed])
//				{
//					if (i == d1 + 1
//						|| i == d1 + 10 * d2 + 1
//						|| i == d1 + 10 * d2 + 10 * d3 + 1
//						|| i == d1 + 10 * d2 + 10 * d3 + 10 * d4 + 1
//						|| i == d1 + 10 * d2 + 10 * d3 + 10 * d4 + 10 * d5 + 1
//						|| i == d1 + 10 * d2 + 10 * d3 + 10 * d4 + 10 * d5 + 10 * d6 + 1
//						)
//					{
//						temptime2 = temptime2 + 1;//上述车辆数时间间隔+1
//					}
//
///////////////////////////////////////个别路口适当延时发车/////////////////////////////////////////////
////					
///////////////////////////////////////30路口适当延时发车//////////////////////////////////////////////
////					for (int crossnum = spd2crossnum[30]-20; crossnum < spd2crossnum[30]; crossnum++)
////				    {
////					     if (carcrossid2[30][crossnum] == i)
////							{
////									temptime2 = temptime2 + 1;
////									break;
////							}
////						}
////							
////////////////////////////////////个别路口适当延时发车结束///////////////////////////////////////////
//					cartime = temptime2 + k2;
//
///////////////////////////////////////1路口按计划时间发车//////////////////////////////////////////////
////					for (int crossnum = 0; crossnum < spd2crossnum[1] - 20; crossnum++)
////					{
////						if (carcrossid2[1][crossnum] == i)
////						{
////							cartime = car[carspeedid[speed][index2[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
////						}
////					}
////
///////////////////////////////////////64路口按计划时间发车//////////////////////////////////////////////
////					for (int crossnum = 0; crossnum < spd2crossnum[64] - 20; crossnum++)
////					{
////						if (carcrossid2[64][crossnum] == i)
////						{
////							cartime = car[carspeedid[speed][index2[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
////						}
////					}
///////////////////////////////////////8路口按计划时间发车//////////////////////////////////////////////
////					for (int crossnum = 0; crossnum < spd2crossnum[8] - 20; crossnum++)
////					{
////						if (carcrossid2[8][crossnum] == i)
////						{
////							cartime = car[carspeedid[speed][index2[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
////						}
////					}
///////////////////////////////////////57路口按计划时间发车//////////////////////////////////////////////
////					for (int crossnum = 0; crossnum < spd2crossnum[57] - 20; crossnum++)
////					{
////						if (carcrossid2[57][crossnum] == i)
////						{
////							cartime = car[carspeedid[speed][index2[i]]].plantime;//由于1路口附近在刚开始发车时车比较少，故让其提前尽早发车
////						}
////					}
//
//					prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index2[i]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
//					lujing1 = searchPath(prev2, car[carspeedid[speed][index2[i]]].srcCross, car[carspeedid[speed][index2[i]]].desCross);
//					carid = carspeedid[speed][index2[i]] + tempcar;
//					write(carid, cartime, lujing1, fp4);
//				}
//				else
//				{
//					cartime = temptime2 + k2;
//					prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index2[i]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
//					lujing1 = searchPath(prev2, car[carspeedid[speed][index2[i]]].srcCross, car[carspeedid[speed][index2[i]]].desCross);
//					carid = carspeedid[speed][index2[i]] + tempcar;
//					write(carid, cartime, lujing1, fp4);
//					k2 = k2 + timeadd2;
//					m2 = m2 + startnum[speed];
//				}
//
//			}
//
//		}

	}
}