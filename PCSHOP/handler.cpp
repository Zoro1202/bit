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

	//// ���� ����
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
	//ti.lpszText = TEXT("�� ��ư�� ������ �׼��� ����˴ϴ�!");
	//// ���� �߰�
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
		//����Ʈ�� �߰�
		con_insert(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON2)
	{
		//��� ����~
		con_modal(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_COMBO1)
	{
		//Ÿ�� ����
		con_updateCombo1(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_COMBO2)
	{
		//��ǰ ����
		con_updateCombo2(hdlg);
		return TRUE;
	}
	return FALSE;
}
