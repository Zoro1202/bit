//start.cpp
#include "std.h"

// ������ �⺻ ũ��
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
// ������ Ŭ������, Ÿ��Ʋ
#define CLASS_NAME TEXT("wb41")
#define WINDOW_NAME TEXT("�����������α׷�")

//�޽��� ó�� �Լ�
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:return OnCommand(hwnd, wParam, lParam);
	case WM_PAINT: return OnPaint(hwnd, wParam, lParam);
	case WM_CREATE: return OnCreate(hwnd, wParam, lParam);
	case WM_DESTROY: return OnDestroy(hwnd, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//���� �Լ�
int WINAPI _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hprevInstance, _In_ LPTSTR cmdline, _In_ int showcmd)
{
	//1. ������ Ŭ���� ����
	WNDCLASSEX wnd;
	wnd.cbSize = sizeof(WNDCLASSEX);

	wnd.style = CS_HREDRAW | CS_VREDRAW;  //  0;
	wnd.hInstance = hInst;
	wnd.lpfnWndProc = WndProc;  // DefWindowProc;	//�̸� ���ǵǾ� �ִ� �޽��� ó�� ���ν���
	wnd.lpszClassName = CLASS_NAME;

	//�̸� ������� ���ҽ��� ����ϴ� ���
	wnd.hIcon = LoadIcon(0, IDI_APPLICATION);
	wnd.hCursor = LoadCursor(0, IDC_ARROW);
	//BRUSH, PEN, FONT
	wnd.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wnd.lpszMenuName = 0;

	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hIconSm = 0;

	//2. ������ Ŭ���� ���
	RegisterClassEx(&wnd);

	//3. �����찴ü (����.. CreateXXX)
	HWND hwnd = CreateWindowEx(WS_EX_TOPMOST, CLASS_NAME, WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,// &~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0,
		WINDOW_WIDTH, WINDOW_HEIGHT, //CW_USEDEFAULT, 0,
		0, 0, hInst, 0);

	//4. ������ ȭ�� ���
	ShowWindow(hwnd, SW_SHOW); //showcmd : WinMain�� ����������	


	//5. �޽��� ����
	MSG msg;
	//GetMessage : WM_QUIT�� �������� ���� FALSE ��ȯ
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}