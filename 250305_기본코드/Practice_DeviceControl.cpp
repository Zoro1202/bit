//Practice_DeviceControl.cpp
#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

//메시지 처리 함수
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		POINTS pt = MAKEPOINTS(lParam);
		HDC hdc = GetDC(hwnd);
		HBRUSH hbrush = (HBRUSH)GetStockObject(WHITE_BRUSH+1);
		SelectObject(hdc, hbrush);
		Rectangle(hdc, pt.x, pt.y, pt.x+20, pt.y+20);

		ReleaseDC(hwnd, hdc);
		return 0;
	}
	case WM_RBUTTONDOWN:
	{
		RECT r = { 10, 10, 200, 200 };

		HDC hdc = GetDC(hwnd);
		SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
		Rectangle(hdc, 10, 10, 200, 200);

		ReleaseDC(hwnd, hdc);

		//InvalidateRect(hwnd, &r, FALSE);

		return 0;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT pt;
		HDC hdc = BeginPaint(hwnd, &pt);

		Rectangle(hdc, 10, 10, 210, 210);

		EndPaint(hwnd, &pt);

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
	wnd.hIcon = LoadIcon(0, IDI_APPLICATION);
	wnd.hCursor = LoadCursor(0, IDC_HAND);
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
		WS_OVERLAPPEDWINDOW,// &~ WS_MAXIMIZEBOX &~ WS_MINIMIZEBOX,
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