//control.h
#pragma once

void con_init();

void con_print(HWND hwnd, HDC hdc);

void con_setShapeType(HWND hwnd, int type);
void con_setShapeColor(HWND hwnd, TCHAR key);
void con_setShapePoint(HWND hwnd, POINTS pt);
void con_setShapeSize(HWND hwnd, TCHAR key);

void con_createShape(HWND hwnd);
void con_deleteLastShape(HWND hwnd);

void con_save(HWND hwnd);
void con_load(HWND hwnd);