#include<stdio.h>
#include<stdlib.h>
#include"struct.h"
void insertionSort(int *A);

//��·��������
int c1, c2;//��·����ʼ·�ںź���ֹ·�ں�
int IDRoad[MAXCROSS+1][MAXCROSS+1];//ÿ����·�ڼ�ĵ�·���
int lenRoad[MAXCROSS + 1][MAXCROSS + 1];//����·�ڼ�ĵ�·����
int spdRoad[MAXCROSS][MAXCROSS];//��·����
int numpathRoad[MAXCROSS][MAXCROSS];//������Ŀ
int srcID[MAXCROSS];//ĳ����·����ʼ·��
int desID[MAXCROSS];//ĳ����·���յ�·��
int douRoad[MAXCROSS];//��·�Ƿ���˫�򳵵�,1��˫��,0������
//������������//
int IDCar[MAXCROSS][MAXCROSS];//ʼ��·�ڶ�Ӧ�ĳ������
int srcCar[MAXCAR];//������ʼ��·��
int desCar[MAXCAR];//������Ŀ��·��
int spdCar[MAXCAR];//����������ٶ�
int statmpCar[MAXCAR];//�����ļƻ�����ʱ��
int statmaCar[MAXCAR];//������ʵ�ʳ���ʱ��
int curtmCar[MAXCAR];//������ǰ��ʻʱ��
int curIDRoadCar[MAXCAR];//������ǰ��ʻ�ĵ�·���
int curIDpathCar[MAXCAR];//������ǰ�������
//·�ڱ�������//
int IDCross[MAXCROSS][2];//ĳ��·��˳ʱ��ת�ĵ�һ�͵ڶ�����·��Ŷ�Ӧ��·�ںţ�ĳ��·�ڵ��Ϸ�����ҷ����·��ű��Ψһ��ȷ�����·�ڣ�
int IDCross1[MAXCROSS];//������ͼ����·����Ϣ
int IDroadCross[MAXCROSS][4];//·��������·�ı�ţ�ע��˳ʱ��洢��˳��

int roadid, road1en, roadspd, roadpathnum, roadsrc, roaddes, roaddou;//��·�ֲ�����
int carid, carsrc, cardes, carmaxspd, cartime;//�����ֲ�����
int crossid, crossroadid1, crossroadid2, crossroadid3, crossroadid4;//·�ھֲ�����
int numLine1;//road.txt�ļ������е�����(��ʵ������������1)
int numLine2;//car.txt�ļ������е�����(��ʵ������������1)
int numLine3;//cross.txt�ļ������е�����(��ʵ������������1)
int tempcar;//��һ�����ı��

