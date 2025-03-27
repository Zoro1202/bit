//net.h
#pragma once

//���̺귯�� �ʱ�ȭ �� ����ó��
bool net_initlibrary();
void net_exitlibrary();

//���� ���� �� �ʱ�ȭ(socket->bind->listen) �� ����ó��
bool net_create_socket(int port);
void net_delete_socket();

//Ŭ���̾�Ʈ ������ ����ϴ� ������(accept -> ��Ž����� ����)
unsigned long __stdcall listen_thread(void* p);
//���ӵ� Ŭ���̾�Ʈ�� ����ϴ� ������(recv -> send)
unsigned long __stdcall work_thread(void* p);

void Initfilename(char* _filename);

DWORD __stdcall FileServer(void* p);

//�۽�& ���� ó�� 
//1.����ũ����� -> 2.���� ������
int recv_data(SOCKET s, char* buf, int len, int flag);
int send_data(SOCKET s, char* buf, int len, int flag);
int recvn(SOCKET s, char* buf, int len, int flag);