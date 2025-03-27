//control.h
#pragma once

void con_Init(HWND hDlg);

//버튼 이벤트
//WM_INITDIALOG, WM_COMMAND(IDC_CANCEL)
void con_ServerConnect(HWND hDlg);
void con_ServerDisConnect(HWND hDlg);

void con_getFileList(HWND hDlg);

void con_listBoxClick(HWND hDlg);

void con_recvFile(HWND hdlg);

void msg_parsing(char* buf);

void list_file(bool flag, FileListAckPack* buf);

void down_file(HWND hdlg);
