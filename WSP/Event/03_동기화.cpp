//생산자, 소비자
#pragma once
#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>
#include <CommCtrl.h>
#include "resource.h"
#include <queue>
using std::queue;

HWND hPro, hStatic1, hStatic2;

HANDLE hCons, hProd;

HANDLE hMutex, hSemaphore;

queue<int>q;

DWORD WINAPI ProduceThread(LPVOID p)
{
	static int value = 0;
	while (1)
	{
		++value;
		//생산
		WaitForSingleObject(hMutex, INFINITE);

		q.push(value);
		TCHAR buf[20];
		wsprintf(buf, TEXT("생산 : %d"), value);
		SetWindowText(hStatic2, buf);


		SendMessage(hPro, PBM_SETPOS, q.size(), 0);
		
		wsprintf(buf, TEXT("큐의 개수 : %ld"), q.size());
		SetWindowText(hStatic1, buf);

		ReleaseMutex(hMutex);
		LONG old;
		ReleaseSemaphore(hSemaphore, 1, &old); // 세마포어 하나 늘리기
		Sleep((rand() % 5 + 1) * 100); // 1ch ~ 5ch
	}
	return 0;
}


DWORD WINAPI ConsumeThread(LPVOID p)
{
	while (1)
	{
		//소비
		WaitForSingleObject(hSemaphore, INFINITE); // Q에 데이터가 있을 때 통과 
		WaitForSingleObject(hMutex, INFINITE); // 공유자원 Q에 대한 접근 제어

		int n = q.front();
		q.pop();

		TCHAR buf[20];
		wsprintf(buf, TEXT("소비 : %d"), n);
		SetWindowText(hStatic2, buf);

		SendMessage(hPro, PBM_SETPOS, q.size(), 0);

		wsprintf(buf, TEXT("큐의 개수 : %ld"), q.size());
		SetWindowText(hStatic1, buf);

		ReleaseMutex(hMutex);
		Sleep((rand() % 5 + 1) * 100); // 1ch ~ 5ch

	}

	return 0;
}

void CreateConsume(HWND hdlg)
{
	hCons = CreateThread(0, 0, ConsumeThread, 0, 0, 0);
}
void CreateProduce(HWND hdlg)
{
	hProd = CreateThread(0, 0, ProduceThread, 0, 0, 0);
}

INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		hSemaphore = CreateSemaphore(0, 0, 100, TEXT("Q_RESOURCE_COUNT"));
		hMutex = CreateMutex(0, 0, TEXT("Q_ACCESS_GUARD")); //non_signal
		hStatic1 = GetDlgItem(hdlg, IDC_STATIC1);
		hStatic2 = GetDlgItem(hdlg, IDC_STATIC2);
		hPro = GetDlgItem(hdlg, IDC_PROGRESS1);
		//SendMessage(hPro, PBM_SETRANGE, 0, 100);

		return TRUE;
	}
	case WM_LBUTTONDOWN: // 마우스캡쳐
	{
		SetCapture(hdlg);
		return TRUE;
	}
	case WM_LBUTTONUP: // 마우스 캡쳐 해제
	{
		POINT pt;
		GetCursorPos(&pt);
		ReleaseCapture();
		return TRUE;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, IDCANCEL);
			return TRUE;
		}
		else if (LOWORD(wParam == IDC_BUTTON1)) // 생산
		{
			CreateProduce(hdlg);
		}
		else if (LOWORD(wParam == IDC_BUTTON2)) // 소비
		{
			CreateConsume(hdlg);
		}
	}
	}
	return FALSE;
}

int WINAPI _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hprevInstance, _In_ LPTSTR cmdline, _In_ int showcmd)
{
	INT_PTR ret = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, DlgProc);

	return 0;
}
