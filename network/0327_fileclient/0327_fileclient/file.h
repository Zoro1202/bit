#pragma once
//file.h
typedef struct tagFILE_INFO
{
	char FileName[260];
	int  size;
}FILE_INFO;

DWORD __stdcall FileClient(void* p);

void file_recvfile(HWND hdlg);
