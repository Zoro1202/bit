#pragma once

//라이브러리 초기화 및 종료처리
bool net_initlibrary(HWND h);
void net_exitlibrary();

//소켓 생성 및 초기화(socket->connect-> recvthread) 및 종료처리
bool net_create_socket(const char* ip, int port, char *buf);
void net_delete_socket();

//통신 스레드(recv->화면출력)
unsigned long __stdcall recv_thread(void* p);

//송신& 수신 처리 
//1.고정크기헤더 -> 2.실제 데이터
int recv_data(SOCKET s, char* buf, int len, int flag);
int send_data(SOCKET s, char* buf, int len, int flag);
int recvn(SOCKET s, char* buf, int len, int flag);

void send_addmember(char* name, char* phone, int age);

void send_selectmember(char* name);

void send_updatemember(char* name, char* phone, int age);

void send_deletemember(char* name);

void send_shortmessage(char* name, const char* msg);
