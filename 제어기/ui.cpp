#include "std.h"

HWND hEdit1, hEdit2, hEdit3, hEdit4, hEdit5;
HWND hBtn1, hBtn2, hBtn3, hBtn4, hBtn5, hBtn6, hBtn7;

void ui_GetControlHandle(HWND hdlg)
{
	hEdit1 = GetDlgItem(hdlg, IDC_EDIT1); // R
	hEdit2 = GetDlgItem(hdlg, IDC_EDIT2); // G
	hEdit3 = GetDlgItem(hdlg, IDC_EDIT3); // B
	hEdit4 = GetDlgItem(hdlg, IDC_EDIT4); // X
	hEdit5 = GetDlgItem(hdlg, IDC_EDIT5); // Y
	hBtn1 = GetDlgItem(hdlg, IDC_BUTTON1);// 생성
	hBtn2 = GetDlgItem(hdlg, IDC_BUTTON2);// 종료
	hBtn3 = GetDlgItem(hdlg, IDC_BUTTON3);// 색상
	hBtn4 = GetDlgItem(hdlg, IDC_BUTTON4);// 위
	hBtn5 = GetDlgItem(hdlg, IDC_BUTTON5);// 왼
	hBtn6 = GetDlgItem(hdlg, IDC_BUTTON6);// 오
	hBtn7 = GetDlgItem(hdlg, IDC_BUTTON7);// 아
	
}

void ui_InitDataControl(HWND hdlg)
{
	//SetDlgItemText(hdlg, IDC_EDIT2, TEXT("ㅎㅇㅇ"));
	//SetWindowText(hEdit1, TEXT("ㅎㅇㅇ"));
	SetDlgItemInt(hdlg, IDC_EDIT1, 255, FALSE);
	SetDlgItemInt(hdlg, IDC_EDIT2, 0, FALSE);
	SetDlgItemInt(hdlg, IDC_EDIT3, 0, FALSE);
	SetDlgItemInt(hdlg, IDC_EDIT4, 10, FALSE);
	SetDlgItemInt(hdlg, IDC_EDIT5, 20, FALSE);

}

COLORREF ui_getColor(HWND hdlg)
{
	int r = GetDlgItemInt(hdlg, IDC_EDIT1, 0, 0);
	int g = GetDlgItemInt(hdlg, IDC_EDIT2, 0, 0);
	int b = GetDlgItemInt(hdlg, IDC_EDIT3, 0, 0);
	return RGB(r, g, b);
}

POINT ui_getPosition(HWND hdlg)
{
	int x = GetDlgItemInt(hdlg, IDC_EDIT4, 0, 0);
	int y = GetDlgItemInt(hdlg, IDC_EDIT5, 0, 0);
	POINT pt = { x, y };
	return pt;
}

void ui_setPosition(HWND hdlg, int x, int y)
{
	SetDlgItemInt(hdlg, IDC_EDIT4, x, 0);
	SetDlgItemInt(hdlg, IDC_EDIT5, y, 0);
}