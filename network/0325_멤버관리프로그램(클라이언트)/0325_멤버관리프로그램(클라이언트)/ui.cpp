#include "std.h"

MEMBER ui_getAddDatafromDlg(HWND hdlg)
{
	MEMBER mem;
	GetDlgItemTextA(hdlg, IDC_EDIT1, mem.name, strlen(mem.name));
	GetDlgItemTextA(hdlg, IDC_EDIT2, mem.phone, strlen(mem.phone));
	mem.age = GetDlgItemInt(hdlg, IDC_EDIT3, 0, 0);
	return mem;
}

MEMBER ui_getUpdateDatafromDlg(HWND hdlg)
{
	MEMBER mem;
	GetDlgItemTextA(hdlg, IDC_EDIT10, mem.name, strlen(mem.name));
	GetDlgItemTextA(hdlg, IDC_EDIT11, mem.phone, strlen(mem.phone));
	mem.age = GetDlgItemInt(hdlg, IDC_EDIT12, 0, 0);
	return mem;
}

void ui_getSelectNamefromDlg(HWND hdlg, char* name)
{
	GetDlgItemTextA(hdlg, IDC_EDIT4, name, strlen(name));
}

void ui_getDeleteNamefromDlg(HWND hdlg, char* name)
{
	GetDlgItemTextA(hdlg, IDC_EDIT7, name, strlen(name));
}

void ui_getipport(HWND hdlg, char* ip, int* port)
{
	GetDlgItemTextA(hdlg, IDC_EDITIP, ip, strlen(ip));
	*port = GetDlgItemInt(hdlg, IDC_EDITPORT, 0, 0);
}

void ui_setUpdateData(HWND hdlg, char* name, char* phone, int age)
{
	SetDlgItemTextA(hdlg, IDC_EDIT4, name);
	SetDlgItemTextA(hdlg, IDC_EDIT5, phone);
	SetDlgItemInt(hdlg, IDC_EDIT6, age, 0);
}