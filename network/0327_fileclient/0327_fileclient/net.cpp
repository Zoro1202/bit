//net.cpp
#include "std.h"

SOCKET sock;

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

bool net_create_socket(const char* ip, int port)
{
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		printf("socket() ���� ����\n");
		return false;
	}

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);

	int ret = connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
	if (ret == SOCKET_ERROR)
	{
		printf("���� ��û ����\n");
		return false;
	}

	CloseHandle(CreateThread(0, 0, recv_thread, (void*)sock, 0, 0));

	return true;
}

void net_delete_socket()
{
	closesocket(sock);
}

unsigned long __stdcall recv_thread(void* p)
{
	SOCKET sock = (SOCKET)p;

	char recv_buf[4096];
	while (true)
	{
		memset(recv_buf, 0, sizeof(recv_buf));
		int recv_byte = recv_data(recv_buf, sizeof(recv_buf), 0);
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
			//printf("	[���� byte] %dbyte, %s\n", recv_byte, recv_buf);
			msg_parsing(recv_buf);
		}
	}
	return 0;
}

int recv_data(char* buf, int len, int flag)
{
	int size;
	int ret = recvn((char*)&size, sizeof(int), flag);
	if (ret == -1)		return -1;
	else if (ret == 0)	return 0;

	ret = recvn(buf, size, flag);
	if (ret == -1)		return -1;
	else if (ret == 0)	return 0;
	else				return size;
}

int send_data(char* buf, int len, int flag)
{
	int ret = send(sock, (char*)&len, sizeof(int), flag);
	ret = send(sock, buf, len, flag);
	return ret;
}

int recvn(char* buf, int len, int flag)
{
	char* ptr = buf;
	int left = len;

	while (left > 0)
	{
		int recv_byte = recv(sock, ptr, left, flag);
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