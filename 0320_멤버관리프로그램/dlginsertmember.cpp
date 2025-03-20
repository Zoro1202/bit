//dlginsertmember.cpp
#include "std.h"


INT_PTR CALLBACK ModalProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static MEMBER* pmember;
	switch (msg)
	{
	case WM_INITDIALOG: 
	{
		pmember = (MEMBER*)lParam;
		return TRUE;
	}
	case WM_COMMAND: 
	{
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, IDCANCEL);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON1)
		{
			TCHAR id[20], pw[20], name[20], phone[20];
			int age = 0;
			GetDlgItemText(hdlg, IDC_EDIT1, id, _countof(id));
			GetDlgItemText(hdlg, IDC_EDIT2, pw, _countof(pw));
			GetDlgItemText(hdlg, IDC_EDIT3, name, _countof(name));
			GetDlgItemText(hdlg, IDC_EDIT4, phone, _countof(phone));
			age = GetDlgItemInt(hdlg, IDC_EDIT5, 0, 0);

			_tcscpy_s(pmember->id, _countof(pmember->id), id);
			_tcscpy_s(pmember->pw, _countof(pmember->pw), pw);
			_tcscpy_s(pmember->name, _countof(pmember->name), name);
			_tcscpy_s(pmember->phone, _countof(pmember->phone), phone);
			pmember->age = age;

			EndDialog(hdlg, IDOK);
			return TRUE;
		}
	}
	}

	return FALSE;
}
