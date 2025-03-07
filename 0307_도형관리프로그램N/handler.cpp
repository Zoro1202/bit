//handler.cpp
#include "std.h"

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	con_init(hwnd);
	//MessageBox(hwnd, TEXT("Create"), TEXT("정보"), MB_OK);
	return 0;
}

LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//MessageBox(hwnd, TEXT("Destroy"), TEXT("정보"), MB_OK);
	PostQuitMessage(0);
	return 0;
}

LRESULT OnPaint(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);

	con_print(hwnd, hdc);

	EndPaint(hwnd, &ps);
	return 0;
}

LRESULT OnLButtonDown(HWND hwnd, LPARAM lParam)
{
	con_updateShapePoint(hwnd, lParam);
	con_shapeInsert(hwnd);
	return 0;
}

LRESULT OnKeyDown(HWND hwnd, WPARAM wParam)
{
	int key = (int)wParam;
	if (key == VK_UP || key == VK_DOWN) {
		con_updateShapeSize(hwnd, (int)wParam);
	}
	else if (key == '1' || key == '2'
		|| key == VK_NUMPAD1 || key == VK_NUMPAD2)
	{
		con_updateShapeType(hwnd, key);
	}
	else if (key == 'R' || key == 'G' || key == 'B')
	{
		con_updateShapeBrushColor(hwnd, key);
	}
	else if (key == VK_ESCAPE) {
		con_shapeDelete(hwnd);
	}
	else if (key == 'I')
	{
		con_shapeInfo(hwnd);
	}
	return 0;
}
