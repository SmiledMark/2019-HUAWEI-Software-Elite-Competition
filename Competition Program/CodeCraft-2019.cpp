#include "iostream"
#include<string>
#include<stdlib.h>
#include"struct.h"
//void ReadFile(FILE *fp1, FILE *fp2, FILE *fp3);
//MGraph* CreateMGraph(MGraph *G);
//void DFSTraverse(LGraphAdjListLink GL);
//LGraph* CreateALGraph(MGraph G, LGraph*  GL);
//void BFSTraverse(LGraphAdjListLink GL);
int* Dijkstra(int n, int src,  int c[MAXCROSS+1][MAXCROSS+1]);
int* searchPath(int *prev1, int src, int des);
//MGraph* MgraphDij(MGraph* GDij);
Car* ReadFile(FILE *fp1, FILE *fp2, FILE *fp3);
void write(int* lujing);
void LuJing(Car* car,FILE* fp4);
int main(int argc, char *argv[])
{	
	FILE *fp1, *fp2, *fp3,*fp4;
	Car *CARtemp;
	std::cout << "Begin" << std::endl;
	///*if(argc < 5){
	//	std::cout << "please input args: carPath, roadPath, crossPath, answerPath" << std::endl;
	//	exit(1);
	//}
	//
	//std::string carPath(argv[1]);//��argv[1]�����ݸ��Ƶ�carPath��
	//std::string roadPath(argv[2]);
	//std::string crossPath(argv[3]);
	//std::string answerPath(argv[4]);
	//
	//std::cout << "carPath is " << carPath << std::endl;
	//std::cout << "roadPath is " << roadPath << std::endl;
	//std::cout << "crossPath is " << crossPath << std::endl;
	//std::cout << "answerPath is " << answerPath << std::endl;*/
	////������Щ��Ϣ��Ҫ��ʱ�����ε���������vs�е��ԣ�������linux����ʱ��Ҫ��argv[]���뼸��·����Ϣ�Ų���ִ��exit(1)�������
	//// TODO:read input filebuf
	printf("nihao\n");
	fp1 = fopen("road.txt", "rb");
	fp2 = fopen("car.txt", "rb");
	fp3 = fopen("cross.txt", "rb");
	fp4 = fopen("answer.txt", "wb");
	if (fp1 == NULL || fp2 == NULL || fp3 == NULL || fp4 == NULL )
	{
		printf("not open this file\n");
		exit(0);
	}
	CARtemp=ReadFile(fp1, fp2, fp3);
	//MGraph G;
	//MGraph* G1 = CreateMGraph(&G);//CreateMGraph(G)��������Graph���͵�ָ��ͨ���������ָ�뼴�ɲ���������ڽӾ��󴴽��õ�ͼ
	//LGraph GL;
	////GL = (LGraph*)malloc(sizeof(LGraph));
	////GL = (LGraph*)malloc(sizeof(LGraph));����뷨�������￪�ٵ�ַ�ռ䲢���׵�ַ��Ϊʵ��ͨ��CreateALGraph�������ݹ�ȥ�������ǲ��Եģ���ַ�ǲ���ֱ����Ϊֵ���ݹ�ȥ�ģ���ᷢ�ֵ��Ǹ������ڲ�GL��ֵ�����Ǵ��ݹ�ȥ���Ǹ�ֵ           
	//LGraph* GL1 = CreateALGraph(*G1, &GL);//CreateALGraph(G,&GL)��������LGraph���͵�ָ��ͨ���������ָ�뼴�ɲ���������ڽ��������õ�ͼ
	/*printf("DFS:\n");
	DFSTraverse(GL1);
	printf("\nBFS:\n");
	BFSTraverse(GL1);*/
	// TODO:process
	LuJing(CARtemp,fp4);
	//lujing = searchPath(prev2, 1, 14);
	// TODO:write output file
	//write(prev2);
	return 0;
}