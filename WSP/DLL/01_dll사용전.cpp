#include <stdio.h>
#include "mycal1.h"



int main()
{
	int num1, num2;

	printf("%.1f\n", mycal_add(10, 20));
	printf("%.1f\n", mycal_min(10, 20));
	printf("%.1f\n", mycal_mul(10, 20));
	printf("%.1f\n", mycal_div(10, 20));

	char dummy = getchar();

	return 0;
}