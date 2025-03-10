//handler.cpp
#include "std.h"

LRESULT OnCreate(HWND hwnd)
{
	//MessageBox(hwnd, TEXT("»ý¼ºµÊ"), TEXT("Ã¢"), MB_OK);
	con_init();
	return 0;
}

LRESULT OnDestroy(HWND hwnd)
{
	//MessageBox(hwnd, TEXT("Á¦°ÅµÊ"), TEXT("Ã¢"), MB_OK);
	PostQuitMessage(0);
	return 0;
}

LRESULT OnPaint(HWND hwnd, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);	//beginPaint

	con_print(hwnd, hdc);

	EndPaint(hwnd, &ps);				//endPaint
	return 0;
}
//wParam => keycode
LRESULT OnKeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	if (wParam >= '1' && wParam <= '3') 
	{
		con_setShapeType(hwnd, (int)wParam - '0');
	}
	else if (wParam == 'R' || wParam == 'G' || wParam == 'B' || wParam == 'P')
	{
		con_setShapeColor(hwnd, (TCHAR)wParam);
	}
	else if (wParam == VK_UP || wParam == VK_DOWN)
	{
		con_setShapeSize(hwnd, (TCHAR)wParam);
	}
	else if (wParam == VK_ESCAPE)
	{
		con_deleteLastShape(hwnd);
	}
	else if (wParam == 'S') 
	{
		con_save(hwnd);
	}
	else if (wParam == 'L')
	{
		con_load(hwnd);
	}
	InvalidateRect(hwnd, 0, TRUE);
	return 0;
}

LRESULT OnLbuttonDown(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	POINTS pt = MAKEPOINTS(lParam);
	con_setShapePoint(hwnd, pt);
	con_createShape(hwnd);
	return 0;
}
