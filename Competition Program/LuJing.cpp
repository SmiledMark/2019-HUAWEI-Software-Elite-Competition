#include <stdio.h>
#include <stdlib.h>
#include"struct.h"
int* searchPath(int *prev1, int src, int des);
int* Dijkstra(int n, int src, int c[MAXCROSS + 1][MAXCROSS + 1]);
MGraph* MgraphDij(MGraph* GDij);
void write(int carid, int cartime, int *lujing, FILE* fp4);
void maopaosortdown(int* a, int length, int* b);
void maopaosortup(int* a, int length, int* b);
int* Dijdis(int n, int src, int c[MAXCROSS + 1][MAXCROSS + 1]);
int **matrixINT(int row, int column);
void LuJing(Car* car, FILE *fp4)

{
///////////////////////////////////变量设置/////////////////////////////////////////////////////////////////
	int carnum = numLine2;//numline2 is the total num of car 
	int* lujing1 = NULL;
	lujing1 = (int *)malloc((MAXCROSS + 1)*sizeof(int));
	int* prev2 = NULL;
	int j = 1;
	int carid, cartime;
	int crossNum = numLine3 / 8;//大路口的数量，分几个大路口就除以几，但是注意这里是整除，如果不能整除就把分母变的小一点
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
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////将源点到终点的最短距离输出////////////////
	//int distance[MAXCROSS + 1][MAXCROSS + 1];//任意两个节点之间的最短距离
	int** distance = matrixINT(MAXCROSS + 1, MAXCROSS + 1);
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

	/////////////////给各个速度的车辆赋予车辆编号////////////////
	//int carspeedid[9][MAXCAR / 3];//记录已某个速度出发的车辆的ID号
	int** carspeedid = matrixINT(9, MAXCAR / 3);//比如速度为6，8，10那么这里的9应该改为11
	int carspeednum[9];//比如速度为6，8，10那么这里的9应该改为11
	for (int i = 1; i <= 8; i++)//注意上面的9必须根据实际地图来进行更改必须是速度数加1
	{
		carspeednum[i] = 0;
	}
	for (int i = 0; i < numLine2; i++)
	{
		carspeedid[car[i].maxspeed][carspeednum[car[i].maxspeed]++] = i;
	}

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
	int** spd8crossid = matrixINT(numLine3 / 8 + 1, MAXCAR / 20);//当前速度竖着的8个路口为一组，对应的车辆ID
	int* spd8crosscnt = NULL;
	spd8crosscnt = (int*)malloc(sizeof(int)*(numLine3 / 3 + 1));
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
	for (int i = 0; i < numLine3 / 8 + 1; i++)
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
			spd8crossid[1][spd8crosscnt[1]++] = i;//记录当前速度下一路口的车辆ID
		}
		/////////将57-64路口设成三路口，也就是最右边那些路口/////////
		if (car[carspeedid[8][index8[i]]].srcCross == 57 || car[carspeedid[8][index8[i]]].srcCross == 58
			|| car[carspeedid[8][index8[i]]].srcCross == 59 || car[carspeedid[8][index8[i]]].srcCross == 60
			|| car[carspeedid[8][index8[i]]].srcCross == 61 || car[carspeedid[8][index8[i]]].srcCross == 62
			|| car[carspeedid[8][index8[i]]].srcCross == 63 || car[carspeedid[8][index8[i]]].srcCross == 64)
		{
			spd8crossid[1][spd8crosscnt[1]++] = i;//记录当前速度下一路口的车辆ID
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

////////////////////////////////////开始发车//////////////////////////////////////////////////////////////////
//////////////////////////每次发车数不定(按速度从大往小发)///////////////////////////////////////////////////
	int startnum[9];//各个速度每次的发车数量,如果速度为6，8，10，那么这里的9应改为11
	int i;
	int m2 = 0;
	int temptime2 = 10;
	int k2 = 0;
	int timeadd2 = 1;//每次发车的时间间隔
	int cishu = 2;//每次的发车次数

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
	printf("second car scope: %d--%d\n", a1, a1 + cishu * a2);
	printf("third car num: %d\n", a3);
	printf("third car scope:%d--%d\n", a1 + cishu * a2, a1 + cishu * a2 + cishu * a3);
	printf("fourth car num: %d\n", a4);
	printf("fourth car scope: %d--%d\n", a1 + cishu * a2 + cishu * a3, a1 + cishu * a2 + cishu * a3 + cishu * a4);
	printf("fifth car num: %d\n", a5);
	printf("fifth car scope: %d--%d\n", a1 + cishu * a2 + cishu * a3 + cishu * a4, a1 + cishu * a2 + cishu * a3 + cishu * a4 + cishu * a5);
	printf("sixth car num: %d\n", a6);
	printf("sixth car scope: %d--%d\n", a1 + cishu * a2 + cishu * a3 + cishu * a4 + cishu * a5, a1 + cishu * a2 + cishu * a3 + cishu * a4 + cishu * a5 + cishu * a6);
	printf("seventh car num: %d\n", a7);
	printf("seventh car scope: %d--%d\n", a1 + cishu * a2 + cishu * a3 + cishu * a4 + cishu * a5 + cishu * a6, spd8crosscnt[1] - a1);

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
	printf("second car scope: %d--%d\n", b1, b1 + cishu * b2);
	printf("third car num: %d\n", b3);
	printf("third car scope:%d--%d\n", b1 + cishu * b2, b1 + cishu * b2 + cishu * b3);
	printf("fourth car num: %d\n", b4);
	printf("fourth car scope: %d--%d\n", b1 + cishu * b2 + cishu * b3, b1 + cishu * b2 + cishu * b3 + cishu * b4);
	printf("fifth car num: %d\n", b5);
	printf("fifth car scope: %d--%d\n", b1 + cishu * b2 + cishu * b3 + cishu * b4, b1 + cishu * b2 + cishu * b3 + cishu * b4 + cishu * b5);
	printf("sixth car num: %d\n", b6);
	printf("sixth car scope: %d--%d\n", b1 + cishu * b2 + cishu * b3 + cishu * b4 + cishu * b5, b1 + cishu * b2 + cishu * b3 + cishu * b4 + cishu * b5 + 3 * b6);
	printf("seventh car num: %d\n", b7);
	printf("seventh car scope: %d--%d\n", b1 + cishu * b2 + cishu * b3 + cishu * b4 + cishu * b5 + cishu * b6, spd6crosscnt[1] - b1);

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
	printf("second car scope: %d--%d\n", c1, c1 + cishu * c2);
	printf("third car num: %d\n", c3);
	printf("third car scope:%d--%d\n", c1 + cishu * c2, c1 + cishu * c2 + cishu * c3);
	printf("fourth car num: %d\n", c4);
	printf("fourth car scope: %d--%d\n", c1 + cishu * c2 + cishu * c3, c1 + cishu * c2 + cishu * c3 + cishu * c4);
	printf("fifth car num: %d\n", c5);
	printf("fifth car scope: %d--%d\n", c1 + cishu * c2 + cishu * c3 + cishu * c4, c1 + cishu * c2 + cishu * c3 + cishu * c4 + cishu * c5);
	printf("sixth car num: %d\n", c6);
	printf("sixth car scope: %d--%d\n", c1 + cishu * c2 + cishu * c3 + cishu * c4 + cishu * c5, c1 + cishu * c2 + cishu * c3 + cishu * c4 + cishu * c5 + cishu * c6);
	printf("seventh car num: %d\n", c7);
	printf("seventh car scope: %d--%d\n", c1 + cishu * c2 + cishu * c3 + cishu * c4 + cishu * c5 + cishu * c6, spd4crosscnt[1] - c1);


	///////////////speed=2发车数量设置////////////////////
	int d1, d2, d3, d4, d5, d6, d7, spd2;
	spd2 = 2;
	d1 = 45;//第一次发车数，发1次
	d2 = 40;//第二次发车数，发10次
	d3 = 35;//第三次发车数，发10次
	d4 = 30;//第四次发车数，发10次
	d5 = 25;//第五次发车数，发10次
	d6 = 20;//第六次发车数，发10次
	d7 = 15;//第七次发车数，发10次
	printf("/////////////////////////////////////////////\n");
	printf("speed=%d\n", spd2);
	printf("first car num: %d\n", d1);
	printf("first car scope: 0--%d\n", d1);
	printf("second car num: %d\n", d2);
	printf("second car scope: %d--%d\n", d1, d1 + cishu * d2);
	printf("third car num: %d\n", d3);
	printf("third car scope:%d--%d\n", d1 + cishu * d2, d1 + cishu * d2 + cishu * d3);
	printf("fourth car num: %d\n", d4);
	printf("fourth car scope: %d--%d\n", d1 + cishu * d2 + cishu * d3, d1 + cishu * d2 + cishu * d3 + cishu * d4);
	printf("fifth car num: %d\n", d5);
	printf("fifth car scope: %d--%d\n", d1 + cishu * d2 + cishu * d3 + cishu * d4, d1 + cishu * d2 + cishu * d3 + cishu * d4 + cishu * d5);
	printf("sixth car num: %d\n", d6);
	printf("sixth car scope: %d--%d\n", d1 + cishu * d2 + cishu * d3 + cishu * d4 + cishu * d5, d1 + cishu * d2 + cishu * d3 + cishu * d4 + cishu * d5 + cishu * d6);
	printf("seventh car num: %d\n", d7);
	printf("seventh car scope: %d--%d\n", d1 + cishu * d2 + cishu * d3 + cishu * d4 + cishu * d5 + cishu * d6, spd4crosscnt[1] - d1);


	for (int speed = 8; speed >= 1; speed--)
	{
		
//////////////////////////////////////////速度8开始发车/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (speed == 8)
		{
			for (int cross = 1; cross <= crossNum; cross++)
			{
				for (int i = 0; i < spd8crosscnt[cross]; i++)
				{
					if (cross == 1)
					{
						a1 = 90;//第一次发车数，发1次
						a2 = 110;//第二次发车数，发2次
						a3 = 90;//第三次发车数，发2次
						a4 = 80;//第四次发车数，发2次
						a5 = 70;//第五次发车数，发2次
						a6 = 50;//第六次发车数，发2次
						a7 = 30;//第七次发车数
					}
					else
					{
						a1 = 50;//第一次发车数，发1次
						a2 = 70;//第二次发车数，发2次
						a3 = 50;//第三次发车数，发2次
						a4 = 40;//第四次发车数，发2次
						a5 = 40;//第五次发车数，发2次
						a6 = 30;//第六次发车数，发2次
						a7 = 25;//第七次发车数
					}



					if (i <= a1)
						startnum[speed] = a1;//当前速度第一次发车数
					else if (i > a1 && i <= a1 + cishu * a2)
						startnum[speed] = a2;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > a1 + cishu * a2 && i <= a1 + cishu * a2 + cishu * a3)
						startnum[speed] = a3;//当前速度车辆号为360-560的车一次发多少辆发10次
					else if (i > a1 + cishu * a2 + cishu * a3 && i <= a1 + cishu * a2 + cishu * a3 + cishu * a4)
						startnum[speed] = a4;//当前速度车辆号为560-960的车一次发多少辆发10次
					else if (i > a1 + cishu * a2 + cishu * a3 + cishu * a4 && i <= a1 + cishu * a2 + cishu * a3 + cishu * a4 + cishu * a5)
						startnum[speed] = a5;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > a1 + cishu * a2 + cishu * a3 + cishu * a4 + cishu * a5 && i <= a1 + cishu * a2 + cishu * a3 + cishu * a4 + cishu * a5 + cishu * a6)
						startnum[speed] = a6;//当前速度车辆号为1260-1510的车一次发多少辆发10次
					else if (i > a1 + cishu * a2 + cishu * a3 + cishu * a4 + cishu * a5 + cishu * a6 && i <= spd8crosscnt[cross])
						startnum[speed] = a7;//当前速度剩余车辆的发车数

					if (i >= m2 && i < m2 + startnum[speed])
					{

						///////////////////////////根据判题器个别路口个别车延时发车/////////////////////////////////////////////
						//if (cross==4||cross==6)//要根据实际情况进行更改，根据判题器，在六路口发车时发生死锁，但五路口发车时也有影响
						//{
						//	if (i == a1 + 1
						//	|| i == a1 + cishu * a2 + 1
						//    || i == a1 + cishu * a2 + cishu * a3 + 1
						//	/*|| i == a1 + cishu * a2 + cishu * a3 + cishu * a4 + 1
						//    || i == a1 + cishu * a2 + cishu * a3 + cishu * a4 + cishu * a5 + 1
						//	|| i == a1 + cishu * a2 + cishu * a3 + cishu * a4 + cishu * a5 + cishu * a6 + 1*/
						//	)
						//	{
						//	temptime2 = temptime2 + 2;
						//	}
						//}
						///////////////////////////根据判题器个别路口个别车延时发车结束/////////////////////////////////////////////

						cartime = temptime2 + k2;
						if (i <= a1)
						{
							cartime = car[carspeedid[speed][index8[spd8crossid[cross][i]]]].plantime;//每个路口的前a1辆车以计划时间出发
						}
						prev2 = Dijkstra(MAXCROSS, car[carspeedid[speed][index8[spd8crossid[cross][i]]]].srcCross, GDij1->roadlen1);//其实这里的没必要传递MAXCROSS改为真实路口数numline3即可
						lujing1 = searchPath(prev2, car[carspeedid[speed][index8[spd8crossid[cross][i]]]].srcCross, car[carspeedid[speed][index8[spd8crossid[cross][i]]]].desCross);
						carid = carspeedid[speed][index8[spd8crossid[cross][i]]] + tempcar;
						write(carid, cartime, lujing1, fp4);

					}
					else
					{
						cartime = temptime2 + k2;
						if (i == a1)
						{
							cartime = car[carspeedid[speed][index8[spd8crossid[cross][i]]]].plantime;//每个路口的前a1辆车以计划时间出发
						}
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
				k2 = 1;//让前后两个路口的间隔为1
///////////////////////根据判题器输出来进行两个路口之间间隔的调整////////////////////////
				//if (cross==2||cross==3||cross==5)
				//{
				//	k2 = 2;
				//}
//////////////////////////相邻两路口间隔调整结束/////////////////////////////////////////
			}
			m2 = 0;//注意要将m2再置为0
			temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
			k2 = 8;//让前后两个速度的车间隔为2

		}
//////////////////////////////////////////速度8发车结束/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////速度6开始发车/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (speed == 6)
		{
			for (int cross = 1; cross <= crossNum; cross++)
			{
				for (int i = 0; i < spd6crosscnt[cross]; i++)
				{
					if (i <= b1)
						startnum[speed] = b1;//当前速度第一次发车数
					else if (i > b1 && i <= b1 + cishu * b2)
						startnum[speed] = b2;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > b1 + cishu * b2 && i <= b1 + cishu * b2 + cishu * b3)
						startnum[speed] = b3;//当前速度车辆号为360-560的车一次发多少辆发10次
					else if (i > b1 + cishu * b2 + cishu * b3 && i <= b1 + cishu * b2 + cishu * b3 + cishu * b4)
						startnum[speed] = b4;//当前速度车辆号为560-960的车一次发多少辆发10次
					else if (i > b1 + cishu * b2 + cishu * b3 + cishu * b4 && i <= b1 + cishu * b2 + cishu * b3 + cishu * b4 + cishu * b5)
						startnum[speed] = b5;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > b1 + cishu * b2 + cishu * b3 + cishu * b4 + cishu * b5 && i <= b1 + cishu * b2 + cishu * b3 + cishu * b4 + cishu * b5 + cishu * b6)
						startnum[speed] = b6;//当前速度车辆号为1260-1510的车一次发多少辆发10次
					else if (i > b1 + cishu * b2 + cishu * b3 + cishu * b4 + cishu * b5 + cishu * b6 && i <= spd6crosscnt[cross])
						startnum[speed] = b7;//当前速度剩余车辆的发车数

					if (i >= m2 && i < m2 + startnum[speed])
					{
						///////////////////////////根据判题器个别路口个别车延时发车/////////////////////////////////////////////
						//if (cross == 3)//要根据实际情况进行更改，根据判题器反馈的死锁时间判断是哪个速度的哪个
						//{              //路口或哪几个路口发车有点多，在这里还是发这么多但是加一点延时再发
						//	if (i == b1 + 1
						//		|| i == b1 + cishu * b2 + 1
						//		|| i == b1 + cishu * b2 + cishu * b3 + 1
						//		/*|| i == b1 + cishu * b2 + cishu * b3 + cishu * b4 + 1
						//        || i == b1 + cishu * b2 + cishu * b3 + cishu * b4 + cishu * b5 + 1
						//        || i == b1 + cishu * b2 + cishu * b3 + cishu * b4 + cishu * b5 + cishu * b6 + 1*/
						//		)
						//	{
						//		temptime2 = temptime2 + 2;
						//	}
						//}
						//if (cross == 4)//要根据实际情况进行更改，根据判题器反馈的死锁时间判断是哪个速度的哪个
						//{              //路口或哪几个路口发车有点多，在这里还是发这么多但是加一点延时再发
						//	if (//i == a1 + 1
						//		 i == a1 + 2 * a2 + 1
						//		|| i == a1 + 2 * a2 + 2 * a3 + 1
						//		//|| i == a1 + 2 * a2 + 2 * a3 + 2 * a4 + 1
						//		)
						//	{
						//		temptime2 = temptime2 + 2;
						//	}
						//}
						///////////////////////////根据判题器个别路口个别车延时发车结束/////////////////////////////////////////////

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
				k2 = 1;//让当前速度下前后两个路口的间隔为1
///////////////////////根据判题器输出来进行两个路口之间间隔的调整////////////////////////
				//if (cross == 3 )
				//{
				//	k2 = 2;
				//}
//////////////////////////相邻两路口间隔调整结束/////////////////////////////////////////
			}
			m2 = 0;//注意要将m2再置为0
			temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
			k2 = 8;//让前后两个速度的车间隔为8
		}

/////////////////////////////////////////////速度6发车结束/////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////速度4开始发车///////////////////////////////////////////////////////////
	
		if (speed == 4)
		{
			for (int cross = 1; cross <= crossNum; cross++)
			{
				for (int i = 0; i < spd4crosscnt[cross]; i++)
				{
					if (i <= c1)
						startnum[speed] = c1;//当前速度第一次发车数
					else if (i > c1 && i <= c1 + cishu * c2)
						startnum[speed] = c2;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > c1 + cishu * c2 && i <= c1 + cishu * c2 + cishu * c3)
						startnum[speed] = c3;//当前速度车辆号为360-560的车一次发多少辆发10次
					else if (i > c1 + cishu * c2 + cishu * c3 && i <= c1 + cishu * c2 + cishu * c3 + cishu * c4)
						startnum[speed] = c4;//当前速度车辆号为560-960的车一次发多少辆发10次
					else if (i > c1 + cishu * c2 + cishu * c3 + cishu * c4 && i <= c1 + cishu * c2 + cishu * c3 + cishu * c4 + cishu * c5)
						startnum[speed] = c5;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > c1 + cishu * c2 + cishu * c3 + cishu * c4 + cishu * c5 && i <= c1 + cishu * c2 + cishu * c3 + cishu * c4 + cishu * c5 + cishu * c6)
						startnum[speed] = c6;//当前速度车辆号为1260-1510的车一次发多少辆发10次
					else if (i > c1 + cishu * c2 + cishu * c3 + cishu * c4 + cishu * c5 + cishu * c6 && i <= spd4crosscnt[cross])
						startnum[speed] = c7;//当前速度剩余车辆的发车数

					if (i >= m2 && i < m2 + startnum[speed])
					{
						
						/////////////////////////////根据判题器个别路口个别车延时发车/////////////////////////////////////////////
						//if (cross == 7)//要根据实际情况进行更改，根据判题器反馈的死锁时间判断是哪个速度的哪个
						//{              //路口或哪几个路口发车有点多，在这里还是发这么多但是加一点延时再发
						//	if (i == c1 + 1
						//		|| i == c1 + cishu * c2 + 1
						//		|| i == c1 + cishu * c2 + cishu * c3 + 1
						//		|| i == c1 + cishu * c2 + cishu * c3 + cishu * c4 + 1
						//		|| i == c1 + cishu * c2 + cishu * c3 + cishu * c4 + cishu * c5 + 1
						//		|| i == c1 + cishu * c2 + cishu * c3 + cishu * c4 + cishu * c5 + cishu * c6 + 1
						//		)
						//	{
						//		temptime2 = temptime2 + 2;
						//	}
						//}
						//if (cross == 6)//要根据实际情况进行更改，根据判题器反馈的死锁时间判断是哪个速度的哪个
						//{              //路口或哪几个路口发车有点多，在这里还是发这么多但是加一点延时再发
						//	if ( //i == a1 + 1
						//		  i == a1 + 2 * a2 + 1
						//		  || i == a1 + 2 * a2 + 2 * a3 + 1
						//		//|| i == a1 + 10 * a2 + 10 * a3 + 10 * a4 + 1
						//		//|| i == a1 + 10 * a2 + 10 * a3 + 10 * a4 + 10 * a5 + 1
						//		//|| i == a1 + 10 * a2 + 10 * a3 + 10 * a4 + 10 * a5 + 10 * a6 + 1
						//		)
						//	{
						//		temptime2 = temptime2 + 2;
						//	}
						//}
						//if (cross == 5)//要根据实际情况进行更改，根据判题器反馈的死锁时间判断是哪个速度的哪个
						//{              //路口或哪几个路口发车有点多，在这里还是发这么多但是加一点延时再发
						//	if ( //i == a1 + 1
						//		i == a1 + 2 * a2 + 1
						//		|| i == a1 + 2 * a2 + 2 * a3 + 1
						//		//|| i == a1 + 10 * a2 + 10 * a3 + 10 * a4 + 1
						//		//|| i == a1 + 10 * a2 + 10 * a3 + 10 * a4 + 10 * a5 + 1
						//		//|| i == a1 + 10 * a2 + 10 * a3 + 10 * a4 + 10 * a5 + 10 * a6 + 1
						//		)
						//	{
						//		temptime2 = temptime2 + 2;
						//	}
						//}
						//if (cross == 4)//要根据实际情况进行更改，根据判题器反馈的死锁时间判断是哪个速度的哪个
						//{              //路口或哪几个路口发车有点多，在这里还是发这么多但是加一点延时再发
						//	if ( i == a1 + 1
						//		|| i == a1 + cishu * a2 + 1
						//		|| i == a1 + cishu * a2 + cishu * a3 + 1
						//		|| i == a1 + cishu * a2 + cishu * a3 + cishu * a4 + 1
						//		|| i == a1 + cishu * a2 + cishu * a3 + cishu * a4 + cishu * a5 + 1
						//		|| i == a1 + cishu * a2 + cishu * a3 + cishu * a4 + cishu * a5 + cishu * a6 + 1
						//		)
						//	{
						//		temptime2 = temptime2 + 2;
						//	}
						//}
						///////////////////////////根据判题器个别路口个别车延时发车结束/////////////////////////////////////////////

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
				k2 = 1;//让当前速度两个路口之间的间隔为1
				
				///////根据判题器得知在速度4的7路口发车时发生死锁，故让6路口和7路口之间间隔为3////////////////////////
				/*if (cross == 7||cross==2||cross==4)
				{
					k2 = 3;
				}*/
				/////////////当前速度路口间隔设置结束/////////////////////////////////////////////////////////////////

			}
			m2 = 0;//注意要将m2再置为0
			temptime2 = cartime;//要将速度为8最后一批车的出发时间赋给temptime2因为下一个的速度是在这个基础上再进行加
			k2 = 8;//让前后两个速度的车间隔为8
		}
////////////////////////////////////////////速度4发车结束///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

////////////////////////////////////////////速度2开始发车///////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (speed == 2)
		{

			for (int cross = 1; cross <= crossNum; cross++)
			{
				for (int i = 0; i < spd2crosscnt[cross]; i++)
				{
					if (i <= d1)
						startnum[speed] = d1;//当前速度第一次发车数
					else if (i > d1 && i <= d1 + cishu * d2)
						startnum[speed] = d2;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > d1 + cishu * d2 && i <= d1 + cishu * d2 + cishu * d3)
						startnum[speed] = d3;//当前速度车辆号为360-560的车一次发多少辆发10次
					else if (i > d1 + cishu * d2 + cishu * d3 && i <= d1 + cishu * d2 + cishu * d3 + cishu * d4)
						startnum[speed] = d4;//当前速度车辆号为560-960的车一次发多少辆发10次
					else if (i > d1 + cishu * d2 + cishu * d3 + cishu * d4 && i <= d1 + cishu * d2 + cishu * d3 + cishu * d4 + cishu * d5)
						startnum[speed] = d5;//当前速度车辆号为60-360的车一次发多少辆发10次
					else if (i > d1 + cishu * d2 + cishu * d3 + cishu * d4 + cishu * d5 && i <= d1 + cishu * d2 + cishu * d3 + cishu * d4 + cishu * d5 + cishu * d6)
						startnum[speed] = d6;//当前速度车辆号为1260-1510的车一次发多少辆发10次
					else if (i > d1 + cishu * d2 + cishu * d3 + cishu * d4 + cishu * d5 + cishu * d6 && i <= spd2crosscnt[cross])
						startnum[speed] = d7;//当前速度剩余车辆的发车数

					if (i >= m2 && i < m2 + startnum[speed])
					{
						/*if (i == d1 + 1
						|| i == d1 + cishu * d2 + 1
						|| i == d1 + cishu * d2 + cishu * d3 + 1
						|| i == d1 + cishu * d2 + cishu * d3 + cishu * d4 + 1
						|| i == d1 + cishu * d2 + cishu * d3 + cishu * d4 + cishu * d5 + 1
						|| i == d1 + cishu * d2 + cishu * d3 + cishu * d4 + cishu * d5 + cishu * d6 + 1
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

////////////////////////////////////////////速度2发车结束///////////////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	}
}