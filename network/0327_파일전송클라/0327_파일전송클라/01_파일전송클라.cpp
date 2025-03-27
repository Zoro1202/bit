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
	
	// 1. 화일의 헤더정보를 수신한다.
	FILE_INFO file_info;
	file_dlg_open(hwnd, file_info.FileName);
	send(s, (char*)&file_info, sizeof(file_info), 0);
	recv(s, (char*)&file_info, sizeof(file_info), 0);

	// 주스레드에 알려준다. ->주스레드가 UI를 Update 한다.!
	PostMessage(hwnd, WM_USER + 100, 0, (LPARAM)&file_info); // 프로그래스 바
	//--------------------------------------------

	// 2. 파일 오픈 => 쓰기
	HANDLE hFile = CreateFile(file_info.FileName, GENERIC_WRITE, FILE_SHARE_READ,
		0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	
	// 3. 파일 데이터 수신 => 파일 쓰기 작업 반복
	int total = file_info.size; // 수신할 파일의 전체 크기
	int current = 0;			// 현재 수신된 파일의 크기
	char buf[4096];				// 수신받을 버퍼 (4KB씩 읽음)
	while (total > current)
	{
		int nRecv = recv(s, buf, 4096, 0);
		if (nRecv <= 0) break;

		DWORD len;
		WriteFile(hFile, buf, nRecv, &len, 0);

		current += nRecv;
		
		PostMessage(hwnd, WM_USER + 200, (WPARAM)current, (LPARAM)nRecv);
	}
	//종료처리
	
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

	OPENFILENAME ofn;              // 대화상자 정보를 담는 구조체
	TCHAR szFile[260] = FILENAME_DEFAULT;      // 파일 경로를 저장할 버퍼

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lpstrTitle = (LPTSTR)TEXT("파일 열기");// 창 캡션
	ofn.lStructSize = sizeof(ofn); // 사이즈
	ofn.hwndOwner = hdlg;          //부모 윈도우 핸들
	ofn.lpstrFile = szFile;			// 파일 경로가 저장될 버퍼
	ofn.nMaxFile = sizeof(szFile); // 위 버퍼의 사이즈
	ofn.lpstrFilter = TEXT("All\0*.*\0zip\0*.zip\0"); // 필터
	ofn.nFilterIndex = 2; // 초기 필터 인덱스
	ofn.lpstrFileTitle = 0; // 경로 없는 버퍼
	ofn.nMaxFileTitle = 0; // 버퍼 사이즈
	ofn.lpstrInitialDir = NULL;    // 기본 디렉토리
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // OFN_PATHMUSTEXIST : 지정한 경로가 실제로 존재해야 한다는 걸 강제함.
	//  OFN_FILEMUSTEXIST : 선택한 파일 자체가 존재해야 한다.
   //	  잘못된 경로나 없는 파일 선택을 막기.
	if (GetOpenFileName(&ofn) == TRUE) {
		// 선택한 파일 경로는 ofn.lpstrFile 에 저장됨
		MessageBox(hdlg, ofn.lpstrFile, TEXT("파일"), MB_OK);
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
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"서버 연결");
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"파일 열기(쓰기)");
		char fileinfo_buf[100];
		wsprintf(fileinfo_buf, "파일명 : %s, 파일사이즈 : %dbyte", file_info.FileName, file_info.size);
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
		wsprintf(temp, "파일데이터수신(현재/합산/전체) : %d / %d / %d", nRecv, current, file_size);
		SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)temp);
		SendMessage(hPrg, PBM_SETPOS, current, 0);
		if (current == file_size)	SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)"파일전송 성공");
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
//시작 함수
int WINAPI _tWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hprevInstance, _In_ LPTSTR cmdline, _In_ int showcmd)
{
	INT_PTR ret = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);

	return 0;
}