Car* ReadFile(FILE *fp1, FILE *fp2, FILE *fp3)
{
	char str[100];
	int temp[4];
	char cur1;//��ǰ��ȡ���ַ�
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
		
	// ����·���ȳ�ʼ��ΪMAXINT
	for (int i = 0; i <= MAXCROSS; i++) {
		for (int j = 0; j <= MAXCROSS; j++) {
			lenRoad[i][j] = MAXINT;
		}
	}

	do {
		fgets(str, 99, fp1);//�������������ö��ǻ���Ȼ���ļ�ָ��ָ����һ�е����ף���֪��Ϊʲô�������������ļ�������֮�������
	//	fgets(str, 99, fp2);//���ǵ���ʱ����ȴҪ���������з�������Ϊfscanf_sû�л��е���������������Ҫ������fgets������������
		cur1 = fgetc(fp1);
		fseek(fp1, -1L, 1);//����fgetc������ȡ��һ���ַ�ʹ���ļ�ָ��ǰ�ƣ�����Ҫ����һ��λ�ã�������һ��fscanf_s��Ҫ��
		fscanf(fp1, "(%d, %d, %d, %d, %d, %d, %d)", &roadid, &road1en, &roadspd, &roadpathnum, &roadsrc, &roaddes, &roaddou);
		
		//////��·�����Ƚ���һ���ĸ��ģ���ϳ���������·���ٵ�///////
	   /////////////////////����1///////////////////
		//////////��ϳ�������·�����Ƚ���һ���ĸ���
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
	   ////////��ϵ�·���ٶ�·�����Ƚ���һ���ĸ���//////////
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
        ////////��ϵ�˫�򵽶�·�����Ƚ��и���//////////
		if (roaddou == 1)
		{
			road1en = road1en;
		}
		else if (roaddou == 0)
		{
			road1en = road1en + 1;
		}
		////////��·�����Ƚ���һ���ĸ��ģ�����///////////////


		////��·�����Ƚ���һ���ĸ��ģ���ϳ���������·���ٵ�///////
		  ///////////////////����2///////////////////
		////////��ϳ�������·�����Ƚ���һ���ĸ���
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
		  //////��ϵ�·���ٶ�·�����Ƚ���һ���ĸ���//////////
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
		      //////��ϵ�˫�򵽶�·�����Ƚ��и���//////////
		if (roaddou == 1)
		{
			road1en = road1en;
		}
		else if (roaddou == 0)
		{
			road1en = road1en + 2;
		}
		//////��·�����Ƚ���һ���ĸ��ģ�����///////////////

		IDRoad[roadsrc][roaddes] = roadid;
		lenRoad[roadsrc][roaddes] = road1en;
		spdRoad[roadsrc][roaddes] = roadspd;
		numpathRoad[roadsrc][roaddes] = roadpathnum;
		srcID[roadid] = roadsrc;
		desID[roadid] = roaddes;
		douRoad[roadid] = roaddou;
///////////���µ�·����////////////////
		lenRoad[46][54] = MAXINT;
		lenRoad[50][51] = MAXINT;
		lenRoad[13][21] = MAXINT;
		//lenRoad[46][54] = MAXINT;

///////////���ϵ�·����//////////////////////////////
		if (roaddou == 1)
		{
			IDRoad[roaddes][roadsrc] = roadid;
			lenRoad[roaddes][roadsrc] = lenRoad[roadsrc][roaddes];
			spdRoad[roaddes][roadsrc] = spdRoad[roadsrc][roaddes];
			numpathRoad[roaddes][roadsrc] = numpathRoad[roadsrc][roaddes];
		}
		
		printf("%d,%d,%d,%d,%d,%d,%d\n", IDRoad[roadsrc][roaddes], lenRoad[roadsrc][roaddes], spdRoad[roadsrc][roaddes], numpathRoad[roadsrc][roaddes], srcID[roadid], desID[roadid], douRoad[roadid]);
		numLine1++;//��Ȼ���һ�������ظ���ȡ��һ�ε��Ƕ��ڸ���������ĸ�ֵ��û��Ӱ��ģ�ֻ�����һ����ͬ�����ݸ�ֵ�����ζ���
	} while (cur1 != -1);
	//-1�Ǹ��ݵ��Ե����ģ���û������ʱcur��ֵΪ - 1
	printf("The num of road is %d\n", --numLine1);//���������������һ���ظ���ȡ��һ��,���Լ�1

	//�ڶ����ļ��������ʽ�е���֣���������֮�����������з�������������������fgets��䣬��һ��Ҫע��//
	printf("The data of car is ...\n");
	do {
		fgets(str, 99, fp2);//�������������ö��ǻ���Ȼ���ļ�ָ��ָ����һ�е����ף���֪��Ϊʲô�������������ļ�������֮�������
	   // fgets(str, 99, fp2);//���ǵ���ʱ����ȴҪ���������з�������Ϊfscanf_sû�л��е���������������Ҫ������fgets������������
		cur2 = fgetc(fp2);    //�������ļ���ʽ���⣬Ӧ���������ļ���ʽת��ʱ�����˴�����win�������ǽ����ŵ�����linux���м�ȷʵ����һ��
		fseek(fp2, -1L, 1);//����fgetc������ȡ��һ���ַ�ʹ���ļ�ָ��ǰ�ƣ�����Ҫ����һ��λ�ã�������һ��fscanf_s��Ҫ��
		fscanf(fp2, "(%d, %d, %d, %d, %d)", &carid, &carsrc, &cardes, &carmaxspd, &cartime);
		if (k == 0)
		{
			tempcar = carid;
			k++;
		}//tempcar�ǵ�һ������id
		CAR[carid - tempcar].carid = carid- tempcar;
		CAR[carid - tempcar].srcCross = carsrc;//��������ʼid̫���ˣ�����������Ǵ��㿪ʼ
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
	} while (cur2 != -1);//���������������һ���ظ���ȡ��һ��
	printf("The num of car is %d\n", --numLine2);
	//-1�Ǹ��ݵ��Ե����ģ���û������ʱcur��ֵΪ - 1.
	/*for (int num = 0; num < CAR->cartimenum[10]; num++)
	{
		printf("%d\n", CAR->cartimeid[10][num]);
	}*/
	printf("The data of cross is ...\n");
	do {//-1�Ǹ��ݵ��Ե����ģ���û������ʱcur��ֵΪ-1
		fgets(str, 99, fp3);//�������������ö��ǻ���Ȼ���ļ�ָ��ָ����һ�е����ף���֪��Ϊʲô�������������ļ�������֮�������
		//fgets(str, 99, fp3);//���ǵ���ʱ����ȴҪ���������з�������Ϊfscanf_sû�л��е���������������Ҫ������fgets������������
		cur3 = fgetc(fp3);
		fseek(fp3, -1L, 1);//����fgetc������ȡ��һ���ַ�ʹ���ļ�ָ��ǰ�ƣ�����Ҫ����һ��λ�ã�������һ��fscanf_s��Ҫ��
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
	} while (cur3 != -1);//-1�Ǹ��ݵ��Ե����ģ���û������ʱcur��ֵΪ-1
	// ���������������һ���ظ���ȡ��һ��
	printf("The num of cross is %d\n", --numLine3);
	return CAR;
}
