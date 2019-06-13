#include<stdio.h>
#include<stdlib.h>
#include"struct.h"

void write(int carid,int cartime,int *lujing,FILE* fp4)
{
	int tot = 1;
	while (lujing[tot] != -1)
		tot++;
	fprintf(fp4, "(");
	fprintf(fp4, "%d,%d,", carid,cartime);
	for (int i = tot-1; i >= 2; --i)
		if (i != 2) {
			//cout << lujing[i] << " -> ";
			fprintf(fp4, "%d,",IDRoad[lujing[i]][lujing[i-1]]);
		}
		else
			//cout << lujing[i] << endl;
		{
			fprintf(fp4, "%d)", IDRoad[lujing[i]][lujing[i-1]]);
			fprintf(fp4, "\r");
			fputs("\n", fp4);//这两句的作用是换行
		}
        free(lujing);
}

