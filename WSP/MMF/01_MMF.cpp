#include <stdio.h>

#include <Windows.h>

#include <tchar.h>


int main()
{
	HANDLE FILE = CreateFile(TEXT("a.txt"), 
		GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	HANDLE hMap = CreateFileMapping(FILE, 0,
		PAGE_READWRITE,
		0, 100,
		TEXT("map"));

	char* p = (char*)MapViewOfFileEx(hMap, FILE_MAP_WRITE,
		0, 0, 0,
		(void*)0x10000000);
	if (p == NULL)
	{
		printf("error");
	}
	else
	{
		printf("매핑된 주소 : %p\n", p);
		strcpy_s(p, sizeof(char) * 6, "hello");
		p[50] = 'a';
		p[100] = 'p';
	}
	UnmapViewOfFile(p);
	CloseHandle(hMap);
	CloseHandle(FILE);

	return 0;
}