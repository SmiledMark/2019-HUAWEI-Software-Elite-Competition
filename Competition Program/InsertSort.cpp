#include <stdio.h>

void insertionSort(int *A)
{
	int i, j, k;
	//int B[4];
	////B = A;
	//for (k = 0; k < 4; k++)
	//{
	//	B[k] = A[k];
	//}
	//int B[10] = { 100, 2, 3, 4, 5, 6, 7, 109, 444, 789 };
	for (i = 0; i < 4; i++)
	{
		j = i;
		for (j; j > 0; j--)
		{
			if (A[j] < A[j - 1])
			{
				int temp;
				temp = A[j - 1];
				A[j - 1] = A[j];
				A[j] = temp;
			}
			else
			{
				break;
			}
		}
	}
}