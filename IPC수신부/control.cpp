//control.cpp
#include "std.h"

SHAPE g_shape;

void con_init(HWND hdlg)
{
	RECT rc = { 10, 10, 100, 100 };
	shape_setShape(&g_shape, 1, RGB(255, 0, 0), rc);
}

void con_print(HWND hdlg, HDC hdc)
{
	ui_print(hdlg, hdc, g_shape.rc, g_shape.color);
}

void con_visible(HWND hdlg, LPARAM lParam)
{
	if (lParam == 1) g_shape.isShow = TRUE;
	else if (lParam == 0) g_shape.isShow = FALSE;
}

void con_color(HWND hdlg, LPARAM lParam)
{
	g_shape.color = (COLORREF)lParam;
}

void con_position(HWND hdlg, LPARAM lParam)
{
	if (lParam == 1) g_shape.rc.top += 10, g_shape.rc.bottom += 10;
	else if (lParam == 2) g_shape.rc.top -= 10, g_shape.rc.bottom -= 10;
	else if (lParam == 3) g_shape.rc.left += 10, g_shape.rc.right += 10;
	else if (lParam == 2) g_shape.rc.left -= 10, g_shape.rc.right -= 10;

}