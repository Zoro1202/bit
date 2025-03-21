#pragma once

void con_init(HWND hdlg);

void con_savefile(HWND hdlg);

void con_loadfile(HWND hdlg);

void con_printBooks(HWND hdlg);

void con_insertBook(HWND hdlg);

void con_updateBook(HWND hdlg);

void con_selectBook(HWND hdlg);

void con_deleteBook(HWND hdlg);

BOOK* checktitle(HWND hdlg, TCHAR* title);

int checktitle_idx(HWND hdlg, TCHAR* title);
