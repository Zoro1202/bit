#pragma once

typedef struct tagSHAPE
{
	bool isShow;
	COLORREF color;
	RECT rc;
}SHAPE;

void shape_setShape(SHAPE* pshape, bool isshow, COLORREF color, RECT rc);
