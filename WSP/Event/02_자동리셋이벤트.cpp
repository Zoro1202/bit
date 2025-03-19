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
	cout << "연산 스레드 시작" << endl;
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
	cout << "연산 스레드 종료" << endl;
	return 0;
}

int main()
{
	hEvent1 = CreateEvent(0,
		FALSE, // FALSE - 자동, TRUE - 수동
		FALSE,
		_T("e")); // "일 해라" 이벤트

	hEvent2 = CreateEvent(0, 0, 0, _T("e2")); // "맡긴 일을 종료했다" 이벤트

	HANDLE h = CreateThread(0, 0, ServerThread, 0, 0, 0);
	Sleep(1);
	while (1)
	{
		cout << ">> "; cin >> gx;
		if (gx == -1) { break; }
		SetEvent(hEvent1);
		WaitForSingleObject(hEvent2, INFINITE);
		cout << "결과 : " << sum << endl;
	}
	bContinue = FALSE;
	SetEvent(hEvent1);
	WaitForSingleObject(h, INFINITE);

	CloseHandle(h);
	CloseHandle(hEvent1);
	CloseHandle(hEvent2);
}