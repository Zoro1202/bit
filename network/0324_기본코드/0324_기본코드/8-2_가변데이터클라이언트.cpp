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

//송신 / 수신처리
int recv_data(SOCKET s, char* data, int len, int flags);
int recvn(SOCKET s, char* data, int len, int flags);

int send_data(SOCKET s, char* data, int len, int flags);

int main()
{
	if (net_createSocket(SERVER_IP, SERVER_PORT) == 0)
	{
		printf("연결 실패!\n");
		return -1;
	}

	while (1) {
		//메시지 전송
		char buf[1024];

		gets_s(buf, sizeof(buf));
		if (strlen(buf) == 0)
		{
			break;
		}
		int sendByte = send_data(sock1, buf, (int)(strlen(buf) + 1), 0);
		printf("전송 : %d Byte %s\n", sendByte, buf);
		
	}

	net_deleteSocket();
}

bool net_createSocket(const char* ip, int port)
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패!\n");
		return -1;
	}
	//소켓 초기화
	sock1 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//TCP - STREAM 연결형 프로토콜, UDP - DGRAM 비연결형 프로토콜

	if (sock1 == INVALID_SOCKET)
	{
		printf("소켓 생성 오류\n");
		return FALSE;
	}

	SOCKADDR_IN adr;
	memset(&adr, 0, sizeof(SOCKADDR_IN));
	adr.sin_family = AF_INET; //ip 주소체계를 쓰겠다
	adr.sin_addr.s_addr = inet_addr(ip);
	adr.sin_port = htons(port);	//포트번호 설정

	int ret = connect(sock1, (SOCKADDR*)&adr, sizeof(adr)); // 소켓에 설정 적용
	if (ret == SOCKET_ERROR)
	{
		printf("연결 실패!\n");
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
		//메시지 수신
		int recvbyte = recv_data(recv_socket, buf, sizeof(buf), 0); // recv 반환 -1 : 오류, 0 : 정상적 종료, > 1 : 데이터 받음
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
		}
	}

	return 0;
}


//1. 고정 크기 헤더 -> 2. 실제 데이터
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
		printf("헤더 : %d\t", size);
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
			printf("수신 : %s\n", data);
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

