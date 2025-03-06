//09_��������Ǹ޽���.cpp
#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

#define WM_MYMESSAGE1 WM_USER+101 // wParam : x��ǥ , lParam : y��ǥ
#define WM_MYMESSAGE2 WM_USER+102 // wParam : ���� , lParam : X

//�޽��� ó�� �Լ�
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MYMESSAGE1:
	{
		HDC hdc = GetDC(hwnd);

		Ellipse(hdc, wParam, lParam, wParam + 50, lParam + 50);

		ReleaseDC(hwnd, hdc);
		return 0;
	}
	case WM_MYMESSAGE2:
	{
		HDC hdc = GetDC(hwnd);

		TCHAR buf[50];
		wsprintf(buf, TEXT("���Ź���:%c"), wParam);
		TextOut(hdc, 10, 10, buf, 6);
		ReleaseDC(hwnd, hdc);

		return 0; 
	}
	case WM_KEYDOWN:
	{
		SendMessage(hwnd, WM_MYMESSAGE2, wParam, 0);
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);

		SendMessage(hwnd, WM_MYMESSAGE1, pt.x, pt.y);
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