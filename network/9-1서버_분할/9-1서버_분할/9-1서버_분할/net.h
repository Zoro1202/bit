#pragma once
//net.h

bool net_initlibrary();
void net_exitlibrary();
bool net_create_socket(int port);
void net_delete_socket();

unsigned long __stdcall listen_thread(void* p);
unsigned long __stdcall work_thread(void* p);

int recv_data(SOCKET s, char* buf, int len, int flag);
int send_data(SOCKET s, char* buf, int len, int flag);
int recvn(SOCKET s, char* buf, int len, int flag);
