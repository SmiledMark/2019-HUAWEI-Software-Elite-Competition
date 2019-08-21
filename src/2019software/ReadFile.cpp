#include<stdio.h>
#include<stdlib.h>
#include"struct.h"
void insertionSort(int *A);

//道路变量设置
int c1, c2;//道路的起始路口号和终止路口号
int IDRoad[MAXCROSS+1][MAXCROSS+1];//每两个路口间的道路编号
int lenRoad[MAXCROSS + 1][MAXCROSS + 1];//两个路口间的道路长度
int spdRoad[MAXCROSS][MAXCROSS];//道路限速
int numpathRoad[MAXCROSS][MAXCROSS];//车道数目
int srcID[MAXCROSS];//某条道路的起始路口
int desID[MAXCROSS];//某条道路的终点路口
int douRoad[MAXCROSS];//道路是否是双向车道,1：双向,0：单向
//车辆变量设置//
int IDCar[MAXCROSS][MAXCROSS];//始发路口对应的车辆编号
int srcCar[MAXCAR];//车辆的始发路口
int desCar[MAXCAR];//车辆的目的路口
int spdCar[MAXCAR];//车辆的最高速度
int statmpCar[MAXCAR];//车辆的计划出发时间
int statmaCar[MAXCAR];//车辆的实际出发时间
int curtmCar[MAXCAR];//车辆当前行驶时间
int curIDRoadCar[MAXCAR];//车辆当前行驶的道路编号
int curIDpathCar[MAXCAR];//车辆当前车道编号
//路口变量设置//
int IDCross[MAXCROSS][2];//某个路口顺时针转的第一和第二个道路编号对应的路口号（某个路口的上方向和右方向道路编号便可唯一的确定这个路口）
int IDCross1[MAXCROSS];//用来给图输入路口信息
int IDroadCross[MAXCROSS][4];//路口四条道路的编号，注意顺时针存储的顺序

int roadid, road1en, roadspd, roadpathnum, roadsrc, roaddes, roaddou;//道路局部变量
int carid, carsrc, cardes, carmaxspd, cartime;//车辆局部变量
int crossid, crossroadid1, crossroadid2, crossroadid3, crossroadid4;//路口局部变量
int numLine1;//road.txt文件数据行的行数(比实际数据行数多1)
int numLine2;//car.txt文件数据行的行数(比实际数据行数多1)
int numLine3;//cross.txt文件数据行的行数(比实际数据行数多1)
int tempcar;//第一辆车的编号

