//08_����ȭ.cpp
#pragma comment (linker, "/subsystem:windows")
/*synchronization
1) ũ��Ƽ�� ����(Critical Section) : �Ӱ� ����(�ϳ��� ���μ����� �� �� �ִ� ����
-------------------------
[Ŀ��, os�� ����, ���μ��� �� ����ȭ ����]
2) mutex : ������ (�������� ���� �ִ� ���μ����� �� �� ����)
3) shemaphore : ���� �ڿ��� ������ �� �ִ� ���� ����
4) Event : (����) �ڰ� �ִ� ��� �����带 ����� ��
		   (�ڵ�) �������� ������ ����
*/
#include <Windows.h>
#include <tchar.h>

int x = 0;

CRITICAL_SECTION g_cs;

DWORD WINAPI ThreadFunc1(LPVOID param)
{
	HDC hdc = GetDC((HWND)param);

	for (int i = 0; i < 100; i++)
	{
		EnterCriticalSection(&g_cs);
		x = 100;
		TextOut(hdc, x, 100, TEXT("������"), 3);
		LeaveCriticalSection(&g_cs);
		Sleep(1);
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}
DWORD WINAPI ThreadFunc2(LPVOID param)
{
	HDC hdc = GetDC((HWND)param);

	for (int i = 0; i < 100; i++)
	{
		EnterCriticalSection(&g_cs);
		x = 200;
		TextOut(hdc, x, 200, TEXT("�����"), 3);
		LeaveCriticalSection(&g_cs);
		Sleep(1);
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}

//�޽��� ó�� �Լ�
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//static HWND hProg;
	static HANDLE hThread1;
	static HANDLE hThread2;
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		DWORD tid;// ������ ���̵� ���� �ʿ������
		hThread1 = CreateThread(0, 0,
			ThreadFunc1, (void*)hwnd,
			0,
			&tid);
		hThread2 = CreateThread(0, 0,
			ThreadFunc2, (void*)hwnd,
			0,
			&tid);


		return 0;
	} case WM_RBUTTONDOWN:
	{
		DWORD code;
		GetExitCodeThread(hThread1, &code);
		if (code == STILL_ACTIVE)
		{
			TerminateThread(hThread1, -1);
			CloseHandle(hThread1);
		}
		GetExitCodeThread(hThread2, &code);
		if (code == STILL_ACTIVE)
		{
			TerminateThread(hThread2, -1);
			CloseHandle(hThread2);
		}
	}
	case WM_CREATE:
	{
		InitializeCriticalSection(&g_cs);
		//SetTimer(hwnd, 1, 10, 0);
		return 0;
	}

	//DestroyWindow() �Լ� ���ο��� ȣ��
	//����ó������!!!!
	case WM_DESTROY:
	{
		//App Q�� WM_QUIT �޽��� �־��ش�.
		//KillTimer(hwnd, 1);
		CloseHandle(hThread1);
		CloseHandle(hThread2);
		DeleteCriticalSection(&g_cs);
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//���� �Լ�
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPTSTR cmdline, int showcmd)
{
	//1. ������ Ŭ���� ����
	WNDCLASSEX wnd;
	wnd.cbSize = sizeof(WNDCLASSEX);

	wnd.style = CS_HREDRAW | CS_VREDRAW;  //  0;
	wnd.hInstance = hInst;
	wnd.lpfnWndProc = WndProc;  // DefWindowProc;	//�̸� ���ǵǾ� �ִ� �޽��� ó�� ���ν���
	wnd.lpszClassName = TEXT("wb41");

	//�̸� ������� ���ҽ��� ����ϴ� ���
	wnd.hIcon = LoadIcon(0, IDI_APPLICATION);
	wnd.hCursor = LoadCursor(0, IDC_HAND);
	//BRUSH, PEN, FONT
	wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.lpszMenuName = 0;

	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hIconSm = 0;

	//2. ������ Ŭ���� ���
	RegisterClassEx(&wnd);

	//3. �����찴ü (����.. CreateXXX)
	HWND hwnd = CreateWindowEx(WS_EX_TOPMOST, TEXT("wb41"), TEXT("ù��° ������"),
		WS_OVERLAPPEDWINDOW,// &~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0,
		500, 500, //CW_USEDEFAULT, 0,
		0, 0, hInst, 0);

	//4. ������ ȭ�� ���
	ShowWindow(hwnd, SW_SHOW); //showcmd : WinMain�� ����������	


	//5. �޽��� ����
	MSG msg;
	//GetMessage : WM_QUIT�� �������� ���� FALSE ��ȯ
	while (GetMessage(&msg, 0, 0, 0))
	{
		DispatchMessage(&msg);
	}

	return 0;
}