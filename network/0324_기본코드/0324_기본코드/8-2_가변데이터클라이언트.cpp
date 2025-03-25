#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#pragma comment (lib, "WS2_32.LIB")

#define SERVER_IP_MAIN "127.0.0.1"
#define SERVER_IP "192.168.0.139"
//#define SERVER_IP "220.90.180.111"
#define SERVER_PORT 9000


bool net_createSocket(const char* ip, int port);
void net_deleteSocket();

unsigned long __stdcall recvThread(void* p);

SOCKET sock1;

//�۽� / ����ó��
int recv_data(SOCKET s, char* data, int len, int flags);
int recvn(SOCKET s, char* data, int len, int flags);

int send_data(SOCKET s, char* data, int len, int flags);

int main()
{
	if (net_createSocket(SERVER_IP, SERVER_PORT) == 0)
	{
		printf("���� ����!\n");
		return -1;
	}

	while (1) {
		//�޽��� ����
		char buf[1024];

		gets_s(buf, sizeof(buf));
		if (strlen(buf) == 0)
		{
			break;
		}
		int sendByte = send_data(sock1, buf, (int)(strlen(buf) + 1), 0);
		printf("���� : %d Byte %s\n", sendByte, buf);
		
	}

	net_deleteSocket();
}

bool net_createSocket(const char* ip, int port)
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����!\n");
		return -1;
	}
	//���� �ʱ�ȭ
	sock1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//TCP - STREAM ������ ��������, UDP - DGRAM �񿬰��� ��������

	if (sock1 == INVALID_SOCKET)
	{
		printf("���� ���� ����\n");
		return FALSE;
	}

	SOCKADDR_IN adr;
	memset(&adr, 0, sizeof(SOCKADDR_IN));
	adr.sin_family = AF_INET; //ip �ּ�ü�踦 ���ڴ�
	adr.sin_addr.s_addr = inet_addr(ip);
	adr.sin_port = htons(port);	//��Ʈ��ȣ ����

	int ret = connect(sock1, (SOCKADDR*)&adr, sizeof(adr)); // ���Ͽ� ���� ����
	if (ret == SOCKET_ERROR)
	{
		printf("���� ����!\n");
		return FALSE;
	}
	HANDLE hThread = CreateThread(0, 0, recvThread, (void*)sock1, 0, 0);
	CloseHandle(hThread);

	return TRUE;
}

void net_deleteSocket()
{
	closesocket(sock1);
	WSACleanup();
}


unsigned long __stdcall recvThread(void* p)
{
	SOCKET recv_socket = (SOCKET)p;
	char buf[1024];
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		//�޽��� ����
		int recvbyte = recv_data(recv_socket, buf, sizeof(buf), 0); // recv ��ȯ -1 : ����, 0 : ������ ����, > 1 : ������ ����
		if (recvbyte == -1) // ����
		{
			printf("������ ���� ����Ǿ�����.\n");
			break;
		}
		else if (recvbyte == 0) // ������ CloseSocket. �������� ����
		{
			printf("������ CloseSocket. �������� ����.\n");
			break;
		}
		else  // ���� ���� �߻�
		{
			printf("���� : %d Byte %s\n", recvbyte, buf);
		}
	}

	return 0;
}


//1. ���� ũ�� ��� -> 2. ���� ������
int recv_data(SOCKET s, char* data, int len, int flags)
{
	int size;
	int ret = recv(s, (char*)&size, len, flags);
	if (ret == -1)
	{
		return -1;
	}
	else if (ret == 0)
	{
		return 0;
	}
	else
	{
		printf("��� : %d\t", size);
		ret = recvn(s, data, size, flags);
		if (ret == -1)
		{
			return -1;
		}
		else if (ret == 0)
		{
			return 0;
		}
		else {
			send_data(s, data, (int)(strlen(data) + 1), 0);
			printf("���� : %s\n", data);
		}
	}

	return 0;
}

int recvn(SOCKET s, char* data, int len, int flags)
{
	int received;
	char* ptr = data;
	int left = len;
	while (left > 0)
	{
		received = recv(s, ptr, left, flags);
		if (received == -1)
		{
			return received;
		}
		else if (received == 0)
		{
			return received;
		}
		left -= received;
		ptr += received;
	}
	return (len - left);
}

int send_data(SOCKET s, char* data, int len, int flags)
{
	int ret = send(s, (char*)&len, sizeof(int), flags);
	ret = send(s, data, len, flags);
	return ret;
}

