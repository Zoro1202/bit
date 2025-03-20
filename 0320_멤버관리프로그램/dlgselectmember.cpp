#include "std.h"

INT_PTR ModalselectProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{

	static TCHAR* pmemberid = NULL;
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		pmemberid = (TCHAR*)lParam;
		return TRUE;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDCANCEL)
		{
			SendMessage(GetParent(hdlg), WM_CHILE_DESTROY, 0, 0);
			EndDialog(hdlg, IDCANCEL);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDOK)
		{
			TCHAR id[20];
			GetDlgItemText(hdlg, IDC_EDIT8, id, _countof(id));
			_tcscpy_s(pmemberid, _countof(id), id);

			SendMessage(GetParent(hdlg), WM_APPLY, 0, 0);

			return TRUE;
		}
	}
	}

	return FALSE;
}
