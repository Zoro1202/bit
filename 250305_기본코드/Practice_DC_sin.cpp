//Practice_DC_sin.cpp
#pragma comment (linker, "/subsystem:windows")

#include <math.h>
#include <Windows.h>
#include <tchar.h>

#define NUM 5			// ���� ��� �ػ� resolution
#define TWOPI (2 * 3.14159) // 2 * PI

//�޽��� ó�� �Լ�
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	int i;
	PAINTSTRUCT ps;
	POINT apt[NUM];
	switch (msg)
	{
	case WM_SIZE:
	{
		cxClient = LOWORD(lParam); // x���� �����´�. ���� 2����Ʈ
		cyClient = HIWORD(lParam); // y���� �����´�. ���� 2����Ʈ
		return 0;
	}
	case WM_PAINT:
	{
		HDC hdc = BeginPaint(hwnd, &ps);
		MoveToEx(hdc, 0, cyClient / 2, NULL); 
		LineTo(hdc, cxClient, cyClient / 2);

		for (i = 0; i < NUM; i++)
		{
			apt[i].x = i * cxClient / (NUM - 1);	// NUM => ���� ����
			apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / (NUM - 1)))); // sin(0)->sin(Pi/2)->sin(Pi)->sin(Pi*3/4)->sin(2*Pi)
		}																 // 0       1          0        -1            0
		Polyline(hdc, apt, NUM);
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
		WS_OVERLAPPEDWINDOW,// &~ WS_MAXIMIZEBOX &~ WS_MINIMIZEBOX,
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