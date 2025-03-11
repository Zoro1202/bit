//handler.cpp
#include "std.h"

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	con_printControls(hwnd);
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

	EndPaint(hwnd, &ps);
	return 0;
}

LRESULT OnCommand(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case IDC_DELBTN:
	{
		con_delete(hwnd);
		break;
	}
	case IDC_SAVE: // 저장하기 버튼
	{
		con_insert(hwnd);
		break;
	}
	case IDC_LISTBTN: // 리스트 전체출력 버튼
	{
		con_printall(hwnd);
		break;
	}
	case IDC_LISTBOX: // 리스트 내 요소 선택 시
	{
		con_select(hwnd);
		break;
	}
	}
	return 0;
}


