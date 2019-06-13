#include<stdio.h>
#include<stdlib.h>
#include "struct.h"


int* Dijdis(int n, int src,  int c[MAXCROSS+1][MAXCROSS+1])
{
	int* dist=NULL; //the distance between current cross and source cross
	dist = (int*)malloc((MAXCROSS + 1)*sizeof(int));
	int* prev1;     // record the previous cross of current cross
	prev1 = (int*)malloc((MAXCROSS + 1)*sizeof(int));//��Ȼһ��·����prev1����ֻ�м���Ԫ�ص���prev1���±귶Χ��1-MAXCROSS�����Է���Ŀռ������ô��
	bool s[MAXCROSS + 1];    // �ж��Ƿ��Ѵ���õ㵽S������
	for (int i = 1; i <= n; ++i)//����Ӧ�ü�36
	{
		dist[i] = c[src][i];
		s[i] = 0;     // ��ʼ��δ�ù��õ�
		if (dist[i] == MAXINT)//��ʼʱ�����е�c[i][j]��ʼ��Ϊmaxint
			prev1[i] = -1;//Ҳ������ʱû��ǰ��
		else
			prev1[i] = src;//�Ƚ���Դ�������ڵ��ǰ����ΪԴ�㣬ע��dist����ʱ�п��ܻ�仯ǰ���ڵ�
	}
	dist[src] = 0;
	s[src] = 1;
	// ���ν�δ����S���ϵĽ���У�ȡdist[]��Сֵ�Ľ�㣬���뼯��S��
	// һ��S����������V�ж��㣬dist�ͼ�¼�˴�Դ�㵽������������֮������·������
	// ע���Ǵӵڶ����ڵ㿪ʼ����һ��ΪԴ��
	//ÿ����һ�������forѭ��������һ���ڵ��Ϊ��֪�ļ��缯��S������Դ���Ѿ��ڼ���S��������i��1��ʼֻ����·������1��ѭ������
	for (int i = 1; i < n; ++i)
	{
		int tmp = MAXINT;
		int u = src;//����ĸ�ֵ�о�û��ʲôʵ������
		// �ҳ���ǰδʹ�õĵ�j��dist[j]��Сֵ
		for (int j = 1; j <= n; ++j)
		if ((!s[j]) && dist[j] < tmp)
		{
			u = j;              // u���浱ǰ�ڽӵ��о�����С�ĵ�ĺ���
			tmp = dist[j];
		}
		s[u] = 1;    //u��Ϊ��֪u���Ѵ���S������

		// ����dist������Ҳһ��Ҫдһд������δ֪�Ľڵ㶼�����dist[u] + c[u][j]��dist[j]�ıȽϣ���Ȼֻ����u�����Ĳ��п���newdist<dist[j]
		for (int j = 1; j <= n; ++j)//����u������c[u][j]=MAXINT,��ô��������newdist<dist[j],�������newdist < dist[j]����ôj��ǰ���ڵ��Ϊ
		if ((!s[j]) && c[u][j] < MAXINT)//u,���Ҹ���dist[j]��ֵΪdist[u] + c[u][j]
		{
			int newdist = dist[u] + c[u][j];
			if (newdist < dist[j])
			{
				dist[j] = newdist;
				prev1[j] = u;
			}
		}
	}
	return dist;
}