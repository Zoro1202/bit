#pragma once

//���̺귯�� �ʱ�ȭ �� ����ó��
bool net_initlibrary();
void net_exitlibrary();

//���� ���� �� �ʱ�ȭ(socket->connect-> recvthread) �� ����ó��
bool net_create_socket(const char* ip, int port);
void net_delete_socket();

//��� ������(recv->ȭ�����)
unsigned long __stdcall recv_thread(void* p);

//�۽�& ���� ó�� 
//1.����ũ����� -> 2.���� ������
int recv_data(SOCKET s, char* buf, int len, int flag);
int send_data(SOCKET s, char* buf, int len, int flag);
int recvn(SOCKET s, char* buf, int len, int flag);

void send_addmember(char* name, char* phone, int age);

void send_selectmember(char* name);

void send_shortmessage(char* name, const char* msg);
