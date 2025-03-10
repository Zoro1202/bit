//control.cpp
#include "std.h"

SHAPE  g_curshape;
vector<SHAPE> g_shape;

void con_init()
{
	POINTS pt = { 100, 200 };
	shape_setShape(&g_curshape, 1, RGB(255, 0, 0), pt, 50);
}

void con_print(HWND hwnd, HDC hdc)
{
	print_ShapeInfo(hdc, &g_curshape, g_shape.size());
	for (size_t i = 0; i < g_shape.size(); i++) {
		print_shape(hdc, &g_shape[i]);
	}
}

void con_setShapeType(HWND hwnd, int type)
{
	if(type == 1) shape_setType(&g_curshape, 1);
	else if(type == 2) shape_setType(&g_curshape, 2);
	else if(type == 3) shape_setType(&g_curshape, 3);
}

void con_setShapeColor(HWND hwnd, int type)
{
	shape_setType(&g_curshape, type);
}

void con_setShapeColor(HWND hwnd, TCHAR key)
{
	if (key == 'R') {
		shape_setColor(&g_curshape, RGB(255, 0, 0));
	}
	else if (key == 'G')
	{
		shape_setColor(&g_curshape, RGB(0, 255, 0));
	}
	else if (key == 'B')
	{
		shape_setColor(&g_curshape, RGB(0, 0, 255));
	}
	else if (key == 'P')
	{
		shape_setColor(&g_curshape, RGB(rand() % 255, rand() % 255, rand() % 255));
	}
}

void con_setShapePoint(HWND hwnd, POINTS pt)
{
	shape_setPoint(&g_curshape, pt);
}

void con_setShapeSize(HWND hwnd, TCHAR key)
{
	if (key == VK_UP && g_curshape.size < 125) 
	{
		shape_setSize(&g_curshape, g_curshape.size + 25);
	}
	else if (key == VK_DOWN && g_curshape.size > 25)
	{
		shape_setSize(&g_curshape, g_curshape.size - 25);
	}
}

void con_createShape(HWND hwnd)
{
	g_shape.push_back(g_curshape);
	RECT rect = {
		g_curshape.pt.x - g_curshape.size, g_curshape.pt.y - g_curshape.size,
		g_curshape.pt.x + g_curshape.size, g_curshape.pt.y + g_curshape.size
	};
	InvalidateRect(hwnd, &rect, TRUE); 
	rect = {
		0, 0, 
		150, 100
	};
	InvalidateRect(hwnd, &rect, TRUE);
}

void con_deleteLastShape(HWND hwnd)
{
	if (g_shape.size() > 0)
	{
		g_shape.pop_back();
	}
}


void con_save(HWND hwnd)
{
	file_save(g_shape, hwnd);
}
void con_load(HWND hwnd)
{
	file_load(g_shape, hwnd);
}