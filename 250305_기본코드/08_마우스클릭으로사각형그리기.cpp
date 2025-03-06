//08_마우스클릭으로사각형그리기.cpp
/*
[어떤 사건이 발생했을 때] -> [어떤 일을 하고 싶다]
WM_LBUTTONUP : DC 획득 -> Rectangle -> DC 반납
*/
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
		POINTS pt = MAKEPOINTS(lParam); // POINT 인데 short 타입. 복수형 s 아님.

		HDC hdc = GetDC(hwnd);
		Rectangle(hdc, pt.x-25, pt.y-25, pt.x+25, pt.y+25); // 왼쪽 위 점 x, y  오른쪽 아래 점 x, y 순서
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
		WS_OVERLAPPEDWINDOW,// &~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0,
		500, 500, //CW_USEDEFAULT, 0,
		0, 0, hInst, 0);

	//4. 윈도우 화면 출력
	ShowWindow(hwnd, SW_SHOW); //showcmd : WinMain의 마지막인자	


	//5. 메시지 루프
	MSG msg;
	//GetMessage : WM_QUIT를 가져왔을 때만 FALSE 반환
	while (true)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else {
				DispatchMessage(&msg);
			}
		}
		else // 유휴 시간
		{
			//HDC hdc = GetDC(hwnd);

			////SetPixel(hdc, 10, 20, RGB(255, 0, 0));
			//SetPixel(hdc, rand() % 500, rand() % 500, RGB(rand() % 255, rand() % 255, rand() % 255));
			//ReleaseDC(hwnd, hdc); // DC는 한번 쓰고 파괴해야 함

		}
	}

	return 0;
}