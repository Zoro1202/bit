#pragma once

MEMBER ui_getAddDatafromDlg(HWND hdlg);

MEMBER ui_getUpdateDatafromDlg(HWND hdlg);

void ui_getSelectNamefromDlg(HWND hdlg, char* name);

void ui_getDeleteNamefromDlg(HWND hdlg, char* name);

void ui_getipport(HWND hdlg, char* ip, int* port);

void ui_setUpdateData(HWND hdlg, char* name, char* phone, int age);
