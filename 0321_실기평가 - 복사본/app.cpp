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
	/// --------------------버튼------------------------
	else if (LOWORD(wParam) == IDC_BUTTON1) // 도서 입력 버튼
	{
		con_insertBook(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON2) // 도서 수정 버튼
	{
		con_updateBook(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON3) // 삭제 버튼
	{
		con_deleteBook(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON4) // 도서 검색 버튼
	{
		con_selectBook(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON5) // 도서 저장 버튼
	{
		con_savefile(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON6) // 도서 불러오기 버튼
	{
		con_loadfile(hdlg);
		return TRUE;
	}
	// 메뉴 -------------------------------------------------------------
	else if (LOWORD(wParam) == ID_40001) // 도서 다른 이름으로 저장 메뉴
	{
		con_savefile_filename(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == ID_40002) // 도서 불러오기 메뉴
	{
		con_loadfile_filename(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == ID_40003) // 프로그램 종료 메뉴
	{
		con_loadfile(hdlg);
		return TRUE;
	}

	return FALSE;
}
