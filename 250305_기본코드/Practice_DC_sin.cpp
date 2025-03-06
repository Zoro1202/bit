//Practice_DC_sin.cpp
#pragma comment (linker, "/subsystem:windows")

#include <math.h>
#include <Windows.h>
#include <tchar.h>

#define NUM 5			// 사인 곡선의 해상도 resolution
#define TWOPI (2 * 3.14159) // 2 * PI

//메시지 처리 함수
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
		cxClient = LOWORD(lParam); // x값을 가져온다. 하위 2바이트
		cyClient = HIWORD(lParam); // y값을 가져온다. 상위 2바이트
		return 0;
	}
	case WM_PAINT:
	{
		HDC hdc = BeginPaint(hwnd, &ps);
		MoveToEx(hdc, 0, cyClient / 2, NULL); 
		LineTo(hdc, cxClient, cyClient / 2);

		for (i = 0; i < NUM; i++)
		{
			apt[i].x = i * cxClient / (NUM - 1);	// NUM => 점의 개수
			apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / (NUM - 1)))); // sin(0)->sin(Pi/2)->sin(Pi)->sin(Pi*3/4)->sin(2*Pi)
		}																 // 0       1          0        -1            0
		Polyline(hdc, apt, NUM);
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