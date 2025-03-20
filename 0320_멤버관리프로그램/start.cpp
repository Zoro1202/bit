//start.cpp
#include "std.h"

INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG: return OnInitDialog(hdlg, wParam, lParam);
	case WM_COMMAND: return OnCommand(hdlg, wParam, lParam);
	case WM_CHILE_DESTROY: return OnChildDestroy(hdlg);
	case WM_APPLY: return OnAPPLY(hdlg);
	}

	return FALSE;
}
//시작 함수
int WINAPI _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hprevInstance, _In_ LPTSTR cmdline, _In_ int showcmd)
{
	INT_PTR ret = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);

	return 0;
}
