//start.cpp
#include "std.h"

HWND hEdit1, hEdit2, hEdit3, hComb, hBtn, hStatic;

void GetHandle(HWND hdlg)
{
	hEdit1 = GetDlgItem(hdlg, IDC_EDIT1);
	hEdit2 = GetDlgItem(hdlg, IDC_EDIT2);
	hEdit3 = GetDlgItem(hdlg, IDC_EDIT3);
	hComb =	hEdit3 = GetDlgItem(hdlg, IDC_COMBO1);
	hBtn = GetDlgItem(hdlg, IDC_BUTTON1);
	hStatic = GetDlgItem(hdlg, IDC_IMAGE);
}

void ComboBoxAddString(HWND hdlg)
{
	SendMessage(hComb, CB_ADDSTRING, 0, (LPARAM)TEXT("°ËÁ¤"));
	SendMessage(hComb, CB_ADDSTRING, 0, (LPARAM)TEXT("»¡°­"));
	SendMessage(hComb, CB_ADDSTRING, 0, (LPARAM)TEXT("ÃÊ·Ï"));
	SendMessage(hComb, CB_ADDSTRING, 0, (LPARAM)TEXT("ÆÄ¶û"));

	SendMessage(hComb, CB_SETCURSEL, 2, 0);
}

void InitDataControl(HWND hdlg)
{
	//SetDlgItemText(hdlg, IDC_EDIT2, TEXT("¤¾¤·¤·"));
	SetWindowText(hEdit1, TEXT("¤¾¤·¤·"));
	SetDlgItemInt(hdlg, IDC_EDIT2, 100, FALSE);
	SetDlgItemInt(hdlg, IDC_EDIT3, 100, FALSE);
}

void PrintText(HWND hdlg, HDC hdc)
{
	TCHAR buf[50];
	GetDlgItemText(hdlg, IDC_EDIT1, buf, 20);
	RECT rc;
	TCHAR tcolor[20];

	int i = SendMessage(hComb, CB_GETCURSEL, 0, 0);

	if (i == 0) {
		SetTextColor(hdc, RGB(0, 0, 0));
	}
	else if (i == 1) {
		SetTextColor(hdc, RGB(255, 0, 0));
	}
	else if (i == 2) {
		SetTextColor(hdc, RGB(0, 255, 0));
	}
	else if (i == 3) {
		SetTextColor(hdc, RGB(0, 0, 255));
	}

	int x = GetDlgItemInt(hdlg, IDC_EDIT2, 0, 0);
	int y = GetDlgItemInt(hdlg, IDC_EDIT3, 0, 0);
	GetClientRect(hStatic, &rc);
	x += rc.right; y += rc.bottom;
	//GetClientRect(hdlg, &rc);
	TextOut(hdc, x, y, buf, _tcslen(buf));

}

INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hdlg, &ps);

		PrintText(hdlg, hdc);

		EndPaint(hdlg, &ps);
		return TRUE;
	}
	case WM_INITDIALOG:
	{
		GetHandle(hdlg);
		ComboBoxAddString(hdlg);
		InitDataControl(hdlg);
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
			HDC hdc = GetDC(hdlg);
			PrintText(hdlg, hdc);
			ReleaseDC(hdlg, hdc);
			return TRUE;
		}
		else if (LOWORD(wParam) == ID_40001) 
		{
			EndDialog(hdlg, IDOK);
			return TRUE;
		}
	}
	}

	return FALSE;
}

int WINAPI _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hprevInstance, _In_ LPTSTR cmdline, _In_ int showcmd)
{
	INT_PTR ret = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);

	return 0;
}
