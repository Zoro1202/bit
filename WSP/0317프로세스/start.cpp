//start.cpp
#include "std.h"

INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
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
		return TRUE;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, IDCANCEL);
			return TRUE;
		}
	}
	}
	return FALSE;
}

int WINAPI _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hprevInstance, _In_ LPTSTR cmdline, _In_ int showcmd)
{
	INT_PTR ret = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);

	return 0;
}
