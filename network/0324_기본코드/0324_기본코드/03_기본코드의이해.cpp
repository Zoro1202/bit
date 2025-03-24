//03_�⺻�ڵ�������.cpp
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#pragma comment (lib, "WS2_32.LIB")

#define SERVER_IP_MAIN "127.0.0.1"
//#define SERVER_IP "169.254.238.146"
#define SERVER_IP "220.90.180.111"
#define SERVER_PORT 9000

void exam1();
void exam2();

int main()
{
	//exam1();
	exam2();
	return 0;
}


void exam1()
{
	char ip[512] = "1.2.3.4";
	printf("%s\n", ip);					// 1.2.3.4
	//���ڿ� -> ����
	int num = inet_addr(ip);
	printf("0x%08x\n", num);			// 0x04030201
	
	//���� -> ���ڿ�: inet_ntoa(IN_ADDR)
	IN_ADDR in_addr;
	//in_addr.S_un.S_addr = num;
	in_addr.s_addr = num;
	printf("%s\n", inet_ntoa(in_addr));	// 1.2.3.4

}

/*
��Ʋ ����� : ���� �ּҺ��� ������ ����
�� ����� : ū �ּҺ��� ������ ����

���� ���α׷� : �� ������� ���(���)			-> ��Ʈ��ũ ����Ʈ ����
�Ϲ� PC : ��Ʋ �����, �� ����� �� �ϳ��� ��� -> ȣ��Ʈ ����Ʈ ����
*/
//���α׷� -> �����Լ� ȣ�� : ��Ʈ��ũ ����Ʈ ���ķ� ��ȯ �� ȣ��
//�����Լ� -> ���α׷� ȣ�� : ȣ��Ʈ ����Ʈ ���ķ� ��ȯ �� ȣ��
void exam2()
{
	unsigned short us = 0x1234;
	unsigned long ul = 0x12345678;

	//ȣ��Ʈ -> ��Ʈ��ũ
	printf("0x%08x -> 0x%08x\n", us, htons(us));
	printf("0x%08x -> 0x%08x\n", ul, htonl(ul));

	unsigned short n_us = htons(us);
	unsigned long n_ul = htonl(ul);
	
	printf("0x%08x -> 0x%08x\n", n_us, ntohs(n_us));
	printf("0x%08x -> 0x%08x\n", n_ul, ntohl(n_ul));

}