#include <stdio.h>

void maopaosortup(int* a, int length, int* b)
{
	int i, j, t1, t;
	for (j = 0; j < length; j++)
	for (i = 0; i < length - 1 - j; i++)
	if (a[i] > a[i + 1])
	{
		t = a[i];
		a[i] = a[i + 1];
		a[i + 1] = t;


		t1 = b[i];
		b[i] = b[i + 1];
		b[i + 1] = t1;
	}
}
