//11_IconCursur.cpp
/*
���콺 �̺�Ʈ �߻�
1) WM_NCHITTEST �޽��� �߻�
	HITTEST Code�� ȹ�� - HTCAPTION, HTCLIENT, HTLEFT, HTRIGHT ���
2) WM_SETCURSOR �޽��� �߻�
	���� HITTEST Code�� ���� ���콺Ŀ�� ��� ����
3) WM_LBUTTONDOWN �� ���콺 Ŀ�� ����
*/
#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

#include "resource.h"

//�޽��� ó�� �Լ�
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HCURSOR h1 = LoadCursorFromFile(TEXT("C:\\Windows\\Cursors\\help_il.cur"));
	static RECT rc = { 100, 100, 200, 200 };
	switch (msg)
	{
	case WM_SETCURSOR:
	{
		int code = LOWORD(lParam);
		POINT pt; 
		GetCursorPos(&pt);
		ScreenToClient(hwnd, &pt);
		if (code == HTCLIENT && PtInRect(&rc, pt))
		{
			SetCursor(h1);
			return TRUE;
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	case WM_NCHITTEST:
	{
		LRESULT code = DefWindowProc(hwnd, msg, wParam, lParam);

		if (code == HTCLIENT && GetKeyState(VK_CONTROL) < 0)
		{
			code = HTCAPTION;
		}
		if (code == HTLEFT)
		{
			code = HTRIGHT;
		}
		return code;
	}
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);

		HICON icon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1));
		POINTS pt = MAKEPOINTS(lParam);
		DrawIcon(hdc, pt.x, pt.y, icon);

		ReleaseDC(hwnd, hdc);
		return 0;
	}
	case WM_PAINT:
	{
		HDC hdc = GetDC(hwnd);

		Rectangle(hdc, 100, 100, 200, 200);

		ReleaseDC(hwnd, hdc);
		return 0;
	}
	//������ �����Ǿ���, ȭ�鿡 �Ⱥ��δ�.
	//�ʱ�ȭ!!!!
	case WM_CREATE:
	{
		return 0;
	}

	//DestroyWindow() �Լ� ���ο��� ȣ��
	//����ó������!!!!
	case WM_DESTROY:
	{
		//App Q�� WM_QUIT �޽��� �־��ش�.
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
	//wnd.hIcon = LoadIcon(0, IDI_APPLICATION);
	wnd.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	//wnd.hCursor = LoadCursor(0, IDC_HAND);
	wnd.hCursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1));
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