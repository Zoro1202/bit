//����� ���
/*
���� ���Ҷ� ���μ����� �޸𸮿� �ε�
���� ���� �� ���μ����� �޸𸮿��� ����

���ߴܰ� : .dll�� ������ ��
�����ܰ� : .dll�� ������ ��
*/
#include <stdio.h>
//#include "mycal.h"
//#pragma comment(lib, "Dll_mycal.lib")

#include <Windows.h>

typedef float(*DllFunc)(int, int);

int main()
{
	HMODULE hMod = LoadLibrary(TEXT("Dll_mycal.dll")); // dll�� �������
	if (hMod == 0)
	{
		printf("�ε� ����\n");
	}

	DllFunc mycal_add = (DllFunc)GetProcAddress(hMod, "mycal_add");
	DllFunc mycal_min = (DllFunc)GetProcAddress(hMod, "mycal_min");
	DllFunc mycal_mul = (DllFunc)GetProcAddress(hMod, "mycal_mul");
	DllFunc mycal_div = (DllFunc)GetProcAddress(hMod, "mycal_div");
	//DllFunc mycal_sample = (DllFunc)GetProcAddress(hMod, "mycal_sample");

	printf("%.1f\n", mycal_add(10, 20));
	printf("%.1f\n", mycal_min(10, 20));
	printf("%.1f\n", mycal_mul(10, 20));
	printf("%.1f\n", mycal_div(10, 20));

	//printf("%.1f\n", mycal_sample(10, 20));

	BOOL b = FreeLibrary(hMod);

	char dummy = getchar();

	return 0;
}