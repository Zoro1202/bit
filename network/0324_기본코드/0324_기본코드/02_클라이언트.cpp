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
	//초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패!\n");
		return -1;
	}

	//소켓 초기화
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//TCP - STREAM 연결형 프로토콜, UDP - DGRAM 비연결형 프로토콜

	if (sock == INVALID_SOCKET)
	{
		printf("소켓 생성 오류\n");
		return -1;
	}
	//서버 소켓에 연결

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	addr.sin_port = htons(SERVER_PORT);

	int ret = connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
	if (ret == SOCKET_ERROR)
	{
		printf("연결 요청 오류\n");
		return -1;
	}

	//메시지 전송
	char buf[1024];

	printf(">> "); gets_s(buf, sizeof(buf));
	//메시지 전송
	int sendByte = send(sock, buf, (int)(strlen(buf) + 1), 0);
	printf("전송 : %d Byte %s\n", sendByte, buf);
	//메시지 수신
	int recvByte = recv(sock, buf, sizeof(buf), 0);
	if (recvByte == -1) // 오류
	{
		printf("상대방이 강제 종료되었을때.\n");
	}
	else if (recvByte == 0) // 상대방이 CloseSocket. 정상적인 종료
	{
		printf("상대방이 CloseSocket. 정상적인 종료.\n");
	}
	else  // 실제 수신 발생
	{
		printf("수신 : %d Byte %s\n", recvByte, buf);
	}
	closesocket(sock);
	WSACleanup();

}