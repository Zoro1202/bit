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
	cout << "Event�� ��ٸ�" << endl;
	WaitForSingleObject(hEvent, INFINITE);
	cout << "Event�� ȹ��" << endl;


	cout << "Event�� ��ٸ�" << endl;
	WaitForSingleObject(hEvent, INFINITE);
	cout << "Event�� ȹ��" << endl;

	CloseHandle(hEvent);
}