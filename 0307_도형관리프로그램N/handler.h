//handler.h
#pragma once

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam);

LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam);
LRESULT OnLButtonDown(HWND hwnd, LPARAM lParam);

LRESULT OnKeyDown(HWND hwnd, WPARAM wParam);