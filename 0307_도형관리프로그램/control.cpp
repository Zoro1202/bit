//control.cpp
#include "std.h"

SHAPE g_shape; // global value : shape

void con_init(HWND hwnd)
{
	POINTS pt = { 100, 200 };
	shape_SetData(&g_shape, ST_ELLIPSE, RGB(255, 0, 0), RGB(255, 0, 0), pt, 100);
}

void con_print(HWND hwnd, HDC hdc)
{
	print_shapePrint(hwnd, hdc, &g_shape);
}
// update pt and window(post PAINT message)
void con_updateShapePoint(HWND hwnd, LPARAM lParam)
{
	shape_setPt(&g_shape, MAKEPOINTS(lParam));
	InvalidateRect(hwnd, 0, TRUE);
}
//update size and window
void con_updateShapeSize(HWND hwnd, int key)
{
	int size = shape_getSize(&g_shape);
	if (key == VK_UP)
	{
		size += 25;
	}
	else if (key == VK_DOWN)
	{
		size -= 25;
	}
	else
	{
		return;
	}
	shape_setSize(&g_shape, size);
	InvalidateRect(hwnd, 0, TRUE);
}

void con_updateShapeType(HWND hwnd, int key)
{
	if (key == '1' || key == VK_NUMPAD1)
	{
		shape_setType(&g_shape, 1);
	}
	else if (key == '2' || key == VK_NUMPAD2)
	{
		shape_setType(&g_shape, 2);
	}
	InvalidateRect(hwnd, 0, TRUE);
}

void con_updateShapeBrushColor(HWND hwnd, int key)
{
	if (key == 'R') shape_setBrushColor(&g_shape, RGB(255, 0, 0));
	else if (key == 'G') shape_setBrushColor(&g_shape, RGB(0, 255, 0));
	else if (key == 'B') shape_setBrushColor(&g_shape, RGB(0, 0, 255));
	InvalidateRect(hwnd, 0, TRUE);
}
