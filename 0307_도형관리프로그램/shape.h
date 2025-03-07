//shape.h
#pragma once

#define ST_RECTANGLE    1
#define ST_ELLIPSE		2

typedef struct tagSHAPE 
{
	int type;		// 1: Rectangle, 2: Ellipse
	COLORREF br_color;	// Brush Color
	COLORREF pen_color; // Pen Color
	POINTS pt;		// xy coordinate
	int size;		// size of Shape (25, 50, 75, 100)
}SHAPE, *PSHAPE;

void shape_SetData(SHAPE *pshape, int type, COLORREF br_color, COLORREF pen_color, POINTS points, int size);

void shape_setType(SHAPE* pshape, int type);
void shape_setBrushColor(SHAPE* pshape, COLORREF color);
void shape_setPenColor(SHAPE* pshape, COLORREF color);
void shape_setPt(SHAPE* pshape, POINTS pt);
void shape_setSize(SHAPE* pshape, int size);

int shape_getType(const SHAPE* pshape);
COLORREF shape_getBrushColor(const SHAPE* pshape);
COLORREF shape_getPenColor(const SHAPE* pshape);
POINTS shape_getPt(const SHAPE* pshape);
int shape_getSize(const SHAPE* pshape);

void shape_tostring(const SHAPE* pshape, TCHAR* buf);