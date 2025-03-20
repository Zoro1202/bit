#pragma once

int file_load(vector<MEMBER*>& members);

int file_save(vector<MEMBER*>& members);

int file_load_filename(vector<MEMBER*>& members, TCHAR* fname);

int file_save_filename(vector<MEMBER*>& members, TCHAR* fname);

void file_dlg_open(HWND hdlg, vector<MEMBER*>& members);

void file_dlg_save(HWND hdlg, vector<MEMBER*>& members);
