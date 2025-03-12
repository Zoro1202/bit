//ui.cpp
#include "std.h"

void ui_print(HWND hdlg, HDC hdc, RECT rc, COLORREF color)
{
	HBRUSH br = CreateSolidBrush(color);
	HBRUSH old = (HBRUSH)SelectObject(hdc, br);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	DeleteObject(SelectObject(hdc, old));
}

void ui_delete(HWND hdlg)
{
	InvalidateRect(hdlg, 0, TRUE);
}
