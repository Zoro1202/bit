#include "std.h"

void shape_setShape(SHAPE* pshape, bool isshow, COLORREF color, RECT rc)
{
	pshape->isShow = isshow;
	pshape->color = color;
	pshape->rc = rc;
}
