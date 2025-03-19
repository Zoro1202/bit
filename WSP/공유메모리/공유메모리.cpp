#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

typedef struct tagLINE
{
	POINTS start;
	POINTS end;
}LINE, *PLINE;

HANDLE hEvent, hMap;
LINE* pData;
POINTS ptFrom;

void mmf_Create(HWND hwnd)
{
	hEvent = CreateEvent(0, 0, 0, TEXT("DRAW_SIGNAL")); // �ڵ� �̺�Ʈ

	hMap = CreateFileMapping((HANDLE)-1, 0, PAGE_READWRITE, 0, sizeof(LINE), TEXT("map"));
	pData = (LINE*)MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, 0);
	if (pData == NULL)
	{
		MessageBox(hwnd, TEXT("MMF ����"), TEXT("â"), MB_OK);
		return;
	}
}

void mmf_Destroy(HWND hwnd)
{
	UnmapViewOfFile(pData);
	CloseHandle(hMap);
	CloseHandle(hEvent);
}

//�޽��� ó�� �Լ�
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		ptFrom = MAKEPOINTS(lParam);
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		if (wParam & MK_LBUTTON) {
			POINTS pts = MAKEPOINTS(lParam);

			HDC hdc = GetDC(hwnd);

			MoveToEx(hdc, ptFrom.x, ptFrom.y, 0);
			LineTo(hdc, pts.x, pts.y);
			
			ReleaseDC(hwnd, hdc);
			

			pData->start = ptFrom;
			pData->end = pts;
			SetEvent(hEvent);
			ptFrom = pts;
			return 0;
		}
	}
	//������ �����Ǿ���, ȭ�鿡 �Ⱥ��δ�.
	//�ʱ�ȭ!!!!
	case WM_CREATE:
	{
		mmf_Create(hwnd);
		return 0;
	}

	//DestroyWindow() �Լ� ���ο��� ȣ��
	//����ó������!!!!
	case WM_DESTROY:
	{
		mmf_Destroy(hwnd);
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