/*
서버기본코드
1. 연결 성공
2. 데이터 수신
3. 수신된 데이터 송신
4. 1~3번을 무한 반복
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#pragma comment (lib, "WS2_32.LIB")

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
	SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//TCP - STREAM 연결형 프로토콜, UDP - DGRAM 비연결형 프로토콜

	if (listen_socket == INVALID_SOCKET)
	{
		printf("소켓 생성 오류\n");
		return -1;
	}

	SOCKADDR_IN adr;
	memset(&adr, 0, sizeof(SOCKADDR_IN));
	adr.sin_family = AF_INET; //ip를 쓰겠다
	adr.sin_addr.s_addr = htonl(INADDR_ANY);// 사용 가능한 아이피가 할당 됨. 

	int ret = bind(listen_socket, (SOCKADDR*)&adr, sizeof(adr));
	if (ret == SOCKET_ERROR)
	{
		printf("바인딩 실패!\n");
		return -1;
	}

	listen(listen_socket, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		printf("리스닝 실패!\n");
		return -1;
	}
	while (1)
	{
		SOCKADDR_IN client_adr;
		memset(&client_adr, 0, sizeof(SOCKADDR_IN));
		int client_length = sizeof(SOCKADDR_IN);
		SOCKET clientSock = accept(listen_socket, (SOCKADDR*)&client_adr, &client_length);
		if (clientSock == INVALID_SOCKET)
		{
			printf("요청 수락 오류\n");
			return -1;
		}

		printf("클라이언트 연결 : (%s : %d)\n", 
			inet_ntoa(client_adr.sin_addr), ntohs(client_adr.sin_port));


		//echo 서버 메아리 서버
		//메시지 수신
		char buf[1024];
		int recvbyte = recv(clientSock, buf, sizeof(buf), 0);
		if (recvbyte == -1) // 오류
		{
			printf("상대방이 강제 종료되었을때.\n");
		}
		else if (recvbyte == 0) // 상대방이 CloseSocket. 정상적인 종료
		{
			printf("상대방이 CloseSocket. 정상적인 종료.\n");
		}
		else  // 실제 수신 발생
		{
			printf("수신 : %d Byte %s\n", recvbyte, buf);
			//메시지 송신
			int sendByte = send(clientSock, buf, strlen(buf) + 1, 0);
			printf("송신 : %d Byte %s\n", sendByte, buf);
		}
	}
	closesocket(listen_socket);
	WSACleanup();

}