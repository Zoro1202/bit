#include <stdio.h>
#include <Windows.h>
#include <process.h>

unsigned int _stdcall foo(void* p)
{
	printf("begin thread");
	Sleep(1000);
	printf("end thread");

	return 0;
}

int main()
{
	unsigned long long ret = _beginthreadex(0, 0, foo, 0, 0, 0);
	
	WaitForSingleObject((HANDLE)ret, INFINITE);

	CloseHandle((HANDLE)ret);


	return 0;
}