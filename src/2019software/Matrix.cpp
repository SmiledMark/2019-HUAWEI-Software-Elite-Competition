#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/////////Int�;���ռ䶯̬����//////////////////////
int **matrixINT(int row, int column)
{
	int **m;
	int i = 0;
	m = (int **)malloc(row*sizeof(int*));
	if (m == NULL)
	{
		printf("������䶯̬�ڴ�ռ�ʧ��");
		return 0;
	}
	for (i = 0; i < row; i++)
		m[i] = (int *)malloc(column*sizeof(int));
	return m;
}