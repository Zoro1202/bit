#include "std.h"

#define DATA_SERVER_PORT		5000
#define FILE_SERVER_MAINIP	"192.168.0.139"
FILE_INFO g_info;
//file
DWORD WINAPI FileClient(void* p)
{
	HWND hwnd = (HWND)p;
	//WSADATA w;
	//WSAStartup(MAKEWORD(2, 2), &w);

	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(DATA_SERVER_PORT);
	addr.sin_addr.s_addr = inet_addr(FILE_SERVER_MAINIP);

	if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		MessageBoxA(0, "Connect Error", "", MB_OK);
		return 0;
	}
	//------------------------------------------

	// 1. ȭ���� ��������� �����Ѵ�.
	FILE_INFO file_info;
	recv(s, (char*)&file_info, sizeof(file_info), 0);

	
	HWND hPrg = GetDlgItem(hwnd, IDC_PROGRESS1);
	SendMessage(hPrg, PBM_SETRANGE32, 0, file_info.size);
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

		SendMessage(hPrg, PBM_SETPOS, current, 0);
	}
	//����ó��
	if(total == current)MessageBox(0, "�������� ����!", "â", MB_OK);
	else MessageBox(0, "�������� ����!", "â", MB_OK | MB_ICONWARNING);
	closesocket(s);
	CloseHandle(hFile);
	//WSACleanup();
	return 0;
}

void file_recvfile(HWND hdlg)
{
	CloseHandle(CreateThread(0, 0, FileClient, (void*)hdlg, 0, 0));
}
