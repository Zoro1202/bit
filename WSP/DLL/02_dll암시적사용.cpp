//dll�Ͻ������
/*
�������� ���� �� dll�� �ڵ����� ���������� �޸𸮿� load
�������� ���� �� dll�� �ڵ����� ���������� �޸𸮿� unload

���ߴܰ� : .h, .dll, .lib �� �� ���� �ΰ� �����ؾ� ��
�����ܰ� : .dll ���ϸ� �������ϰ� ���� ������ ��
*/
#include <stdio.h>
#include "mycal.h"

#pragma comment(lib, "Dll_mycal.lib")

int main()
{
	printf("%.1f\n", mycal_add(10, 20));
	printf("%.1f\n", mycal_min(10, 20));
	printf("%.1f\n", mycal_mul(10, 20));
	printf("%.1f\n", mycal_div(10, 20));

	printf("%.1f\n", mycal_sample(10, 20));

	char dummy = getchar();

	return 0;
}