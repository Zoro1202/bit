#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (linker, "/subsystem:windows")
#include <tchar.h>
#include <WinSock2.h>
#pragma comment( lib, "ws2_32.lib")
#include <Windows.h>
#include <CommCtrl.h>

#include "resource.h"

#define FILE_PORT 5000
#define FILE_SERVER_MAINIP "192.168.0.139"
#define FILE_SERVER_MYIP "192.168.0.1"
#define FILENAME_DEFAULT "a.zip"
//file.h
struct FILE_INFO
{
	char FileName[260];
	int  size;
};

void file_dlg_open(HWND hdlg, char* buf);

FILE_INFO g_info;
//file
DWORD WINAPI FileClient( void* p )
{
	HWND hwnd = (HWND)p;
	WSADATA w;
	WSAStartup(MAKEWORD(2, 2), &w);

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(FILE_PORT);
	addr.sin_addr.s_addr = inet_addr(FILE_SERVER_MAINIP);

	if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		MessageBoxA(0, "Connect Error", "", MB_OK);
		return 0;
	}
	//------------------------------------------
	
	// 1. ȭ���� ��������� �����Ѵ�.
	FILE_INFO file_info;
	file_dlg_open(hwnd, file_info.FileName);
	send(s, (char*)&file_info, sizeof(file_info), 0);
	recv(s, (char*)&file_info, sizeof(file_info), 0);

	// �ֽ����忡 �˷��ش�. ->�ֽ����尡 UI�� Update �Ѵ�.!
	PostMessage(hwnd, WM_USER + 100, 0, (LPARAM)&file_info); // ���α׷��� ��
	//--------------------------------------------

	// 2. ���� ���� => ����
	HANDLE hFile = CreateFile(file_info.FileName, GENERIC_WRITE, FILE_SHARE_READ,
		0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	
	// 3. ���� ������ ���� => ���� ���� �۾� �ݺ�
	int total = file_info.size; // ������ ������ ��ü ũ��
	int current = 0;			// ���� ���ŵ� ������ ũ��
	char buf[4096];				// ���Ź��� ���� (4KB�� ����)
	while (total > current)
	{
		int nRecv = recv(s, buf, 4096, 0);
		if (nRecv <= 0) break;

		DWORD len;
		WriteFile(hFile, buf, nRecv, &len, 0);

		current += nRecv;
		
		PostMessage(hwnd, WM_USER + 200, (WPARAM)current, (LPARAM)nRecv);
	}
	//����ó��
	
	closesocket(s);
	CloseHandle(hFile);
	WSACleanup();
	return 0;
}

void file_recvfile(HWND hdlg)
{
	CloseHandle(CreateThread(0, 0, FileClient, (void*)hdlg, 0, 0));
}

//control
void con_recvFile(HWND hdlg)
{
	file_recvfile(hdlg);
}

void file_dlg_open(HWND hdlg, char* buf)
{

	OPENFILENAME ofn;              // ��ȭ���� ������ ��� ����ü
	TCHAR szFile[260] = FILENAME_DEFAULT;      // ���� ��θ� ������ ����

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lpstrTitle = (LPTSTR)TEXT("���� ����");// â ĸ��
	ofn.lStructSize = sizeof(ofn); // ������
	ofn.hwndOwner = hdlg;          //�θ� ������ �ڵ�
	ofn.lpstrFile = szFile;			// ���� ��ΰ� ����� ����
	ofn.nMaxFile = sizeof(szFile); // �� ������ ������
	ofn.lpstrFilter = TEXT("All\0*.*\0zip\0*.zip\0"); // ����
	ofn.nFilterIndex = 2; // �ʱ� ���� �ε���
	ofn.lpstrFileTitle = 0; // ��� ���� ����
	ofn.nMaxFileTitle = 0; // ���� ������
	ofn.lpstrInitialDir = NULL;    // �⺻ ���丮
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // OFN_PATHMUSTEXIST : ������ ��ΰ� ������ �����ؾ� �Ѵٴ� �� ������.
	//  OFN_FILEMUSTEXIST : ������ ���� ��ü�� �����ؾ� �Ѵ�.
   //	  �߸��� ��γ� ���� ���� ������ ����.
	if (GetOpenFileName(&ofn) == TRUE) {
		// ������ ���� ��δ� ofn.lpstrFile �� �����
		MessageBox(hdlg, ofn.lpstrFile, TEXT("����"), MB_OK);
		strcpy_s(buf, sizeof(buf), ofn.lpstrFile);
	}
}
HWND hPrg; HWND hList;

INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int file_size = 0;
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		hPrg = GetDlgItem(hdlg, IDC_PROGRESS1);

		hList = GetDlgItem(hdlg, IDC_LIST1);
		return TRUE;
	}
	case WM_USER+100:
	{
		FILE_INFO file_info = *(FILE_INFO*)lParam;
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"���� ����");
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"���� ����(����)");
		char fileinfo_buf[100];
		wsprintf(fileinfo_buf, "���ϸ� : %s, ���ϻ����� : %dbyte", file_info.FileName, file_info.size);
		SendMessage(hPrg, PBM_SETRANGE32, 0, file_info.size);
		file_size = file_info.size;
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)fileinfo_buf);
		return TRUE;
	}
	case WM_USER + 200:
	{
		int nRecv = lParam;
		int current = wParam;
		//listbox
		char temp[100];
		wsprintf(temp, "���ϵ����ͼ���(����/�ջ�/��ü) : %d / %d / %d", nRecv, current, file_size);
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)temp);
		SendMessage(hPrg, PBM_SETPOS, current, 0);
		if (current == file_size)	SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"�������� ����");
		return TRUE;
	}
	case WM_COMMAND: 
	{
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hdlg, IDCANCEL);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDOK)
		{
			con_recvFile(hdlg);
		}
	}
	}

	return FALSE;
}
//���� �Լ�
int WINAPI _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hprevInstance, _In_ LPTSTR cmdline, _In_ int showcmd)
{
	INT_PTR ret = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);

	return 0;
}
