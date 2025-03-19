#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

#include "resource.h"

HANDLE he;

INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hProcess2;
	switch (msg)
	{
	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hdlg, &ps);


	//	EndPaint(hdlg, &ps);
	//	return TRUE;
	//}
	case WM_INITDIALOG:
	{
		he = CreateEvent(0, 0, TRUE, TEXT("e"));
		return TRUE;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDCANCEL)
		{
			CloseHandle(he);
			EndDialog(hdlg, IDCANCEL);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON1) // setEvent
		{
			SetEvent(he);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON2) // reset Event
		{
			ResetEvent(he);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON3)// pulse Event
		{
			PulseEvent(he);
			return TRUE;
		}
	}
	}

	return FALSE;
}

//시작 함수
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPTSTR cmdline, int showcmd)
{
	INT_PTR ret = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);

	return 0;
}