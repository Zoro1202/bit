//11_IconCursur.cpp
/*
마우스 이벤트 발생
1) WM_NCHITTEST 메시지 발생
	HITTEST Code를 획득 - HTCAPTION, HTCLIENT, HTLEFT, HTRIGHT 등등
2) WM_SETCURSOR 메시지 발생
	현재 HITTEST Code에 따른 마우스커서 모양 변경
3) WM_LBUTTONDOWN 등 마우스 커서 변경
*/
#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

#include "resource.h"

//메시지 처리 함수
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
	//윈도우 생성되었고, 화면에 안보인다.
	//초기화!!!!
	case WM_CREATE:
	{
		return 0;
	}

	//DestroyWindow() 함수 내부에서 호출
	//종료처리시점!!!!
	case WM_DESTROY:
	{
		//App Q에 WM_QUIT 메시지 넣어준다.
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//시작 함수
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPTSTR cmdline, int showcmd)
{
	//1. 윈도우 클래스 정의
	WNDCLASSEX wnd;
	wnd.cbSize = sizeof(WNDCLASSEX);

	wnd.style = CS_HREDRAW | CS_VREDRAW;  //  0;
	wnd.hInstance = hInst;
	wnd.lpfnWndProc = WndProc;  // DefWindowProc;	//미리 정의되어 있는 메시지 처리 프로시저
	wnd.lpszClassName = TEXT("wb41");

	//미리 만들어진 리소스를 사용하는 방법
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

	//2. 윈도우 클래스 등록
	RegisterClassEx(&wnd);

	//3. 윈도우객체 (생성.. CreateXXX)
	HWND hwnd = CreateWindowEx(WS_EX_TOPMOST, TEXT("wb41"), TEXT("첫번째 윈도우"),
		WS_OVERLAPPEDWINDOW,// &~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0,
		500, 500, //CW_USEDEFAULT, 0,
		0, 0, hInst, 0);

	//4. 윈도우 화면 출력
	ShowWindow(hwnd, SW_SHOW); //showcmd : WinMain의 마지막인자	


	//5. 메시지 루프
	MSG msg;
	//GetMessage : WM_QUIT를 가져왔을 때만 FALSE 반환
	while (GetMessage(&msg, 0, 0, 0))
	{
		DispatchMessage(&msg);
	}

	return 0;
}