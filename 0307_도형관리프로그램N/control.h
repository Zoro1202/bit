//control.h
#pragma once

void con_init(HWND hwnd);

void con_print(HWND hwnd, HDC hdc);


void con_shapeInsert(HWND hwnd);
void con_updateShapePoint(HWND hwn, LPARAM lParam);
void con_updateShapeSize(HWND hwnd, int key);
void con_updateShapeType(HWND hwnd, int key);
void con_updateShapeBrushColor(HWND hwnd, int key);
void con_shapeDelete(HWND hwnd);
void con_shapeInfo(HWND hwnd);