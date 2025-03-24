/*
�����⺻�ڵ�
1. ���� ����
2. ������ ����
3. ���ŵ� ������ �۽�
4. 1~3���� ���� �ݺ�
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#pragma comment (lib, "WS2_32.LIB")

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
	SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//TCP - STREAM ������ ��������, UDP - DGRAM �񿬰��� ��������

	if (listen_socket == INVALID_SOCKET)
	{
		printf("���� ���� ����\n");
		return -1;
	}

	SOCKADDR_IN adr;
	memset(&adr, 0, sizeof(SOCKADDR_IN));
	adr.sin_family = AF_INET; //ip �ּ�ü�踦 ���ڴ�
	adr.sin_addr.s_addr = htonl(INADDR_ANY);// ��� ������ �����ǰ� �Ҵ� ��. 
	adr.sin_port = htons(9000);	//��Ʈ��ȣ ����
	int ret = bind(listen_socket, (SOCKADDR*)&adr, sizeof(adr)); // ���Ͽ� ���� ����
	if (ret == SOCKET_ERROR)
	{
		printf("���ε� ����!\n");
		return -1;
	}

	listen(listen_socket, SOMAXCONN); // ���� ���?
	if (ret == SOCKET_ERROR)
	{
		printf("listen ����!\n");
		return -1;
	}
	int isRun = 1;
	while (isRun) {
		SOCKADDR_IN client_adr;
		memset(&client_adr, 0, sizeof(SOCKADDR_IN)); // �޸� 0���� �ʱ�ȭ
		int client_length = sizeof(SOCKADDR_IN);	//client length ����
		SOCKET clientSock = accept(listen_socket, (SOCKADDR*)&client_adr, &client_length); // Ŭ���̾�Ʈ�� ��ٸ�
		if (clientSock == INVALID_SOCKET)
		{
			printf("��û ���� ����\n");
			return -1;
		}

		printf("Ŭ���̾�Ʈ ���� : (%s : %d)\n",
			inet_ntoa(client_adr.sin_addr), ntohs(client_adr.sin_port)); // ntoa ��Ʈ��ũ ������ ȣ��Ʈ ���ķ� �ٲ� �Ŀ� ���ڿ��� �ٲ���. ntohs ��Ʈ->ȣ��Ʈ ����(shortŸ��)

		while (1) {
			//echo ���� �޾Ƹ� ����
			//�޽��� ����
			char buf[1024];
			int recvbyte = recv(clientSock, buf, sizeof(buf), 0); // recv ��ȯ -1 : ����, 0 : ������ ����, > 1 : ������ ����
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
				//�޽��� �۽�
				int sendByte = send(clientSock, buf, strlen(buf) + 1, 0);
				printf("�۽� : %d Byte %s\n", sendByte, buf);
				if (strcmp(buf, "-1") == 0) { isRun = 0; break; }
			}
		}
		closesocket(clientSock);
	}
	closesocket(listen_socket);
	WSACleanup();

}