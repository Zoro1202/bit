//print.cpp
#include "std.h"

void print_shapePrint(HWND hwnd, HDC hdc, const SHAPE* pshape)
{
	//brush
	HBRUSH br = CreateSolidBrush(pshape->br_color);
	HBRUSH old_brush = (HBRUSH)SelectObject(hdc, br);
	//pen
	HPEN pen = CreatePen(PS_SOLID, 3, pshape->pen_color);
	HPEN old_pen = (HPEN)SelectObject(hdc, pen);
	//Draw / print 
	switch (pshape->type)
	{
	case ST_RECTANGLE:
	{
		Rectangle(hdc, 
			pshape->pt.x - (pshape->size/2),
			pshape->pt.y - (pshape->size / 2),
			pshape->pt.x + (pshape->size / 2),
			pshape->pt.y + (pshape->size / 2)
			);
		break;
	}
	case ST_ELLIPSE:
	{
		Ellipse(hdc,
			pshape->pt.x - (pshape->size / 2),
			pshape->pt.y - (pshape->size / 2),
			pshape->pt.x + (pshape->size / 2),
			pshape->pt.y + (pshape->size / 2)
		);
		break;
	}
	}
	//delete
	DeleteObject(SelectObject(hdc, old_brush));
	DeleteObject(SelectObject(hdc, old_pen));
}