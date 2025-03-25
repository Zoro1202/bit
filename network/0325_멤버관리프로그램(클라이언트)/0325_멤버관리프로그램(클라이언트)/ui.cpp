#include "std.h"

MEMBER ui_getDatafromDlg(HWND hdlg)
{
	MEMBER mem;
	GetDlgItemTextA(hdlg, IDC_EDIT1, mem.name, strlen(mem.name));
	GetDlgItemTextA(hdlg, IDC_EDIT2, mem.phone, strlen(mem.phone));
	mem.age = GetDlgItemInt(hdlg, IDC_EDIT3, 0, 0);
	return mem;
}

void ui_getname(HWND hdlg, char* name)
{
	GetDlgItemTextA(hdlg, IDC_EDIT4, name, strlen(name));
}

void ui_getipport(HWND hdlg, char* ip, int* port)
{
	GetDlgItemTextA(hdlg, IDC_EDITIP, ip, strlen(ip));
	*port = GetDlgItemInt(hdlg, IDC_EDITPORT, 0, 0);
}

void ui_setDatatoDlg(HWND hdlg)
{
	char name[20] = {0}; // 서버에서 가져올 예정
	char phone[20] = {0}; // 서버에서 가져올 예정
	int age = 0; // 서버에서 가져올 예정
	SetDlgItemTextA(hdlg, IDC_EDIT4, name);
	SetDlgItemTextA(hdlg, IDC_EDIT5, phone);
	SetDlgItemInt(hdlg, IDC_EDIT6, age, 0);
}