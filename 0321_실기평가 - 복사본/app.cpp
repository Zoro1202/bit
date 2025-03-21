//handler.cpp
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
		EndDialog(hdlg, IDCANCEL);
		return TRUE;
	}
	/// --------------------��ư------------------------
	else if (LOWORD(wParam) == IDC_BUTTON1) // ���� �Է� ��ư
	{
		con_insertBook(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON2) // ���� ���� ��ư
	{
		con_updateBook(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON3) // ���� ��ư
	{
		con_deleteBook(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON4) // ���� �˻� ��ư
	{
		con_selectBook(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON5) // ���� ���� ��ư
	{
		con_savefile(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON6) // ���� �ҷ����� ��ư
	{
		con_loadfile(hdlg);
		return TRUE;
	}
	// �޴� -------------------------------------------------------------
	else if (LOWORD(wParam) == ID_40001) // ���� �ٸ� �̸����� ���� �޴�
	{
		con_savefile_filename(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == ID_40002) // ���� �ҷ����� �޴�
	{
		con_loadfile_filename(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == ID_40003) // ���α׷� ���� �޴�
	{
		con_loadfile(hdlg);
		return TRUE;
	}

	return FALSE;
}
