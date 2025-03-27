//net.h
#pragma once

//라이브러리 초기화 및 종료처리
bool net_initlibrary();
void net_exitlibrary();

//소켓 생성 및 초기화(socket->bind->listen) 및 종료처리
bool net_create_socket(int port);
void net_delete_socket();

//클라이언트 접속을 대기하는 스레드(accept -> 통신스레드 생성)
unsigned long __stdcall listen_thread(void* p);
//접속된 클라이언트와 통신하는 스레드(recv -> send)
unsigned long __stdcall work_thread(void* p);

void Initfilename(char* _filename);

DWORD __stdcall FileServer(void* p);

//송신& 수신 처리 
//1.고정크기헤더 -> 2.실제 데이터
int recv_data(SOCKET s, char* buf, int len, int flag);
int send_data(SOCKET s, char* buf, int len, int flag);
int recvn(SOCKET s, char* buf, int len, int flag);