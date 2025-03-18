#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>
#include <CommCtrl.h>

DWORD ThreadFunc1(LPVOID temp)
{
	HWND hProg = (HWND)temp;

	for (int i = 0; i < 1000; i++)
	{
		SendMessage(hProg, PBM_SETPOS, i, 0);
		Sleep(10);
	}
	return 0;
}

//�޽��� ó�� �Լ�
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hProg;
	static HANDLE hThread;
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		DWORD tid;
		hThread = CreateThread(0, 0,
			ThreadFunc1, (void*)hProg,
			CREATE_SUSPENDED,
			&tid);

		return 0;
	} case WM_RBUTTONDOWN:
	{
		static BOOL b = FALSE;
		b = !b;
		if (b)
		{
			ResumeThread(hThread);
		}
		else {
			SuspendThread(hThread);
		}
		return 0;
	}
	case WM_CREATE:
	{
		hProg = CreateWindow(PROGRESS_CLASS, TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | PBS_SMOOTH,
			10, 10, 500, 30, hwnd, (HMENU)1, 0, 0);
		SendMessage(hProg, PBM_SETRANGE32, 0, 1000);
		SendMessage(hProg, PBM_SETPOS, 0, 0);
		//SetTimer(hwnd, 1, 10, 0);
		return 0;
	}

	//DestroyWindow() �Լ� ���ο��� ȣ��
	//����ó������!!!!
	case WM_DESTROY:
	{
		//App Q�� WM_QUIT �޽��� �־��ش�.
		//KillTimer(hwnd, 1);
		CloseHandle(hThread);
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