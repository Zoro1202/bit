//12_메뉴.cpp
/*
1. 메인 메뉴
	-메뉴의 아이템 클릭 시 -> 이벤트 수신 : WM_COMMAND, 어떤 아이템이 클릭되었는지?(ID)
	메뉴바에 있는 메뉴 인덱스 0부터 시작 왼쪽부터
2. 시스템 메뉴
	시스템 영역에서 우클릭하면 뜨는 메뉴
3. 컨텍스트 메뉴
	클라이언트 메뉴에서 우클릭하면 뜨는 메뉴
*/

#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

#include "resource.h"

//메시지 처리 함수
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
		case ID_INFO: MessageBox(hwnd, TEXT("정보"), TEXT("프로그램정보"), MB_OK);
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
	wnd.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

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
