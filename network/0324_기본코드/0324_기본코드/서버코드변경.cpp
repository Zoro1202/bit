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
	adr.sin_family = AF_INET; //ip 주소체계를 쓰겠다
	adr.sin_addr.s_addr = htonl(INADDR_ANY);// 사용 가능한 아이피가 할당 됨. 
	adr.sin_port = htons(9000);	//포트번호 설정
	int ret = bind(listen_socket, (SOCKADDR*)&adr, sizeof(adr)); // 소켓에 설정 적용
	if (ret == SOCKET_ERROR)
	{
		printf("바인딩 실패!\n");
		return -1;
	}

	listen(listen_socket, SOMAXCONN); // 소켓 등록?
	if (ret == SOCKET_ERROR)
	{
		printf("listen 실패!\n");
		return -1;
	}
	int isRun = 1;
	while (isRun) {
		SOCKADDR_IN client_adr;
		memset(&client_adr, 0, sizeof(SOCKADDR_IN)); // 메모리 0으로 초기화
		int client_length = sizeof(SOCKADDR_IN);	//client length 설정
		SOCKET clientSock = accept(listen_socket, (SOCKADDR*)&client_adr, &client_length); // 클라이언트를 기다림
		if (clientSock == INVALID_SOCKET)
		{
			printf("요청 수락 오류\n");
			return -1;
		}

		printf("클라이언트 연결 : (%s : %d)\n",
			inet_ntoa(client_adr.sin_addr), ntohs(client_adr.sin_port)); // ntoa 네트워크 정렬을 호스트 정렬로 바꾼 후에 문자열로 바꿔줌. ntohs 네트->호스트 정렬(short타입)

		while (1) {
			//echo 서버 메아리 서버
			//메시지 수신
			char buf[1024];
			int recvbyte = recv(clientSock, buf, sizeof(buf), 0); // recv 반환 -1 : 오류, 0 : 정상적 종료, > 1 : 데이터 받음
			if (recvbyte == -1) // 오류
			{
				printf("상대방이 강제 종료되었을때.\n");
				break;
			}
			else if (recvbyte == 0) // 상대방이 CloseSocket. 정상적인 종료
			{
				printf("상대방이 CloseSocket. 정상적인 종료.\n");
				break;
			}
			else  // 실제 수신 발생
			{
				printf("수신 : %d Byte %s\n", recvbyte, buf);
				//메시지 송신
				int sendByte = send(clientSock, buf, strlen(buf) + 1, 0);
				printf("송신 : %d Byte %s\n", sendByte, buf);
				if (strcmp(buf, "-1") == 0) { isRun = 0; break; }
			}
		}
		closesocket(clientSock);
	}
	closesocket(listen_socket);
	WSACleanup();

}