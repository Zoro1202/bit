#include "std.h"

vector<BOOK*> books;

HWND hList;
//초기화
void con_init(HWND hdlg)
{

	hList = GetDlgItem(hdlg, IDC_LIST1);

	LVCOLUMN COL;
	COL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	COL.fmt = LVCFMT_LEFT;
	COL.cx = 150;

	COL.pszText = (LPTSTR)TEXT("타이틀");
	COL.iSubItem = 0;
	SendMessage(hList, LVM_INSERTCOLUMN, 0, (LPARAM)&COL);

	COL.pszText = (LPTSTR)TEXT("가격");
	COL.iSubItem = 1;
	SendMessage(hList, LVM_INSERTCOLUMN, 1, (LPARAM)&COL);

	COL.pszText = (LPTSTR)TEXT("저자");
	COL.iSubItem = 2;
	SendMessage(hList, LVM_INSERTCOLUMN, 2, (LPARAM)&COL);

	ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
}
//file
void con_savefile(HWND hdlg)
{
	file_save(books);
}
void con_loadfile(HWND hdlg)
{
	file_load(books);
	con_printBooks(hdlg);
}

void con_printBooks(HWND hdlg)
{
	SendMessage(hList, LVM_DELETEALLITEMS, 0, 0);
	LVITEM LI;
	for (int i = 0; i < books.size(); i++) {
		LI.mask = LVIF_TEXT | LVIF_IMAGE;
		LI.iItem = i;
		LI.iSubItem = 0;
		LI.pszText = books[i]->title;
		LI.iImage = 1;
		SendMessage(hList, LVM_INSERTITEM, i, (WPARAM)&LI);
		//ListView_InsertItem(hList, &LI);

		//SendMessage(hList, LVM_SETITEM, i, (WPARAM)pmember[i]->pw);
		TCHAR age[20]; wsprintf(age, TEXT("%d"), books[i]->price);
		ListView_SetItemText(hList, i, 1, age);
		ListView_SetItemText(hList, i, 2, books[i]->author);
	}
}

void con_insertBook(HWND hdlg)
{
	TCHAR title[30], author[30];
	int price;
	GetDlgItemText(hdlg, IDC_EDIT1, title, _countof(title));
	price = GetDlgItemInt(hdlg, IDC_EDIT2, 0, 0);
	GetDlgItemText(hdlg, IDC_EDIT3, author, _countof(author));


	BOOK* pb = book_createBook(title, price, author);
	books.push_back(pb);
	con_printBooks(hdlg);
}

void con_updateBook(HWND hdlg)
{
	TCHAR title[30], author[30];
	int price;
	try
	{
		GetDlgItemText(hdlg, IDC_EDIT4, title, _countof(title));
		price = GetDlgItemInt(hdlg, IDC_EDIT5, 0, 0);
		GetDlgItemText(hdlg, IDC_EDIT6, author, _countof(author));
		BOOK* pbook = checktitle(hdlg, title);
		MessageBox(hdlg, TEXT("성공"), TEXT("update"), MB_OK);
		book_setData(pbook, price, pbook->author);
		//print book
		con_printBooks(hdlg);
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hdlg, msg, TEXT("update"), MB_OK);
	}
}

void con_selectBook(HWND hdlg)
{
	TCHAR title[20];
	try
	{
		GetDlgItemText(hdlg, IDC_EDIT8, title, _countof(title));
		int i = checktitle_idx(hdlg, title);

		BOOK* pbook = checktitle(hdlg, title);
		BOOK* pbook1 = checktitle(hdlg, title);

		SetDlgItemInt(hdlg, IDC_EDIT9, pbook->price, 0);
		SetDlgItemText(hdlg, IDC_EDIT10, pbook->author);

		MessageBox(hdlg, TEXT("성공"), TEXT("select"), MB_OK);
		
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hdlg, msg, TEXT("select"), MB_OK);
	}
}

void con_deleteBook(HWND hdlg)
{
	TCHAR title[20];
	try
	{
		GetDlgItemText(hdlg, IDC_EDIT7, title, _countof(title));
		int i = checktitle_idx(hdlg, title);
		MessageBox(hdlg, TEXT("성공"), TEXT("delete"), MB_OK);
		free(books[i]);
		books.erase(books.begin() + i);
		//print
		con_printBooks(hdlg);
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hdlg, msg, TEXT("delete"), MB_OK);
	}
}

//id check to member
BOOK* checktitle(HWND hdlg, TCHAR* title)
{
	for (int i = 0; i < books.size(); i++)
	{
		BOOK* pbook = books[i];
		if (_tcscmp(pbook->title, title) == 0)
		{
			return pbook;
		}
	}
	throw TEXT("title 불일치");
}
//id check to idx
int checktitle_idx(HWND hdlg, TCHAR* title)
{
	for (int i = 0; i < books.size(); i++)
	{
		BOOK* pbook = books[i];
		if (_tcscmp(pbook->title, title) == 0)
		{
			return i;
		}
	}
	throw TEXT("title 불일치");
}