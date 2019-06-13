#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/////////Int型矩阵空间动态分配//////////////////////
int **matrixINT(int row, int column)
{
	int **m;
	int i = 0;
	m = (int **)malloc(row*sizeof(int*));
	if (m == NULL)
	{
		printf("矩阵分配动态内存空间失败");
		return 0;
	}
	for (i = 0; i < row; i++)
		m[i] = (int *)malloc(column*sizeof(int));
	return m;
}