//handler.cpp
#include "std.h"

BOOL OnInitDialog(HWND hdlg, WPARAM wParam, LPARAM lParam)
{
	con_init(hdlg);
	//static HWND hToolTip;
	//INITCOMMONCONTROLSEX icex;
	//icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	//icex.dwICC = ICC_WIN95_CLASSES;
	//InitCommonControlsEx(&icex);

	//// 툴팁 생성
	//hToolTip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL,
	//	WS_POPUP | TTS_ALWAYSTIP | TTS_BALLOON,
	//	CW_USEDEFAULT, CW_USEDEFAULT,
	//	CW_USEDEFAULT, CW_USEDEFAULT,
	//	hdlg, NULL, GetModuleHandle(NULL), NULL);

	//if (!hToolTip) return FALSE;

	//TOOLINFO ti = { 0 };
	//ti.cbSize = sizeof(TOOLINFO);
	//ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	//ti.hwnd = hdlg;
	//ti.hinst = GetModuleHandle(NULL);

	//ti.uId = (UINT_PTR)hButton;
	//ti.lpszText = TEXT("이 버튼을 누르면 액션이 실행됩니다!");
	//// 툴팁 추가
	//SendMessage(hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);
	

	return TRUE;
}

BOOL OnCommand(HWND hdlg, WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(wParam) == IDCANCEL)
	{
		EndDialog(hdlg, IDCANCEL);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON1)
	{
		//리스트에 추가
		con_insert(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON2)
	{
		//모달 오픈~
		con_modal(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_COMBO1)
	{
		//타입 변경
		con_updateCombo1(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_COMBO2)
	{
		//상품 선택
		con_updateCombo2(hdlg);
		return TRUE;
	}
	return FALSE;
}
