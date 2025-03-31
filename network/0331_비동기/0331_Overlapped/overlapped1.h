//overlapped1.h
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 512

// ���� ���� ������ ���� ����ü
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

// ���� ����� �Լ�
DWORD WINAPI WorkerThread(LPVOID arg);
DWORD WINAPI ListenThread(LPVOID arg);

// ���� ���� �Լ�
BOOL AddSocketInfo(SOCKET sock);
void RemoveSocketInfo(int index);

// ���� ��� �Լ�
void err_quit(const char* msg);
void err_display(const char* msg);