//print.cpp
#include "std.h"

void print_ShapeInfo(HDC hdc, const SHAPE* shape, size_t size)
{
	POINT pt = { 0, 0 };
	TCHAR msg[30];
	wsprintf(msg, TEXT("타입 : %d"), shape->type);
	TextOut(hdc, pt.x, pt.y, msg, _tcslen(msg));
	wsprintf(msg, TEXT("색상 : %d, %d, %d"), 
		GetRValue(shape->color), GetGValue(shape->color), GetBValue(shape->color));
	TextOut(hdc, pt.x, pt.y+20, msg, _tcslen(msg));
	wsprintf(msg, TEXT("좌표 : %d, %d"),
		shape->pt.x, shape->pt.y);
	TextOut(hdc, pt.x, pt.y+40, msg, _tcslen(msg));
	wsprintf(msg, TEXT("크기 : %d"),
		shape->size);
	TextOut(hdc, pt.x, pt.y+60, msg, _tcslen(msg));
	wsprintf(msg, TEXT("저장된 개수 : %d"),
		size);
	TextOut(hdc, pt.x, pt.y + 80, msg, _tcslen(msg));
}

void print_shape(HDC hdc, const SHAPE* shape)
{
	HBRUSH hbrush = CreateSolidBrush(shape->color);
	HBRUSH oldbr = (HBRUSH)SelectObject(hdc, hbrush);
	if (shape->type == 1)
	{
		Rectangle(hdc, shape->pt.x, shape->pt.y, shape->pt.x + shape->size, shape->pt.y + shape->size);
	}
	else if (shape->type == 2)
	{
		Ellipse(hdc, shape->pt.x, shape->pt.y, shape->pt.x + shape->size, shape->pt.y + shape->size);
	}
	else if (shape->type == 3)
	{
		POINT pt[3] = { 
			{shape->pt.x, shape->pt.y},
			{shape->pt.x + (shape->size / 2), shape->pt.y + sin(3.141592 / 3) * shape->size},						//PI
			{shape->pt.x - shape->size / 2, shape->pt.y + sqrt(pow(shape->size, 2) - pow(shape->size / 2, 2))}};	//pita
		Polygon(hdc, pt, 3);
	}
	DeleteObject(SelectObject(hdc, oldbr));
}
