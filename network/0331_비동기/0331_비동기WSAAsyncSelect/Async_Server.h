#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>
#include <vector>
using namespace std;

bool net_initSocket(HWND hwnd);

void net_Accept(HWND hwnd);

int net_recvData(SOCKET sock, char* line, int size);

int net_sendallData(SOCKET sock, char* msg, int size);

void net_CloseSocket(SOCKET sock);

void net_ExitSocket();
