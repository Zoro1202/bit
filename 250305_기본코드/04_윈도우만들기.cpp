//04_�����츸���.cpp

#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPTSTR cmdline, int showcmd)
{
	// 1. ������ Ŭ���� ����
	WNDCLASSEX wnd;
	wnd.cbSize			= sizeof(WNDCLASSEX);
	wnd.style			= CS_HREDRAW | CS_VREDRAW; // 0;
	wnd.lpfnWndProc		= DefWindowProc; // �̸� ���ǵǾ� �ִ� �޽��� ó�� ���ν���
	wnd.cbClsExtra		= 0;
	wnd.cbWndExtra		= 0;
	wnd.hInstance		= hInst;
	//�̸� ����� �� ���� ������ ����
	wnd.hIcon			= LoadIcon(0, IDI_APPLICATION); // �ý��ۿ��� ��ϵ� ���� ����, APPLICATION ������ ���.
	wnd.hCursor			= LoadCursor(0, IDC_ARROW); // �ý��ۿ��� ��ϵ� ���� ����, ARROW ������ ���.
	//GetStockObject() -> BRUSH, PEN, FONT
	wnd.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);//(HBRUSH)(COLOR_WINDOW + 1);

	wnd.lpszMenuName	= 0;
	wnd.lpszClassName	= TEXT("wb41");
	wnd.hIconSm			= 0;

	//2. ������ Ŭ���� ���(������Ʈ��)
	RegisterClassEx(&wnd);

	//3. ������ ��ü ����

	HWND hwnd = CreateWindowEx(WS_EX_TOPMOST, TEXT("wb41"), TEXT("1st ������"), // â �Ӽ�, Ŭ������, ������ Ÿ��Ʋ
		WS_OVERLAPPEDWINDOW,  // ���� �̰� ��
		0, 0, // x, y
		500, 300, // Width, Height
		0, 0, hInst, 0 // parent, menu, hInstance, param
		);

	//4. ������ ȭ�� ���
	ShowWindow(hwnd, SW_SHOW); // showcmd : WinMain�� ������ ����

	MessageBox(NULL, TEXT("Hello, API"), TEXT("FIRST"), MB_YESNO | MB_ICONQUESTION); //NULL, ����, ĸ��, �޽����ڽ� �÷��� |(or) ������ (��Ʈ�������� �Ѱ� �� �� ����)

	return 0;
}