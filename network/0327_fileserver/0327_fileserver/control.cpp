//control.cpp
#include "std.h"

#define MAIN_SERVER_PORT		9000
#define DATA_SERVER_PORT		5000

char files[50][30];
SOCKET c_s;
void con_init()
{
	if (net_initlibrary() == false)
	{
		printf("윈속 초기화 실패\n");
		exit(-1);
	}
	if (net_create_socket(MAIN_SERVER_PORT) == false)
	{
		printf("소켓 생성 오류..\n");
		exit(-1);
	}
}

void con_exit()
{
	net_delete_socket();
	net_exitlibrary();
}

void con_server_start()
{
	printf("연결 대기.....................\n");
	HANDLE hthread = CreateThread(0, 0, listen_thread, 0, 0, 0);

	WaitForSingleObject(hthread, INFINITE);
	CloseHandle(hthread);
}

unsigned long __stdcall con_start_dataserver(void *p)
{
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(DATA_SERVER_PORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (SOCKADDR*)&addr, sizeof(addr)) == -1)
	{
		printf("Can't Bind\n");
		closesocket(s);
		return 0;
	}
	printf("Bind\n");

	if (listen(s, 10) == -1)
	{
		printf("Can't Listen\n");
		closesocket(s);
		return 0;
	}
	printf("Listen\n");

	SOCKADDR_IN c_addr;
	int size = sizeof(c_addr);

	printf("Client 접속 대기중.........\n");
	c_s = accept(s, (SOCKADDR*)&c_addr, &size);
	printf("Client 접속 : %s\n", inet_ntoa(c_addr.sin_addr));
	HANDLE h = CreateThread(0, 0, FileServer, (void*)c_s, 0, 0);
	WaitForSingleObject(h, INFINITE);
	//--------------------------------------------
	CloseHandle(h);
	closesocket(s);
	return 1;
}

//---------------- 기능 ------------------------------------
int con_msg_parsing(char* buf)
{
	//파싱
	int* flag = (int*)buf;
	switch (*flag)
	{
	case PACKET_FILE_LIST:		return list_file((FileListPack*)buf);
	case PACKET_FILE_DOWNLOAD:  return down_file((FileDownloadPack*)buf);
	}
	return 0;
}

int list_file(FileListPack* packet)
{
	int size;
	int ret = file_list(files, &size);
	//response 처리
	FileListAckPack ack = pack_filelist(files, size);
	memcpy_s(packet, sizeof(FileListAckPack), (char*)&ack, sizeof(FileListAckPack));
	return sizeof(FileListAckPack);
}

int down_file(FileDownloadPack* packet)
{
	char * filename = packet->filename;
	Initfilename(filename);
	FileDownloadPackAck ack;
	strcpy_s(ack.filename, sizeof(ack.filename), filename);
	printf("파일 다운로드 요청을 받음....\n");
	CloseHandle(CreateThread(0, 0, con_start_dataserver, 0, 0, 0));

	return sizeof(FileListAckPack);
}