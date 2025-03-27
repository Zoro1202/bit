//ui.cpp
#include "std.h"

HWND hList;

void ui_InitControl(HWND hDlg)
{
	hList = GetDlgItem(hDlg, IDC_LIST1);
	SetDlgItemText(hDlg, IDC_IPADDRESS1, TEXT("192.168.0.139"));
	SetDlgItemText(hDlg, IDC_EDIT2, TEXT("9000"));
}

void ui_getIPPORT(HWND hDlg, char* ip, int* port)
{
	GetDlgItemTextA(hDlg, IDC_IPADDRESS1, ip, strlen(ip));
	*port = GetDlgItemInt(hDlg, IDC_EDIT2, 0, 0);
}

void ui_addFileListPrint(char(*files)[30], int size)
{
	SendMessage(hList, LB_RESETCONTENT, 0, 0);
	for (int i = 0; i < size; i++)
	{
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)files[i]);
	}
}

void ui_getListText(HWND hDlg, char* filename)
{
	int index = SendMessage(hList, LB_GETCURSEL, 0, 0);
	if (index != LB_ERR) {
		TCHAR buffer[30];
		SendMessage(hList, LB_GETTEXT, index, (LPARAM)buffer);
		strcpy_s(filename, sizeof(buffer), buffer);
	}
}

void ui_setEditBox(HWND hDlg, char* filename)
{
	SetDlgItemText(hDlg, IDC_EDIT3, filename);
}

void ui_getFileName(HWND hDlg, char* filename)
{
	GetDlgItemText(hDlg, IDC_EDIT3, filename, strlen(filename));
}