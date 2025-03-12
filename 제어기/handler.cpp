//handler.cpp
#include "std.h"

bool OnInitDialog(HWND hdlg)
{
	con_init(hdlg);
	return TRUE;
}

bool OnCommand(HWND hdlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_BUTTON1: con_ipc_new(hdlg); return TRUE;
	case IDC_BUTTON2: con_ipc_exit(hdlg); return TRUE;
	case IDC_BUTTON3: con_ipc_color(hdlg); return TRUE;
	case IDC_BUTTON4:
	case IDC_BUTTON5:
	case IDC_BUTTON6:
	case IDC_BUTTON7:
	{
		con_ipc_Point(hdlg, wParam);
		return TRUE;
	}
	case IDCANCEL:
	{
		EndDialog(hdlg, IDCANCEL);
		return TRUE;
	}
	}
	return FALSE;
}