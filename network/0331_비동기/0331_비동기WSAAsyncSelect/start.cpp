//echo server
//#pragma comment(linker, "/SUBSYSTEM:WINDOWS")
#include "Async_Server.h"

struct LINE
{
	POINTS ptFrom;
	POINTS ptTo;
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS ptFrom;

	switch (msg)
	{
	case WM_CREATE:
	{
		net_initSocket(hwnd);
		return 0;
	}
	case WM_DESTROY:
	{
		net_ExitSocket();
		PostQuitMessage(0);
		return 0;
	}
	case WM_USER + 100:
	{
		WORD event = WSAGETSELECTEVENT(lParam);
		WORD error = WSAGETSELECTERROR(lParam);

		switch (event)
		{
		case FD_CLOSE:
		{
			SetWindowText(hwnd, "접속이 끊어 졌습니다.");
			net_CloseSocket(wParam);
			return 0;
		}
		case FD_READ:
		{
			// data 도착 - 읽어 낸다.
			LINE line;
			int ret = net_recvData(wParam, (char *)&line, sizeof(line));
			if (ret == -1)
			{
				//접속이 끊겼습니다.
				net_CloseSocket(wParam);
			}
			else if (ret > 0)
			{
				net_sendallData(wParam, (char*)&line, sizeof(line));
				
			}
			return 0;
		}
		case FD_ACCEPT:
		{
			net_Accept(hwnd);
			break;
		}
		}
		break;
	}
	return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{

	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = "First";
	wc.lpszMenuName = 0;
	wc.style = 0;

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(0, "first", "Hello", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 600, 600, 0, 0,
		hInstance, 0);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	net_ExitSocket();
	return 0;
}


