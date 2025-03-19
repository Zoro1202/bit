//������, �Һ���
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
		//����
		WaitForSingleObject(hMutex, INFINITE);

		q.push(value);
		TCHAR buf[20];
		wsprintf(buf, TEXT("���� : %d"), value);
		SetWindowText(hStatic2, buf);


		SendMessage(hPro, PBM_SETPOS, q.size(), 0);
		
		wsprintf(buf, TEXT("ť�� ���� : %ld"), q.size());
		SetWindowText(hStatic1, buf);

		ReleaseMutex(hMutex);
		LONG old;
		ReleaseSemaphore(hSemaphore, 1, &old); // �������� �ϳ� �ø���
		Sleep((rand() % 5 + 1) * 100); // 1ch ~ 5ch
	}
	return 0;
}


DWORD WINAPI ConsumeThread(LPVOID p)
{
	while (1)
	{
		//�Һ�
		WaitForSingleObject(hSemaphore, INFINITE); // Q�� �����Ͱ� ���� �� ��� 
		WaitForSingleObject(hMutex, INFINITE); // �����ڿ� Q�� ���� ���� ����

		int n = q.front();
		q.pop();

		TCHAR buf[20];
		wsprintf(buf, TEXT("�Һ� : %d"), n);
		SetWindowText(hStatic2, buf);

		SendMessage(hPro, PBM_SETPOS, q.size(), 0);

		wsprintf(buf, TEXT("ť�� ���� : %ld"), q.size());
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
	case WM_LBUTTONDOWN: // ���콺ĸ��
	{
		SetCapture(hdlg);
		return TRUE;
	}
	case WM_LBUTTONUP: // ���콺 ĸ�� ����
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
		else if (LOWORD(wParam == IDC_BUTTON1)) // ����
		{
			CreateProduce(hdlg);
		}
		else if (LOWORD(wParam == IDC_BUTTON2)) // �Һ�
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
