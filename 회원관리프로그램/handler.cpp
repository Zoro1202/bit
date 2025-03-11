//handler.cpp
#include "std.h"

LRESULT OnCreate(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	con_printControls(hwnd);
	con_init(hwnd);
	//MessageBox(hwnd, TEXT("Create"), TEXT("����"), MB_OK);
	return 0;
}

LRESULT OnDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	//MessageBox(hwnd, TEXT("Destroy"), TEXT("����"), MB_OK);
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
	case IDC_SAVE: // �����ϱ� ��ư
	{
		con_insert(hwnd);
		break;
	}
	case IDC_LISTBTN: // ����Ʈ ��ü��� ��ư
	{
		con_printall(hwnd);
		break;
	}
	case IDC_LISTBOX: // ����Ʈ �� ��� ���� ��
	{
		con_select(hwnd);
		break;
	}
	}
	return 0;
}


