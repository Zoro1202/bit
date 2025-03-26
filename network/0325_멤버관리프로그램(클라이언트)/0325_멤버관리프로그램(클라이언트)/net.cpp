#include "std.h"

//net ��⿡ �����ϴ� ��������(��ż���)
SOCKET sock;
HWND hdlg;
bool net_initlibrary(HWND h)
{
	hdlg = h;
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return false;
	else
		return true;
}

void net_exitlibrary()
{
	WSACleanup();
}

bool net_create_socket(const char* ip, int port, char* buf)
{
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		printf("socket() ���� ����\n");
		return false;
	}

	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(ip);
	addr.sin_port = htons(port);

	int ret = connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN));
	if (ret == SOCKET_ERROR)
	{
		printf("���� ��û ����\n");
		return false;
	}

	CloseHandle(CreateThread(0, 0, recv_thread, (void*)buf, 0, 0));

	return true;
}

void net_delete_socket()
{
	closesocket(sock);
}

unsigned long __stdcall recv_thread(void* p)
{
	char recv_buf[1024];
	while (true)
	{
		memset(recv_buf, 0, sizeof(recv_buf));
		int recv_byte = recv_data(sock, recv_buf, sizeof(recv_buf), 0);
		if (recv_byte == -1)
		{
			printf("����-���� ���α׷��� ���� ����\n");
			break;
		}
		else if (recv_byte == 0)
		{
			printf("������ closesocket() ���� ����\n");
			break;
		}
		else
		{
			//printf("	[���� byte] %dbyte, %s\n", recv_byte, recv_buf);
			msg_parsing(hdlg, recv_buf);
			
		}
	}
	return 0;
}

int recv_data(SOCKET s, char* buf, int len, int flag)
{
	int size;
	int ret = recvn(s, (char*)&size, sizeof(int), flag);
	if (ret == -1)		return -1;
	else if (ret == 0)	return 0;

	ret = recvn(s, buf, size, flag);
	if (ret == -1)		return -1;
	else if (ret == 0)	return 0;
	else				return size;
}

int send_data(SOCKET s, char* buf, int len, int flag)
{
	int ret = send(s, (char*)&len, sizeof(int), flag);
	ret = send(s, buf, len, flag);
	return ret;
}

int recvn(SOCKET s, char* buf, int len, int flag)
{
	char* ptr = buf;
	int left = len;

	while (left > 0)
	{
		int recv_byte = recv(s, ptr, left, flag);
		if (recv_byte == -1)
			return -1;
		else if (recv_byte == 0)
			return recv_byte;
		else
		{
			left = left - recv_byte;
			ptr = ptr + recv_byte;
		}
	}
	return len - left;
}

//���� sample
void send_addmember(char* name, char* phone, int age)
{
	AddMemberPacket packet;
	packet.flag = PACKET_ADDMEMBER;
	strcpy_s(packet.name,sizeof(packet.name), name);
	strcpy_s(packet.phone, sizeof(packet.phone), phone);
	packet.age = age;
	send_data(sock, (char*)&packet, sizeof(packet), 0);
}

void send_selectmember(char* name)
{
	SelectMemberPacket packet;
	packet.flag = PACKET_SELECTMEMBER;
	strcpy_s(packet.name, sizeof(packet.name), name);
	send_data(sock, (char*)&packet, sizeof(packet), 0);
}

void send_updatemember(char* name, char* phone, int age)
{
	UpdateMemberPacket packet;
	packet.flag = PACKET_UPDATEMEMBER;
	strcpy_s(packet.name, sizeof(packet.name), name);
	strcpy_s(packet.phone, sizeof(packet.phone), phone);
	packet.age = age;
	send_data(sock, (char*)&packet, sizeof(packet), 0);
}

void send_deletemember(char* name)
{
	DeleteMemberPacket packet = { 0 };
	packet.flag = PACKET_DELETEMEMBER;
	strcpy_s(packet.name, sizeof(packet.name), name);
	send_data(sock, (char*)&packet, sizeof(packet), 0);
}

void send_shortmessage(char* name, const char* msg)
{
	ShortMessagePacket packet;
	packet.flag = PACKET_SHORTMESSAGE;
	strcpy_s(packet.name, sizeof(packet.name), name);
	strcpy_s(packet.msg, sizeof(packet.msg), msg);
	send_data(sock, (char*)&packet, sizeof(packet), 0);
}