Car* ReadFile(FILE *fp1, FILE *fp2, FILE *fp3)
{
	char str[100];
	int temp[4];
	char cur1;//当前读取的字符
	char cur2;
	char cur3;
	Car* CAR=NULL;
	CAR = (Car *)malloc(MAXCAR * sizeof(Car));
	int k = 0;
	numLine1 = 0;
	numLine2 = 0;
	numLine3 = 0;
	printf("The data of road is ...\n");
	//for (int i = 1; i <= 10; i++)
	//{
	//	CAR->cartimenum[i] = 0;//init the num on certain time
	//}
		
	// 将道路长度初始化为MAXINT
	for (int i = 0; i <= MAXCROSS; i++) {
		for (int j = 0; j <= MAXCROSS; j++) {
			lenRoad[i][j] = MAXINT;
		}
	}

	do {
		fgets(str, 99, fp1);//这两条语句的作用都是换行然后文件指针指向下一行的行首，不知道为什么明明看着输入文件行与行之间紧挨着
	//	fgets(str, 99, fp2);//但是调试时发现却要有两个换行符，又因为fscanf_s没有换行的作用所以在这里要有两个fgets函数换行两次
		cur1 = fgetc(fp1);
		fseek(fp1, -1L, 1);//由于fgetc函数读取了一个字符使得文件指针前移，故需要后移一个位置，这是下一行fscanf_s的要求
		fscanf(fp1, "(%d, %d, %d, %d, %d, %d, %d)", &roadid, &road1en, &roadspd, &roadpathnum, &roadsrc, &roaddes, &roaddou);
		
		//////对路径长度进行一定的更改，结合车道数，道路限速等///////
	   /////////////////////方案1///////////////////
		//////////结合车道数对路径长度进行一定的更改
		if (roadpathnum == 5)
		{
			road1en = road1en - 2;
		}
		else if (roadpathnum == 4)
		{
			road1en =road1en - 1;
		}
		else if (roadpathnum == 2)
		{
			road1en = road1en + 1;
		}
		else if (roadpathnum == 1)
		{
			road1en = road1en + 2;
		}
		else
		{
			road1en = road1en;
		}
	   ////////结合道路限速对路径长度进行一定的更改//////////
		if (roadspd == 8)
		{
			road1en = road1en - 1;
		}
		else if (roadspd==4)
		{
			road1en = road1en + 1;
		}
		else if (roadspd==6)
		{
			road1en = road1en;
		}
        ////////结合单双向到对路径长度进行更改//////////
		if (roaddou == 1)
		{
			road1en = road1en;
		}
		else if (roaddou == 0)
		{
			road1en = road1en + 1;
		}
		////////对路径长度进行一定的更改，结束///////////////


		////对路径长度进行一定的更改，结合车道数，道路限速等///////
		  ///////////////////方案2///////////////////
		////////结合车道数对路径长度进行一定的更改
		if (roadpathnum == 5)
		{
			road1en = road1en - 4;
		}
		else if (roadpathnum == 4)
		{
			road1en =road1en - 3;
		}
		else if (roadpathnum == 2)
		{
			road1en = road1en + 3;
		}
		else if (roadpathnum == 1)
		{
			road1en = road1en + 4;
		}
		else
		{
			road1en = road1en;
		}
		  //////结合道路限速对路径长度进行一定的更改//////////
		if (roadspd == 8)
		{
			road1en = road1en - 1;
		}
		else if (roadspd==4)
		{
			road1en = road1en + 1;
		}
		else if (roadspd==6)
		{
			road1en = road1en;
		}
		      //////结合单双向到对路径长度进行更改//////////
		if (roaddou == 1)
		{
			road1en = road1en;
		}
		else if (roaddou == 0)
		{
			road1en = road1en + 2;
		}
		//////对路径长度进行一定的更改，结束///////////////

		IDRoad[roadsrc][roaddes] = roadid;
		lenRoad[roadsrc][roaddes] = road1en;
		spdRoad[roadsrc][roaddes] = roadspd;
		numpathRoad[roadsrc][roaddes] = roadpathnum;
		srcID[roadid] = roadsrc;
		desID[roadid] = roaddes;
		douRoad[roadid] = roaddou;
///////////以下道路禁走////////////////
		lenRoad[46][54] = MAXINT;
		lenRoad[50][51] = MAXINT;
		lenRoad[13][21] = MAXINT;
		//lenRoad[46][54] = MAXINT;

///////////以上道路禁走//////////////////////////////
		if (roaddou == 1)
		{
			IDRoad[roaddes][roadsrc] = roadid;
			lenRoad[roaddes][roadsrc] = lenRoad[roadsrc][roaddes];
			spdRoad[roaddes][roadsrc] = spdRoad[roadsrc][roaddes];
			numpathRoad[roaddes][roadsrc] = numpathRoad[roadsrc][roaddes];
		}
		
		printf("%d,%d,%d,%d,%d,%d,%d\n", IDRoad[roadsrc][roaddes], lenRoad[roadsrc][roaddes], spdRoad[roadsrc][roaddes], numpathRoad[roadsrc][roaddes], srcID[roadid], desID[roadid], douRoad[roadid]);
		numLine1++;//虽然最后一组数据重复读取了一次但是对于给上述数组的赋值是没有影响的，只是最后一组相同的内容赋值了两次而已
	} while (cur1 != -1);
	//-1是根据调试得来的，当没有数据时cur的值为 - 1
	printf("The num of road is %d\n", --numLine1);//读出来的数据最后一组重复读取了一次,所以减1

	//第二个文件的输入格式有点奇怪，两行数据之间有两个换行符，所以这里用了两个fgets语句，这一点要注意//
	printf("The data of car is ...\n");
	do {
		fgets(str, 99, fp2);//这两条语句的作用都是换行然后文件指针指向下一行的行首，不知道为什么明明看着输入文件行与行之间紧挨着
	   // fgets(str, 99, fp2);//但是调试时发现却要有两个换行符，又因为fscanf_s没有换行的作用所以在这里要有两个fgets函数换行两次
		cur2 = fgetc(fp2);    //问题在文件格式问题，应该是你在文件格式转换时出现了错误，在win下两行是紧挨着但是在linux下中间确实空着一行
		fseek(fp2, -1L, 1);//由于fgetc函数读取了一个字符使得文件指针前移，故需要后移一个位置，这是下一行fscanf_s的要求
		fscanf(fp2, "(%d, %d, %d, %d, %d)", &carid, &carsrc, &cardes, &carmaxspd, &cartime);
		if (k == 0)
		{
			tempcar = carid;
			k++;
		}//tempcar是第一辆车的id
		CAR[carid - tempcar].carid = carid- tempcar;
		CAR[carid - tempcar].srcCross = carsrc;//车辆的起始id太大了，这样相减又是从零开始
		CAR[carid - tempcar].desCross = cardes;
		CAR[carid - tempcar].maxspeed = carmaxspd;
		CAR[carid - tempcar].plantime = cartime;
		//CAR->cartimeid[cartime][CAR->cartimenum[cartime]++]= carid - tempcar;
		//CAR->cartimeid[cartime][]
		/*IDCar[carsrc][cardes] = carid;
		srcCar[carid] = carsrc;
		desCar[carid] = cardes;
		spdCar[carid] = carmaxspd;
		statmpCar[carid] = cartime;*/
		printf("%d,%d,%d,%d,%d\n", CAR[carid - tempcar].carid, CAR[carid - tempcar].srcCross, CAR[carid - tempcar].desCross, CAR[carid - tempcar].maxspeed, CAR[carid - tempcar].plantime);
		
		numLine2++;
	} while (cur2 != -1);//读出来的数据最后一组重复读取了一次
	printf("The num of car is %d\n", --numLine2);
	//-1是根据调试得来的，当没有数据时cur的值为 - 1.
	/*for (int num = 0; num < CAR->cartimenum[10]; num++)
	{
		printf("%d\n", CAR->cartimeid[10][num]);
	}*/
	printf("The data of cross is ...\n");
	do {//-1是根据调试得来的，当没有数据时cur的值为-1
		fgets(str, 99, fp3);//这两条语句的作用都是换行然后文件指针指向下一行的行首，不知道为什么明明看着输入文件行与行之间紧挨着
		//fgets(str, 99, fp3);//但是调试时发现却要有两个换行符，又因为fscanf_s没有换行的作用所以在这里要有两个fgets函数换行两次
		cur3 = fgetc(fp3);
		fseek(fp3, -1L, 1);//由于fgetc函数读取了一个字符使得文件指针前移，故需要后移一个位置，这是下一行fscanf_s的要求
		fscanf(fp3, "(%d, %d, %d, %d, %d)", &crossid, &crossroadid1, &crossroadid2, &crossroadid3, &crossroadid4);
		IDCross1[numLine3] = crossid;
		IDCross[crossroadid1][crossroadid2] = crossid;
		temp[0] = crossroadid1;
		temp[1] = crossroadid2;
		temp[2] = crossroadid3;
		temp[3] = crossroadid4;
		insertionSort(temp);
		for (int i = 0; i < 4; i++)
		{
			IDroadCross[crossid][i] = temp[i];
		}
		printf("%d,%d,%d,%d,%d\n", IDCross[crossroadid1][crossroadid2], IDroadCross[crossid][0], IDroadCross[crossid][1], IDroadCross[crossid][2], IDroadCross[crossid][3]);
		numLine3++;
	} while (cur3 != -1);//-1是根据调试得来的，当没有数据时cur的值为-1
	// 读出来的数据最后一组重复读取了一次
	printf("The num of cross is %d\n", --numLine3);
	return CAR;
}
