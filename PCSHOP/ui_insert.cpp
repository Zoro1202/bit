//ui_insert.cpp
#include "std.h"

HWND hCom1, hCom2, hBtn1;
HWND hList1;
HWND hToolTip;
INITCOMMONCONTROLSEX icex;
TOOLINFO ti = { 0 };

void ui_insert_init(HWND hdlg)
{
	hCom1 = GetDlgItem(hdlg, IDC_COMBO1);
	hCom2 = GetDlgItem(hdlg, IDC_COMBO2);
	hBtn1 = GetDlgItem(hdlg, IDC_BUTTON1);
	hList1 = GetDlgItem(hdlg, IDC_LIST1);
	SendMessage(hCom1, CB_ADDSTRING, 0, (LPARAM)TEXT("CPU"));
	SendMessage(hCom1, CB_ADDSTRING, 0, (LPARAM)TEXT("SSD"));
	SendMessage(hCom1, CB_ADDSTRING, 0, (LPARAM)TEXT("VGA"));
	SendMessage(hCom1, CB_SETCURSEL, 0, 0);


	//------------------¹ú·é-------------------
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icex);

	// ÅøÆÁ »ý¼º
	hToolTip = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL, TTS_BALLOON,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		hdlg, NULL, GetModuleHandle(NULL), NULL);
	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_TRACK | TTF_ABSOLUTE;
	ti.hwnd = hdlg;
	ti.hinst = GetModuleHandle(NULL);
	static TCHAR buf_tool[20] = TEXT("toolTip");
	ti.lpszText = buf_tool; // ÀÌ°Ô ÅøÆÁ

	//SendMessage(hToolTip, TTM_ADDTOOL, 0, (LPARAM)&ti);

}

void ui_insert_combo1Update(HWND hdlg, vector<ITEM>& items)
{
	int id = 0;
	int type = (int)SendMessage(hCom1, CB_GETCURSEL, 0, 0);
	SendMessage(hCom2, CB_RESETCONTENT, 0, 0);
	for (int i = 0; i < items.size(); i++)
	{
		if (type == items[i].type) 
		{
			SendMessage(hCom2, CB_ADDSTRING, 0, (LPARAM)items[i].name);
			items[i].id = id;
			id++;
		}
	}
}

int ui_insert_getcombo2idx(HWND hdlg, vector<ITEM>& items)
{
	int type = (int)SendMessage(hCom1, CB_GETCURSEL, 0, 0);
	int idx = (int)SendMessage(hCom2, CB_GETCURSEL, 0, 0);
	if (idx == -1) { return -2; }
	TCHAR name[20];
	SendMessage(hCom2, CB_GETLBTEXT, idx, (LPARAM)name);
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].id == idx && lstrcmp(items[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;
}

void ui_listbox_add(HWND hdlg, ITEM item)
{
	TCHAR str[100];
	wsprintf(str, TEXT("%-15s %-20d %50s"), item.name, item.price, item.spec);
	SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)str);
}
