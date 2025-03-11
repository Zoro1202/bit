//12_�޴�.cpp
/*
1. ���� �޴�
	-�޴��� ������ Ŭ�� �� -> �̺�Ʈ ���� : WM_COMMAND, � �������� Ŭ���Ǿ�����?(ID)
	�޴��ٿ� �ִ� �޴� �ε��� 0���� ���� ���ʺ���
2. �ý��� �޴�
	�ý��� �������� ��Ŭ���ϸ� �ߴ� �޴�
3. ���ؽ�Ʈ �޴�
	Ŭ���̾�Ʈ �޴����� ��Ŭ���ϸ� �ߴ� �޴�
*/

#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

#include "resource.h"

//�޽��� ó�� �Լ�
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static COLORREF color = RGB(255, 0, 0);
	static int type = 1;
	switch (msg)
	{
	case WM_CONTEXTMENU://case WM_RBUTTONUP:
	{
		HMENU hmenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));

		HMENU hsub = GetSubMenu(hmenu, 1);
		 
		POINT pt = {LOWORD(lParam), HIWORD(lParam)};

		//ClientToScreen(hwnd, &pt);

		TrackPopupMenu(hsub, TPM_LEFTBUTTON, pt.x, pt.y, 0, hwnd, 0);

		return 0;
	}
	case WM_INITMENUPOPUP:
	{
		//HMENU hmenu = GetMenu(hwnd);
		HMENU hmenu = (HMENU)wParam;
		//EnableMenuItem(hmenu, ID_CLOSE, TRUE);
		EnableMenuItem(hmenu, ID_RCOLOR, color == RGB(255, 0, 0));
		EnableMenuItem(hmenu, ID_GCOLOR, color == RGB(0, 255, 0));
		EnableMenuItem(hmenu, ID_BCOLOR, color == RGB(0, 0, 255));

		CheckMenuItem(hmenu, ID_RECT, type == 1 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hmenu, ID_ELLI, type == 2 ? MF_CHECKED : MF_UNCHECKED);
		return 0;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_CLOSE:
		{
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			return 0;
		}
		case ID_RCOLOR: color = RGB(255, 0, 0); break;
		case ID_GCOLOR: color = RGB(0, 255, 0); break;
		case ID_BCOLOR: color = RGB(0, 0, 255); break;
		case ID_RECT: type = 1; break;
		case ID_ELLI: type = 2; break;
		case ID_INFO: MessageBox(hwnd, TEXT("����"), TEXT("���α׷�����"), MB_OK);
		}
		InvalidateRect(hwnd, 0, TRUE);
		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		HBRUSH hbr = CreateSolidBrush(color);
		HBRUSH old = (HBRUSH)SelectObject(hdc, hbr);

		if (type == 1) Rectangle(hdc, 100, 100, 200, 200);
		else if (type == 2) Ellipse(hdc, 100, 100, 200, 200);

		DeleteObject(SelectObject(hdc, old));

		EndPaint(hwnd, &ps);
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
	wnd.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

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
