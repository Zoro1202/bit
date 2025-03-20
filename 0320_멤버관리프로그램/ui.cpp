#include "std.h"

HWND hList;

void ui_initControl(HWND hdlg)
{
	//InitCommonControls();

	hList = GetDlgItem(hdlg, IDC_LIST2);

	LVCOLUMN COL;
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 150;
	
	COL.pszText = (LPTSTR)TEXT("아이디");
	COL.iSubItem = 0;
	SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = (LPTSTR)TEXT("패스워드");
	COL.iSubItem = 1;
	SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.pszText = (LPTSTR)TEXT("이름");
	COL.iSubItem = 2;
	SendMessage(hList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	COL.pszText = (LPTSTR)TEXT("전화번호");
	COL.iSubItem = 3;
	SendMessage(hList, LVM_INSERTCOLUMN, 3, (LPARAM)&COL);

	COL.pszText = (LPTSTR)TEXT("나이");
	COL.iSubItem = 4;
	SendMessage(hList, LVM_INSERTCOLUMN, 4, (LPARAM)&COL);

	ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
}

void ui_getMemberData(HWND hdlg, TCHAR* id, int id_size, TCHAR* pw, int pw_size, TCHAR* name, int name_size, TCHAR* phone, int phone_size, int *age)
{
	GetDlgItemText(hdlg, IDC_EDIT1, id, id_size);
	GetDlgItemText(hdlg, IDC_EDIT2, pw, pw_size);
	GetDlgItemText(hdlg, IDC_EDIT3, name, name_size);
	GetDlgItemText(hdlg, IDC_EDIT4, phone, phone_size);
	*age = GetDlgItemInt(hdlg, IDC_EDIT5, 0, 0);
}

void ui_getLoginData(HWND hdlg, TCHAR* id, int id_size, TCHAR* pw, int pw_size)
{
	GetDlgItemText(hdlg, IDC_EDIT6, id, id_size);
	GetDlgItemText(hdlg, IDC_EDIT7, pw, pw_size);
}

void ui_getSelectData(HWND hdlg, TCHAR* id, int id_size)
{
	GetDlgItemText(hdlg, IDC_EDIT8, id, id_size);
}

void ui_getUpdateData(HWND hdlg, TCHAR* id, int id_size, TCHAR* phone, int phone_size, int *age)
{
	GetDlgItemText(hdlg, IDC_EDIT8, id, id_size);
	GetDlgItemText(hdlg, IDC_EDIT11, phone, phone_size);
	*age = GetDlgItemInt(hdlg, IDC_EDIT12, 0, 0);
}

void ui_setSelectMember(HWND hdlg, MEMBER* pmember)
{
	//SetDlgItemText(hdlg, IDC_EDIT8, pmember->id);
	SetDlgItemText(hdlg, IDC_EDIT9, pmember->pw);
	SetDlgItemText(hdlg, IDC_EDIT10, pmember->name);
	SetDlgItemText(hdlg, IDC_EDIT11, pmember->phone);
	SetDlgItemInt(hdlg, IDC_EDIT12, pmember->age, 0);
}

void ui_printMember(HWND hdlg, vector<MEMBER*> pmember)
{
	SendMessage(hList, LVM_DELETEALLITEMS, 0, 0);
	LVITEM LI;
	for (int i = 0; i < pmember.size(); i++) {
		LI.mask = LVIF_TEXT | LVIF_IMAGE;
		LI.iItem = i;
		LI.iSubItem = 0;
		LI.pszText = pmember[i]->id;
		LI.iImage = 1;
		SendMessage(hList, LVM_INSERTITEM, i, (WPARAM)&LI);
		//ListView_InsertItem(hList, &LI);

		//SendMessage(hList, LVM_SETITEM, i, (WPARAM)pmember[i]->pw);
		ListView_SetItemText(hList, i, 1, pmember[i]->pw);
		ListView_SetItemText(hList, i, 2, pmember[i]->name);
		ListView_SetItemText(hList, i, 3, pmember[i]->phone);
		TCHAR age[20]; wsprintf(age, TEXT("%d"), pmember[i]->age);
		ListView_SetItemText(hList, i, 4, age);
	}
}