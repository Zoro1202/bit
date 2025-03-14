//modal.cpp
#include"modal.h"


INT_PTR CALLBACK ModalProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static vector<ITEM> *myItems;
	static HWND hList;
	static HWND hEdit;
	//static DATA* tempdata = NULL;
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		int totalprice = 0;
		myItems = (vector<ITEM>*)lParam;

		hList = GetDlgItem(hdlg, IDC_LIST2);
		TCHAR buf[128];
		for (vector<ITEM>::iterator iter = myItems->begin(); iter != myItems->end();)
		{
			totalprice += iter->price;
			ITEM item = *iter;
			wsprintf(buf, TEXT("%d %s %d %s"),
				item.type,
				item.name,
				item.price, 
				item.spec);
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buf);
			++iter;
		}
		SetDlgItemInt(hdlg, IDC_EDIT1, (WPARAM)totalprice, 0);
		return TRUE;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
		{
			EndDialog(hdlg, IDCANCEL);
			return TRUE;
		}
		}
	}
	}

	return FALSE;
}