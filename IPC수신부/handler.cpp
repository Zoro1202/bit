//handler.cpp
#include "std.h"



bool OnInitDialog(HWND hdlg)
{
	con_init(hdlg);
	return TRUE;
}

bool OnPaint(HWND hdlg)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hdlg, &ps);

	con_print(hdlg, hdc);

	EndPaint(hdlg, &ps);
	return TRUE;
}

bool OnCommand(HWND hdlg, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDCANCEL:
	{
		EndDialog(hdlg, IDCANCEL);
		return TRUE;
	}
	}
	return FALSE;
}

bool OnMYSHOW(HWND hdlg, WPARAM wParam, LPARAM lParam)
{
	//MessageBox(hdlg, TEXT("Ã£À½"), TEXT("Ã¢"), MB_OK);
	con_visible(hdlg, lParam);
	InvalidateRect(hdlg, 0, TRUE);
	return TRUE;
}

bool OnMYCOLOR(HWND hdlg, WPARAM wParam, LPARAM lParam)
{
	con_color(hdlg, lParam);
	InvalidateRect(hdlg, 0, TRUE);
	return TRUE;
}

bool OnMYPOSITION(HWND hdlg, WPARAM wParam, LPARAM lParam)
{
	con_position(hdlg, lParam);
	InvalidateRect(hdlg, 0, TRUE);
	return TRUE;
}
