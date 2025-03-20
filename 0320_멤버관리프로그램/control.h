#pragma once
//init----------
void con_init(HWND hdlg);
//file----------
void con_savefile(HWND hdlg);

void con_loadfile(HWND hdlg);
//file dialog----------
void con_fileOpenDial(HWND hdlg);

void con_fileSaveDial(HWND hdlg);
//modal----------
void con_InsertMember_Modal(HWND hdlg);

void con_selectMember_Modaless(HWND hdlg);

void con_OnChildDestroy(HWND hdlg);

void con_OnApply(HWND hdlg);
//default----------
void con_insertMember(HWND hdlg);

void con_login(HWND hdlg);

void con_selectMember(HWND hdlg);

void con_updateMember(HWND hdlg);

void con_deleteMember(HWND hdlg);
//util----------
MEMBER* checkLogin(HWND hdlg, TCHAR* id, TCHAR* pw);

MEMBER* checkid(HWND hdlg, TCHAR* id);

int checkid_idx(HWND hdlg, TCHAR* id);

