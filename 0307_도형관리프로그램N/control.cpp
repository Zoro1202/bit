//control.cpp
#include "std.h"

vector<SHAPE> g_shapes;

SHAPE g_shape; // global value : shape

void con_shapeInsert(HWND hwnd)
{
	SHAPE newshape = g_shape;
	g_shapes.push_back(newshape);
	InvalidateRect(hwnd, 0, TRUE);
}

void con_init(HWND hwnd)
{
	POINTS pt = { 100, 200 };
	shape_SetData(&g_shape, ST_ELLIPSE, RGB(255, 0, 0), RGB(255, 0, 0), pt, 100);
}

void con_print(HWND hwnd, HDC hdc)
{
	for (int i = 0; i < g_shapes.size(); i++)
	{
		SHAPE sh = g_shapes[i];
		print_shapePrint(hwnd, hdc, &sh);
	}
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

void con_shapeDelete(HWND hwnd)
{
	if (g_shapes.size() == 0) {
		MessageBox(hwnd, TEXT("도형이 없음"), TEXT("정보"), MB_OK);
	}
	else {
		g_shapes.erase(g_shapes.begin() + g_shapes.size() - 1);
		InvalidateRect(hwnd, 0, TRUE);
	}
}

void con_shapeInfo(HWND hwnd)
{
	static TCHAR buf[50];
	shape_tostring(&g_shape, buf);
	MessageBox(hwnd, buf, TEXT("정보"), MB_OK);
	
}