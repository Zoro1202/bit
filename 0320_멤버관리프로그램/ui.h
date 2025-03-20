
#pragma once

void ui_initControl(HWND hdlg);

void ui_getMemberData(HWND hdlg, TCHAR* id, int id_size, TCHAR* pw, int pw_size, TCHAR* name, int name_size, TCHAR* phone, int phone_size, int *age);

void ui_getLoginData(HWND hdlg, TCHAR* id, int idcountof, TCHAR* pw, int pwcountof);

void ui_getSelectData(HWND hdlg, TCHAR* id, int id_size);

void ui_getUpdateData(HWND hdlg, TCHAR* id, int id_size, TCHAR* phone, int phone_size, int* age);

void ui_setSelectMember(HWND hdlg, MEMBER* pmember);

void ui_printMember(HWND hdlg, vector<MEMBER*> pmember);
