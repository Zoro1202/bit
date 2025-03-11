//13_Control.cpp

#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

#include "resource.h"

#define IDC_BUTTON	1
#define IDC_EDIT	2
#define IDC_LISTBOX 3
#define IDC_COMBOBOX 6
#define IDC_STATIC 5

HWND hBtn, hEdit, hListBox, hComboBox, hStatic;

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

		POINT pt = { LOWORD(lParam), HIWORD(lParam) };

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
		case ID_CLOSE: SendMessage(hwnd, WM_CLOSE, 0, 0); break;
		case ID_RCOLOR: color = RGB(255, 0, 0); break;
		case ID_GCOLOR: color = RGB(0, 255, 0); break;
		case ID_BCOLOR: color = RGB(0, 0, 255); break;
		case ID_RECT: type = 1; break;
		case ID_ELLI: type = 2; break;
		case ID_INFO: MessageBox(hwnd, TEXT("정보"), TEXT("프로그램정보"), MB_OK);

		case IDC_BUTTON:
		{
			TCHAR buf[100];
			GetWindowText(hStatic, buf, _countof(buf));//SetWindowText(hEdit, TEXT("립력")); break;

			SetWindowText(hEdit, buf);
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)buf);
			SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)buf);

			break;
		}
		case IDC_EDIT: 
		{
			TCHAR buf[100];
			GetWindowText(hEdit, buf, _countof(buf));
			SetWindowText(hwnd, buf);
			break;
		}
		case IDC_LISTBOX: 
		{
			if (HIWORD(wParam) == LBN_SELCHANGE)
			{
				TCHAR str[128];
				int i = (int)SendMessage(hListBox, LB_GETCURSEL, 0, 0);
				SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)str);
				SetWindowText(hwnd, str);
			}
			break;
		}
		case IDC_COMBOBOX: 
		{
			TCHAR str[128];
			if (LOWORD(wParam) == CBN_SELCHANGE) {
				int i = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
				SendMessage(hComboBox, CB_GETLBTEXT, i, (LPARAM)str);
				SetWindowText(hwnd, str);
			}
			else if (LOWORD(wParam) == CBN_EDITCHANGE)
			{
				GetWindowText(hComboBox, str, 128);
				SetWindowText(hwnd, str);
			}
			break;
		}
		case IDC_STATIC: break;
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
		hEdit = CreateWindow(TEXT("Edit"), TEXT("에디트"),
			WS_CHILD | WS_BORDER,
			10, 40, 90, 20, hwnd, (HMENU)IDC_EDIT, 0, 0);
		ShowWindow(hEdit, SW_SHOW);
		hBtn = CreateWindow(TEXT("button"), TEXT("버튼!"),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 10, 90, 20, hwnd, (HMENU)IDC_BUTTON, 0, 0);
		hListBox = CreateWindow(TEXT("listbox"), 0,
			WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
			10, 100, 90, 200, hwnd, (HMENU)IDC_LISTBOX, 0, 0);
		hComboBox = CreateWindow(TEXT("combobox"), 0,
			WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN,
			150, 10, 210, 20, hwnd, (HMENU)IDC_COMBOBOX, 0, 0);
		hStatic = CreateWindow(TEXT("static"), TEXT("스태틱"),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			250, 40, 90, 20, hwnd, (HMENU)IDC_STATIC, 0, 0);

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
int WINAPI _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hprevInstance, _In_ LPTSTR cmdline, _In_ int showcmd)
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
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
