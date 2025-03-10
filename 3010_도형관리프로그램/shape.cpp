//shape.cpp
#include "std.h"


void shape_setShape(SHAPE* shape, int type, COLORREF color, POINTS point, int size)
{
	shape->type = type;
	shape->color = color;
	shape->pt = point;
	shape->size = size;
}

void shape_setType(SHAPE* shape, int type) { shape->type = type; }
void shape_setColor(SHAPE* shape, COLORREF color) { shape->color = color; }
void shape_setPoint(SHAPE* shape, POINTS pt) { shape->pt = pt; }
void shape_setSize(SHAPE* shape, int size) { shape->size = size; }

int shape_getType(const SHAPE* shape) { return shape->type; }
COLORREF shape_getColor(const SHAPE* shape){ return shape->color; }
POINTS shape_getPoint(const SHAPE* shape){ return shape->pt; }
int shape_get_Size(const SHAPE* shape){ return shape->size; }

