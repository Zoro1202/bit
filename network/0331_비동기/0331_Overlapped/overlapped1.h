//overlapped1.h
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 512

// 소켓 정보 저장을 위한 구조체
struct SOCKETINFO
{
	WSAOVERLAPPED overlapped;
	SOCKET sock;
	char buf[1024];
	int size;
	WSABUF wsabuf;
};

struct LINE
{
	POINTS ptFrom;
	POINTS ptTo;
};

int net_initSocket();

void net_run();

void net_exit();

// 소켓 입출력 함수
DWORD WINAPI WorkerThread(LPVOID arg);
DWORD WINAPI ListenThread(LPVOID arg);

// 소켓 관리 함수
BOOL AddSocketInfo(SOCKET sock);
void RemoveSocketInfo(int index);

// 오류 출력 함수
void err_quit(const char* msg);
void err_display(const char* msg);