#include "Async_Server.h"

SOCKET listen_socket;
vector<SOCKET> link_socket;

bool net_initSocket(HWND hwnd)
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
		return 0;

	listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	// socket �� �񵿱� �������� �����Ѵ�.
	WSAAsyncSelect(listen_socket, hwnd, WM_USER + 100, FD_ACCEPT);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(6000);
	addr.sin_addr.s_addr = INADDR_ANY;

	bind(listen_socket, (SOCKADDR*)&addr, sizeof(addr));

	listen(listen_socket, 5);
	return 1;
}

void net_Accept(HWND hwnd)
{
	SOCKADDR_IN addr;
	int	size = sizeof(addr);

	SOCKET socket = accept(listen_socket, (SOCKADDR*)&addr, &size);

	// ��� ������ �ݴ´�.(1:1 ���)
	closesocket(listen_socket);

	SetWindowText(hwnd, "���� �Ǿ����ϴ�.");

	// ����� ������ �񵿱� �������� �����Ѵ�.
	WSAAsyncSelect(socket, hwnd, WM_USER + 100, FD_READ | FD_CLOSE);
	link_socket.push_back(socket);
}

int net_recvData(SOCKET sock, char* msg, int size)
{
	return recv(sock, msg, size, 0);
}

int net_sendallData(SOCKET sock, char* msg, int size)
{
	int ret = 0;
	for (int i = 0; i < link_socket.size(); i++)
	{
		SOCKET s = link_socket[i];
		//if(sock != s)
			 ret = send(sock, msg, size, 0);
	}
	return ret;
}

void net_CloseSocket(SOCKET sock)
{
	for (int i = 0; i < link_socket.size(); i++)
	{
		SOCKET s = link_socket[i];
		if (sock == s)
		{
			link_socket.erase(link_socket.begin() + i);
			closesocket(sock);
		}
	}
}

void net_ExitSocket()
{
	WSACleanup();
}