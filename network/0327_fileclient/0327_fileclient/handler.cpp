//handler.cpp
#include "std.h"

INT_PTR OnInitDialog(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	con_Init(hDlg);
	return TRUE;
}

INT_PTR OnCommand(HWND hDlg, WPARAM wParam, LPARAM lParam)
{
	//���α׷� ����
	if (LOWORD(wParam) == IDCANCEL)
	{
		EndDialog(hDlg, IDCANCEL);
		return TRUE;
	}
	//���ϸ���Ʈ �ҷ�����
	else if (LOWORD(wParam) == IDC_BUTTON1)
	{
		con_getFileList(hDlg);
		return TRUE;
	}
	//���� ����
	else if (LOWORD(wParam) == IDC_BUTTON2)
	{
		con_ServerConnect(hDlg);
		return TRUE;
	}
	//���� ���� ����
	else if (LOWORD(wParam) == IDC_BUTTON3)
	{
		con_ServerDisConnect(hDlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON4)
	{
		con_recvFile(hDlg);
		
		return TRUE;
	}
	if (LOWORD(wParam) == IDC_LIST1 && HIWORD(wParam) == LBN_SELCHANGE) {
		con_listBoxClick(hDlg);
		return TRUE;
	}
	return FALSE;
}
