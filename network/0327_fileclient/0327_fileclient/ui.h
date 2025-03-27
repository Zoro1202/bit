//ui.h
#pragma once

void ui_InitControl(HWND hDlg);

void ui_getIPPORT(HWND hDlg, char* ip, int* port);

void ui_addFileListPrint(char(*files)[30], int size);

void ui_getListText(HWND hDlg,char* filename);

void ui_setEditBox(HWND hDlg, char* filename);

void ui_getFileName(HWND hDlg, char* filename);
