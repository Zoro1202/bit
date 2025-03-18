//08_동기화.cpp
#pragma comment (linker, "/subsystem:windows")
/*synchronization
1) 크리티컬 섹션(Critical Section) : 임계 영역(하나의 프로세스만 들어갈 수 있는 영역
-------------------------
[커널, os가 소유, 프로세스 간 동기화 가능]
2) mutex : 소유권 (소유권을 갖고 있는 프로세스만 들어갈 수 있음)
3) shemaphore : 공유 자원에 접근할 수 있는 개수 제한
4) Event : (수동) 자고 있는 모든 스레드를 깨우는 것
		   (자동) 스레드의 순서를 제어
*/
#include <Windows.h>
#include <tchar.h>

int x = 0;

CRITICAL_SECTION g_cs;

DWORD WINAPI ThreadFunc1(LPVOID param)
{
	HDC hdc = GetDC((HWND)param);

	for (int i = 0; i < 100; i++)
	{
		EnterCriticalSection(&g_cs);
		x = 100;
		TextOut(hdc, x, 100, TEXT("강아지"), 3);
		LeaveCriticalSection(&g_cs);
		Sleep(1);
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}
DWORD WINAPI ThreadFunc2(LPVOID param)
{
	HDC hdc = GetDC((HWND)param);

	for (int i = 0; i < 100; i++)
	{
		EnterCriticalSection(&g_cs);
		x = 200;
		TextOut(hdc, x, 200, TEXT("고양이"), 3);
		LeaveCriticalSection(&g_cs);
		Sleep(1);
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}

//메시지 처리 함수
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//static HWND hProg;
	static HANDLE hThread1;
	static HANDLE hThread2;
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
		DWORD tid;// 스레드 아이디 보톤 필요없긴함
		hThread1 = CreateThread(0, 0,
			ThreadFunc1, (void*)hwnd,
			0,
			&tid);
		hThread2 = CreateThread(0, 0,
			ThreadFunc2, (void*)hwnd,
			0,
			&tid);


		return 0;
	} case WM_RBUTTONDOWN:
	{
		DWORD code;
		GetExitCodeThread(hThread1, &code);
		if (code == STILL_ACTIVE)
		{
			TerminateThread(hThread1, -1);
			CloseHandle(hThread1);
		}
		GetExitCodeThread(hThread2, &code);
		if (code == STILL_ACTIVE)
		{
			TerminateThread(hThread2, -1);
			CloseHandle(hThread2);
		}
	}
	case WM_CREATE:
	{
		InitializeCriticalSection(&g_cs);
		//SetTimer(hwnd, 1, 10, 0);
		return 0;
	}

	//DestroyWindow() 함수 내부에서 호출
	//종료처리시점!!!!
	case WM_DESTROY:
	{
		//App Q에 WM_QUIT 메시지 넣어준다.
		//KillTimer(hwnd, 1);
		CloseHandle(hThread1);
		CloseHandle(hThread2);
		DeleteCriticalSection(&g_cs);
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