#include "std.h"

BOOL OnInitDialog(HWND hdlg, WPARAM wParam, LPARAM lParam)
{
	con_init(hdlg);
	return TRUE;
}

BOOL OnCommand(HWND hdlg, WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(wParam) == IDCANCEL)
	{
		con_exit(hdlg);
		EndDialog(hdlg, IDCANCEL);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTONCON)
	{
		con_connect(hdlg);
	}
	//----------------»µÆ°-----------------------
	else if (LOWORD(wParam) == IDC_BUTTON1)
	{
		con_insertMember(hdlg);
	}
	else if (LOWORD(wParam) == IDC_BUTTON2)
	{
		con_selectMember(hdlg);
	}
	else if (LOWORD(wParam) == IDC_BUTTON3)
	{
		con_sendmessage(hdlg);
	}
	return FALSE;
}

