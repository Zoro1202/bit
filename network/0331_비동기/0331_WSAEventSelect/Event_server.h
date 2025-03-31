//Event_server.h
#pragma once
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
void net_vectorToArr(WSAEVENT* parr, int* size);

bool net_initSocket();
void net_run();
void net_exitSocket();
void net_CloseSocket(SOCKET sock);

unsigned long __stdcall WorkerThread(void* pParam);




