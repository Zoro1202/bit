//net.cpp
#include "std.h"

SOCKET listen_sock;
vector<SOCKET> sockets;

bool net_initlibrary()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return false;
	else
		return true;
}

void net_exitlibrary()
{
	WSACleanup();
}

bool net_create_socket(int port)
{
	listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listen_sock == INVALID_SOCKET)
	{
		printf("socket() 생성 오류\n");
		return false;
	}

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY); //사용 가능한 IP가 할당됨.
	addr.sin_port = htons(port);

	int ret = bind(listen_sock, (SOCKADDR*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		printf("bind() 실패\n");
		return false;
	}

	ret = listen(listen_sock, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		printf("listen() 실패\n");
		return false;
	}

	return true;
}

void net_delete_socket()
{
	closesocket(listen_sock);
}

unsigned long __stdcall listen_thread(void* p)
{
	SOCKADDR_IN client_addr;
	int client_length = sizeof(SOCKADDR_IN);

	while (true)
	{
		memset(&client_addr, 0, sizeof(SOCKADDR_IN));
		SOCKET client_socket = accept(listen_sock, (SOCKADDR*)&client_addr, &client_length);
		if (client_socket == INVALID_SOCKET)
		{
			printf("연결 실패\n");
			continue;  //반복문의 마지막으로 강제 이동!
		}
		printf("클라이언트 연결 : (%s:%d)\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

		sockets.push_back(client_socket);

		DWORD tid;
		HANDLE htread = CreateThread(0, 0, work_thread, (void*)client_socket, 0, &tid);
		CloseHandle(htread);
	}
	return 0;
}

unsigned long __stdcall work_thread(void* p)
{
	SOCKET client_socket = (SOCKET)p;
	char buf[4096];

	while (true)
	{
		memset(buf, 0, sizeof(buf));
		int recv_byte = recv_data(client_socket, buf, sizeof(buf), 0);
		if (recv_byte == -1)
		{
			printf("오류-상대방 프로그램이 강제 종료\n");
			break;
		}
		else if (recv_byte == 0)
		{
			printf("상대방이 closesocket() 연결 종료\n");
			break;
		}
		else
		{
			//printf("	[수신 byte] %dbyte, %s\n", recv_byte, buf);

			int size = con_msg_parsing(buf);

			int send_byte = send_data(client_socket, buf, size, 0);
			printf("	[송신] ");
			/*
			for (int i = 0; i < sockets.size(); i++)
			{
				SOCKET s = sockets[i];
				int send_byte = send_data(s, buf, (int)(strlen(buf) + 1), 0);
				printf("	[송신] ");
			}
			*/
			printf("\n\n");
		}
	}

	//getsockname, getpeername
	SOCKADDR_IN client_addr;
	int client_length = sizeof(SOCKADDR_IN);
	getpeername(client_socket, (SOCKADDR*)&client_addr, &client_length);
	printf("클라이언트 종료 : (%s:%d)\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

	closesocket(client_socket);

	for (int i = 0; i < sockets.size(); i++)
	{
		SOCKET s = sockets[i];
		if (s == client_socket)
		{
			sockets.erase(sockets.begin() + i);
			break;
		}
	}

	return 0;
}


char filename[260] = "C:\\00_myfile\\a.zip"; // 전송할 파일

struct FILE_INFO
{
	char FileName[260]; // 전송할 파일 이름.
	int  size;			// 화일 크기
};

void Initfilename(char* _filename)
{
	strcpy_s(filename, sizeof(filename), _filename);
}

DWORD WINAPI FileServer(void* p)
{
	SOCKET s = (SOCKET)p;

	FILE_INFO fi;
	strcpy_s(fi.FileName, sizeof(fi.FileName), filename);
	// 전송할 파일Open
		//FILE *f = fopen("test.txt", "r");  --> CreateFile() 함수 호출
	char realfilename[265];
	sprintf_s(realfilename, "C:\\00_myfile\\%s", fi.FileName);
	HANDLE hFile = CreateFile(realfilename, GENERIC_READ, FILE_SHARE_READ,
		0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Can't Open File\n");
		closesocket(s);
		return 0;
	}
	printf("Open!!\n");
	// 크기를 구하고 화일의 정보를 전송한다.
	DWORD size1;
	DWORD size2 = GetFileSize(hFile, &size1);

	strcpy_s(fi.FileName, sizeof(fi.FileName), filename);
	fi.size = size2;

	send(s, (char*)&fi, sizeof(fi), 0);
	//-------------------------------------------------
	// 화일 전송
	int total = size2; // 전송할 전체 크기
	int current = 0;   // 전송한 크기
	int nRead = 0;
	char buf[4096];    // 4k 버퍼.

	while (total >= current)
	{
		DWORD len;
		nRead = ReadFile(hFile, buf, 4096, &len, 0);

		if (len <= 0) break;

		int nSend = send(s, buf, len, 0);
		if (nSend <= 0) break;

		current += nSend;
	}
	if (total != current)	printf("전송에러\n");
	else					printf("전송완료 \n");

	closesocket(s);
	CloseHandle(hFile);
	return 0;
}

int recv_data(SOCKET s, char* buf, int len, int flag)
{
	int size;
	int ret = recvn(s, (char*)&size, sizeof(int), flag);
	if (ret == -1)		return -1;
	else if (ret == 0)	return 0;

	ret = recvn(s, buf, size, flag);
	if (ret == -1)		return -1;
	else if (ret == 0)	return 0;
	else				return size;
}

int send_data(SOCKET s, char* buf, int len, int flag)
{
	int ret = send(s, (char*)&len, sizeof(int), flag);
	ret = send(s, buf, len, flag);
	return ret;
}

int recvn(SOCKET s, char* buf, int len, int flag)
{
	char* ptr = buf;
	int left = len;

	while (left > 0)
	{
		int recv_byte = recv(s, ptr, left, flag);
		if (recv_byte == -1)
			return -1;
		else if (recv_byte == 0)
			return recv_byte;
		else
		{
			left = left - recv_byte;
			ptr = ptr + recv_byte;
		}
	}
	return len - left;
}