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
		printf("socket() ���� ����\n");
		return false;
	}

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY); //��� ������ IP�� �Ҵ��.
	addr.sin_port = htons(port);

	int ret = bind(listen_sock, (SOCKADDR*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		printf("bind() ����\n");
		return false;
	}

	ret = listen(listen_sock, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		printf("listen() ����\n");
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
			printf("���� ����\n");
			continue;  //�ݺ����� ���������� ���� �̵�!
		}
		printf("Ŭ���̾�Ʈ ���� : (%s:%d)\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

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
	char buf[1024];

	while (true)
	{
		memset(buf, 0, sizeof(buf));
		int recv_byte = recv_data(client_socket, buf, sizeof(buf), 0);
		if (recv_byte == -1)
		{
			printf("����-���� ���α׷��� ���� ����\n");
			break;
		}
		else if (recv_byte == 0)
		{
			printf("������ closesocket() ���� ����\n");
			break;
		}
		else
		{
			//printf("	[���� byte] %dbyte, %s\n", recv_byte, buf);

			int size = con_msg_parsing(buf);

			int send_byte = send_data(client_socket, buf, size, 0);
			printf("	[�۽�] ");
			printf("\n\n");
		}
	}

	//getsockname, getpeername
	SOCKADDR_IN client_addr;
	int client_length = sizeof(SOCKADDR_IN);
	getpeername(client_socket, (SOCKADDR*)&client_addr, &client_length);
	printf("Ŭ���̾�Ʈ ���� : (%s:%d)\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

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