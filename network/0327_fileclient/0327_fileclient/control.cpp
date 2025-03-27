//control.cpp
#include "std.h"

#define SERVER_IP_MY	"127.0.0.1"
#define SERVER_IP_MAIN	"192.168.0.139"		//cmd >> ipconfig
#define SERVER_PORT		9000

HWND g_hDlg;

void con_Init(HWND hDlg)
{
	g_hDlg = hDlg;

	ui_InitControl(hDlg);
}

void con_ServerConnect(HWND hDlg)
{
	if (net_initlibrary() == false)
	{
		printf("윈속 초기화 실패\n");
		//EndDialog(hDlg, IDCANCEL);
	}
	char ip[20];
	int port;
	ui_getIPPORT(hDlg, ip, &port);
	if (net_create_socket(ip, port) == false)
	{
		MessageBox(hDlg, TEXT("서버연결실패"), TEXT("알림"), MB_OK);
		//EndDialog(hDlg, IDCANCEL);
	}
}

void con_ServerDisConnect(HWND hDlg)
{
	net_delete_socket();
	net_exitlibrary();
	MessageBox(hDlg, TEXT("서버연결종료 성공"), TEXT("알림"), MB_OK);
}

void con_getFileList(HWND hDlg)
{
	try
	{
		FileListPack packet = pack_filelist();
		send_data((char*)&packet, sizeof(packet), 0);
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hDlg, msg, TEXT("filelist"), MB_OK);
	}
}

void con_listBoxClick(HWND hDlg)
{
	char filename[30];
	ui_getListText(hDlg, filename);
	ui_setEditBox(hDlg, filename);
}

void con_recvFile(HWND hDlg)
{
	try
	{
		/*ui_get*/
		char filename[30];
		ui_getFileName(hDlg, filename);
		FileDownloadPack packet = pack_filedown(filename);
		send_data((char*)&packet, sizeof(packet), 0);
		CloseHandle(CreateThread(0, 0, FileClient, (void*)hDlg, 0, 0));
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hDlg, msg, TEXT("filelist"), MB_OK);
	}
}

//---------- 응답함수들 -----------------------------------------------
void msg_parsing(char* buf)
{
	//파싱
	switch (*(int*)buf)
	{
	case PACKET_FILE_LIST_ACK:		list_file(true, (FileListAckPack*)buf);			break;
	case PACKET_FILE_DOWNLOAD_ACK:  down_file(g_hDlg); break;
	}
}

void list_file(bool flag, FileListAckPack* buf)
{
	if (flag == true)
	{
		ui_addFileListPrint(buf->filename, buf->count);
	}
	else
		MessageBox(NULL, TEXT("회원가입 실패"), TEXT("회원가입"), MB_OK);
}

void down_file(HWND hdlg)
{
	file_recvfile(hdlg);
}