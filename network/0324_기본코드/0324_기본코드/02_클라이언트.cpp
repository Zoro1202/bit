#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#pragma comment (lib, "WS2_32.LIB")

#define SERVER_IP_MAIN "127.0.0.1"
#define SERVER_IP "169.254.238.146"
//#define SERVER_IP "220.90.180.111"
#define SERVER_PORT 9000

int main()
{
	WSADATA wsa;
	//�ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����!\n");
		return -1;
	}

	//���� �ʱ�ȭ
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//TCP - STREAM ������ ��������, UDP - DGRAM �񿬰��� ��������

	if (sock == INVALID_SOCKET)
	{
		printf("���� ���� ����\n");
		return -1;
	}
	//���� ���Ͽ� ����

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	addr.sin_port = htons(SERVER_PORT);

	int ret = connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
	if (ret == SOCKET_ERROR)
	{
		printf("���� ��û ����\n");
		return -1;
	}

	//�޽��� ����
	char buf[1024];

	printf(">> "); gets_s(buf, sizeof(buf));
	//�޽��� ����
	int sendByte = send(sock, buf, (int)(strlen(buf) + 1), 0);
	printf("���� : %d Byte %s\n", sendByte, buf);
	//�޽��� ����
	int recvByte = recv(sock, buf, sizeof(buf), 0);
	if (recvByte == -1) // ����
	{
		printf("������ ���� ����Ǿ�����.\n");
	}
	else if (recvByte == 0) // ������ CloseSocket. �������� ����
	{
		printf("������ CloseSocket. �������� ����.\n");
	}
	else  // ���� ���� �߻�
	{
		printf("���� : %d Byte %s\n", recvByte, buf);
	}
	closesocket(sock);
	WSACleanup();

}