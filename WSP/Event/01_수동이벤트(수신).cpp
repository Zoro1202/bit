#pragma comment (linker, "/subsystem:console")
#include <iostream>
#include <Windows.h>
#include <tchar.h>
using namespace std;
int main()
{
	HANDLE hEvent = CreateEvent(0,
		TRUE,
		FALSE,
		_T("e"));
	cout << "Event¸¦ ±â´Ù¸²" << endl;
	WaitForSingleObject(hEvent, INFINITE);
	cout << "Event¸¦ È¹µæ" << endl;


	cout << "Event¸¦ ±â´Ù¸²" << endl;
	WaitForSingleObject(hEvent, INFINITE);
	cout << "Event¸¦ È¹µæ" << endl;

	CloseHandle(hEvent);
}