//control.cpp
#include "std.h"
#include "modal.h"

ITEM g_curitem;
vector<ITEM> g_items;
vector<ITEM> g_myitem;

void con_init(HWND hdlg)
{
//0 9950X3D	1340700		16core 4.3GHz AMD
//0 14900KS	1078010		24core 3.2GHz INTEL
//0 285K		995500		24core 3.7GHz INTEL
//1 SN850X	89910		1TB WD
//1 P41		292120		1TB SK
//1 990PRO	185350		1TB SAMSUNG
//2 H100		46440000	NVIDIA
//2 RTX5080	2578000		COLORFUL
////2 RTX5070TI	1426000		MSI
//	ITEM item;
//	//초기 세팅 // 나중에 파일로 불러올 데이타
//	item_setItem(&item, 1, 0, TEXT("9950X3D"), 1340700, TEXT("16core 4.3GHz AMD")); g_items.push_back(item);
//	item_setItem(&item, 2, 0, TEXT("14900KS"), 1078010, TEXT("24core 3.2GHz INTEL")); g_items.push_back(item);
//	item_setItem(&item, 3, 0, TEXT("285K"), 995500, TEXT("24core 3.7GHz INTEL")); g_items.push_back(item);
//	item_setItem(&item, 3, 0, TEXT("asd5K"), 900, TEXT("2asdf")); g_items.push_back(item);
//
//	item_setItem(&item, 4, 1, TEXT("SN850X"), 89910, TEXT("1TB WD")); g_items.push_back(item);
//	item_setItem(&item, 5, 1, TEXT("P41"), 292120, TEXT("1TB SK")); g_items.push_back(item);
//	item_setItem(&item, 6, 1, TEXT("990PRO"), 185350, TEXT("1TB SAMSUNG")); g_items.push_back(item);
//
//	item_setItem(&item, 7, 2, TEXT("H100"), 46440000, TEXT("NVIDIA")); g_items.push_back(item);
//	item_setItem(&item, 8, 2, TEXT("RTX5080"), 2578000, TEXT("COLORFUL")); g_items.push_back(item);
//	item_setItem(&item, 9, 2, TEXT("RTX5070TI"), 1426000, TEXT("MSI")); g_items.push_back(item);

	file_load(g_items);

	//-----------COMBOBOX INIT----------------
	ui_insert_init(hdlg);
	//ui_insert_combo1Update(hdlg, ui_insert_getcurItem(), g_items);
}

void con_insert(HWND hdlg)
{
	if(g_curitem.name == NULL) { MessageBox(hdlg, TEXT("오류!"), TEXT("Warning!"), MB_OK); return; }
	ui_listbox_add(hdlg, g_curitem);
	for (int i = 0; i < g_items.size(); i++)
		if (memcmp(&g_curitem, &g_items[i], sizeof(ITEM)) == 0)
			g_myitem.push_back(g_items[i]);
}

void con_modal(HWND hdlg)
{
	INT_PTR ret = DialogBoxParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2), hdlg, ModalProc, (LPARAM)&g_myitem);
	if (ret == IDOK)
	{
		//g_data = tempdata;
		//InvalidateRect(hdlg, 0, TRUE);
	}
}

void con_updateCombo1(HWND hdlg)
{
	ui_insert_combo1Update(hdlg, g_items);
}
void con_updateCombo2(HWND hdlg)
{
	int idx = ui_insert_getcombo2idx(hdlg, g_items);
	if (idx == -1) { MessageBox(hdlg, TEXT("오류!"), TEXT("Warning!"), MB_OK); return; }
	if (idx == -2) { return; }
	g_curitem = g_items[idx];
}

