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
	//----------------뻐튼-----------------------
	else if (LOWORD(wParam) == IDC_BUTTON1) // 입력
	{
		con_insertMember(hdlg);
	}
	else if (LOWORD(wParam) == IDC_BUTTON2) // 검색 
	{
		con_selectMember(hdlg);
	}
	else if (LOWORD(wParam) == IDC_BUTTON3) // 메시지
	{
		con_sendmessage(hdlg);
	}
	else if (LOWORD(wParam) == IDC_BUTTON4) // 삭제
	{
		con_deleteMember(hdlg);
	}
	else if (LOWORD(wParam) == IDC_BUTTON5) // 수정
	{
		con_updateMember(hdlg);
	}
	return FALSE;
}

