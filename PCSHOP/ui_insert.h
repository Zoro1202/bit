//ui_insert.h
#pragma once

void ui_insert_init(HWND hdlg);



void ui_insert_combo1Update(HWND hdlg, vector<ITEM>& items);
int ui_insert_getcombo2idx(HWND hdlg, vector<ITEM>& items);

void ui_listbox_add(HWND hdlg, ITEM item);
