#include <stdio.h>
#include "struct.h"
MGraph* MgraphDij(MGraph* GDij)
{
	//����ͼ�бߵ���Ϣ������ָ���ǵ�·���
	int i, j, k, m;
	//GDij->edgeNum = numLine1;//�ߵ������ͽ���������ʵ��ʵ�δ��ݹ����ȽϺ�
	//GDij->verNum = numLine3;
	for (i = 1; i <= MAXCROSS; i++) {
		for (j = 1; j <= MAXCROSS; j++) {
			GDij->roadlen1[i][j] = lenRoad[i][j];//ע���ʼʱlenRoad��ʼ��ΪMAXINT,Ȼ���ȥ��ȡ�ļ�.
		}
	}
	return GDij;


}