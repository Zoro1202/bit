#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>
#include <CommCtrl.h>

DWORD ThreadFunc1(LPVOID temp)
{
	HWND hProg = (HWND)temp;

	for (int i = 0; i < 1000; i++)
	{
		SendMessage(hProg, PBM_SETPOS, i, 0);
		Sleep(10);
	}
	return 0;
}

//메시지 처리 함수
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hProg;
	static HANDLE hThread;
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		DWORD tid;
		hThread = CreateThread(0, 0,
			ThreadFunc1, (void*)hProg,
			CREATE_SUSPENDED,
			&tid);

		return 0;
	} case WM_RBUTTONDOWN:
	{
		static BOOL b = FALSE;
		b = !b;
		if (b)
		{
			ResumeThread(hThread);
		}
		else {
			SuspendThread(hThread);
		}
		return 0;
	}
	case WM_CREATE:
	{
		hProg = CreateWindow(PROGRESS_CLASS, TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | PBS_SMOOTH,
			10, 10, 500, 30, hwnd, (HMENU)1, 0, 0);
		SendMessage(hProg, PBM_SETRANGE32, 0, 1000);
		SendMessage(hProg, PBM_SETPOS, 0, 0);
		//SetTimer(hwnd, 1, 10, 0);
		return 0;
	}

	//DestroyWindow() 함수 내부에서 호출
	//종료처리시점!!!!
	case WM_DESTROY:
	{
		//App Q에 WM_QUIT 메시지 넣어준다.
		//KillTimer(hwnd, 1);
		CloseHandle(hThread);
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
	while (GetMessage(&msg, 0, 0, 0))
	{
		DispatchMessage(&msg);
	}

	return 0;
}