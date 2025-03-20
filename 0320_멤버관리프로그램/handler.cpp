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
	else if (LOWORD(wParam) == IDC_BUTTON1) // 멤버 입력 버튼
	{
		con_insertMember(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON2) // 로그인 버튼
	{
		con_login(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON3) // 멤버 검색
	{
		con_selectMember(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON4) // 멤버 수정 버튼
	{
		con_updateMember(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON5) // 멤버 삭제 버튼
	{
		con_deleteMember(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON6) // 파일 저장 버튼
	{
		con_savefile(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON7) // 파일 불러오기 버튼
	{
		con_loadfile(hdlg);
		return TRUE;
	}
	///-------------------------메뉴--------------------------
	else if (LOWORD(wParam) == ID_40001) // 멤버 불러오기
	{
		// 파일 저장 다이얼로그... 내가 원하는 파일을 읽어 오도록
		con_fileOpenDial(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == ID_40002) // 멤버 저장
	{
		// 파일 저장 다이얼로그... 내가 원하는 파일에 저장할 수 있도록
		con_fileSaveDial(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == ID_40003) // 프로그램 종료
	{
		// ENDDialog
		SendMessage(hdlg, WM_CLOSE, 0, 0);
		return TRUE;
	}
	else if (LOWORD(wParam) == ID_40004) // 멤버 저장
	{
		// 모달 창 띄우기
		con_InsertMember_Modal(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == ID_40005) // 멤버 검색
	{
		//모달리스 창 띄우기
		con_selectMember_Modaless(hdlg);
		return TRUE;
	}
	return FALSE;
}


BOOL OnChildDestroy(HWND hdlg)
{
	con_OnChildDestroy(hdlg);
	return TRUE;
}

BOOL OnAPPLY(HWND hdlg)
{
	//멤버 검색 모달에서 select 버튼 누름
	con_OnApply(hdlg);
	return TRUE;
}
