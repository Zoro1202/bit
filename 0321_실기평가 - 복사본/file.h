#pragma once

int file_load(vector<BOOK*>& books);

int file_save(vector<BOOK*>& books);

int file_load_filename(vector<BOOK*>& books, TCHAR* fname);

int file_save_filename(vector<BOOK*>& books, TCHAR* fname);

void file_dlg_open(HWND hdlg, vector<BOOK*>& books);

void file_dlg_save(HWND hdlg, vector<BOOK*>& books);
