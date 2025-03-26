#pragma once

void con_init(HWND hdlg);

void con_connect(HWND hdlg);

void con_exit(HWND hdlg);

void con_insertMember(HWND hdlg);

void con_selectMember(HWND hdlg);

void con_updateMember(HWND hdlg);

void con_deleteMember(HWND hdlg);

//test
void con_sendmessage(HWND hdlg);

void msg_parsing(HWND hdlg, char* buf);