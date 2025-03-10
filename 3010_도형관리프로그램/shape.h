//shape.h
#pragma once

//SHAPE
//type | 1 : RECT , 2 : ELLIPSE, 3:TRIANGLE
//color | R , G, B 
//pt | X, Y
//size
typedef struct tagSHAPE
{
	int type;
	COLORREF color;
	POINTS pt;
	int size;
}SHAPE, *PSHAPE;

//initialize

void shape_setShape(SHAPE* shape, int type, COLORREF color, POINTS point, int size);

//setter

void shape_setType(SHAPE* shape, int type);
void shape_setColor(SHAPE* shape, COLORREF color);
void shape_setPoint(SHAPE* shape, POINTS pt);
void shape_setSize(SHAPE* shape, int size);

//getter

int shape_getType(const SHAPE* shape);
COLORREF shape_getColor(const SHAPE* shape);
POINTS shape_getPoint(const SHAPE* shape);
int shape_get_Size(const SHAPE* shape);

