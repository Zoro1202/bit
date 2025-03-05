//04_윈도우만들기.cpp

#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPTSTR cmdline, int showcmd)
{
	// 1. 윈도우 클래스 정의
	WNDCLASSEX wnd;
	wnd.cbSize			= sizeof(WNDCLASSEX);
	wnd.style			= CS_HREDRAW | CS_VREDRAW; // 0;
	wnd.lpfnWndProc		= DefWindowProc; // 미리 정의되어 있는 메시지 처리 프로시저
	wnd.cbClsExtra		= 0;
	wnd.cbWndExtra		= 0;
	wnd.hInstance		= hInst;
	//미리 만들어 진 것을 가져다 쓰기
	wnd.hIcon			= LoadIcon(0, IDI_APPLICATION); // 시스템에서 등록된 것을 쓴다, APPLICATION 아이콘 사용.
	wnd.hCursor			= LoadCursor(0, IDC_ARROW); // 시스템에서 등록된 것을 쓴다, ARROW 아이콘 사용.
	//GetStockObject() -> BRUSH, PEN, FONT
	wnd.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);//(HBRUSH)(COLOR_WINDOW + 1);

	wnd.lpszMenuName	= 0;
	wnd.lpszClassName	= TEXT("wb41");
	wnd.hIconSm			= 0;

	//2. 윈도우 클래스 등록(레지스트리)
	RegisterClassEx(&wnd);

	//3. 윈도우 객체 생성

	HWND hwnd = CreateWindowEx(WS_EX_TOPMOST, TEXT("wb41"), TEXT("1st 윈도우"), // 창 속성, 클래스명, 윈도우 타이틀
		WS_OVERLAPPEDWINDOW,  // 보통 이거 씀
		0, 0, // x, y
		500, 300, // Width, Height
		0, 0, hInst, 0 // parent, menu, hInstance, param
		);

	//4. 윈도우 화면 출력
	ShowWindow(hwnd, SW_SHOW); // showcmd : WinMain의 마지막 인자

	MessageBox(NULL, TEXT("Hello, API"), TEXT("FIRST"), MB_YESNO | MB_ICONQUESTION); //NULL, 내용, 캡션, 메시지박스 플래그 |(or) 아이콘 (비트연산으로 켜고 끌 수 있음)

	return 0;
}