#pragma comment (linker, "/subsystem:console")
#include <iostream>
#include <Windows.h>
#include <tchar.h>
using namespace std;

HANDLE hEvent1, hEvent2;

BOOL bContinue = TRUE;
int gx, sum;

DWORD WINAPI ServerThread(LPVOID p)
{
	cout << "���� ������ ����" << endl;
	while (bContinue)
	{
		WaitForSingleObject(hEvent1, INFINITE);
		sum = 0;
		for (int i = 1; i <= gx; i++)
		{
			sum += i;
		}
		SetEvent(hEvent2);
	}
	cout << "���� ������ ����" << endl;
	return 0;
}

int main()
{
	hEvent1 = CreateEvent(0,
		FALSE, // FALSE - �ڵ�, TRUE - ����
		FALSE,
		_T("e")); // "�� �ض�" �̺�Ʈ

	hEvent2 = CreateEvent(0, 0, 0, _T("e2")); // "�ñ� ���� �����ߴ�" �̺�Ʈ

	HANDLE h = CreateThread(0, 0, ServerThread, 0, 0, 0);
	Sleep(1);
	while (1)
	{
		cout << ">> "; cin >> gx;
		if (gx == -1) { break; }
		SetEvent(hEvent1);
		WaitForSingleObject(hEvent2, INFINITE);
		cout << "��� : " << sum << endl;
	}
	bContinue = FALSE;
	SetEvent(hEvent1);
	WaitForSingleObject(h, INFINITE);

	CloseHandle(h);
	CloseHandle(hEvent1);
	CloseHandle(hEvent2);
}