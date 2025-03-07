//shape.cpp
#include "std.h"

//initialize SHAPE
void shape_SetData(SHAPE* pshape, int type, COLORREF br_color, COLORREF pen_color, POINTS points, int size)
{
	pshape->type = type;
	pshape->br_color = br_color;
	pshape->pen_color = pen_color;
	pshape->pt = points;
	pshape->size = size;
}
// setter
void shape_setType(SHAPE* pshape, int type) { pshape->type = type; }
void shape_setBrushColor(SHAPE* pshape, COLORREF color) { pshape->br_color = color; }
void shape_setPenColor(SHAPE* pshape, COLORREF color) { pshape->pen_color = color; }
void shape_setPt(SHAPE* pshape, POINTS pt) { pshape->pt = pt; }
void shape_setSize(SHAPE* pshape, int size) { pshape->size = size; }
// getter
int shape_getType(const SHAPE* pshape) { return pshape->type; }
COLORREF shape_getBrushColor(const SHAPE* pshape) { return pshape->br_color; }
COLORREF shape_getPenColor(const SHAPE* pshape) { return pshape->pen_color; }
POINTS shape_getPt(const SHAPE* pshape) { return pshape->pt; }
int shape_getSize(const SHAPE* pshape) { return pshape->size; }

// shape data to string
void shape_tostring(const SHAPE* pshape, TCHAR* buf)
{
	// brush color to string
	TCHAR brush_color[20];
	wsprintf(brush_color, TEXT("r:%d, g:%d, b:%d"),
		GetRValue(pshape->br_color), GetGValue(pshape->br_color), GetBValue(pshape->br_color));
	// pen color to string
	TCHAR pen_color[20];
	wsprintf(pen_color, TEXT("r:%d, g:%d, b:%d"),
		GetRValue(pshape->pen_color), GetGValue(pshape->pen_color), GetBValue(pshape->pen_color));
	// data to string
	wsprintf(buf, TEXT("%d\r\n%s\r\n%s\r\n(%d, %d)\r\n%d"),
		pshape->type, brush_color, pen_color,
		(int)pshape->pt.x, (int)pshape->pt.y, pshape->size);
}