#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <vector>
using namespace std;

#include "Event_server.h"

vector<SOCKET> SocketInfoArray;
vector<WSAEVENT> EventArray;
	//WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];//64
	//int nTotalSockets = 0;
//���� �����̳� to �迭�� �̵�

SOCKET listen_socket;

void net_vectorToArr(WSAEVENT* parr, int *size)
{
	*size = (int)EventArray.size();
	for (int i = 0; i < *size; i++)
	{
		parr[i] = EventArray[i];
	}
}

bool net_initSocket()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		MessageBox(0, "Error", "", MB_OK);
		return 0;
	}

	//----------------------------------------------------------------------------------
	listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // ���� ����
	SocketInfoArray.push_back(listen_socket); // ���� ����

	WSAEVENT hEvent = WSACreateEvent();	// �̺�Ʈ ����
	EventArray.push_back(hEvent); // �̺�Ʈ ����

	WSAEventSelect(listen_socket, hEvent, FD_ACCEPT); // �̺�Ʈ�� ���� ����
	//-----------------------------------------------------------------------------------

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(6000);
	addr.sin_addr.s_addr = INADDR_ANY;
	bind(listen_socket, (SOCKADDR*)&addr, sizeof(addr));
	listen(listen_socket, 5);

	return true;
}

void net_run()
{
	//������ ����
	HANDLE hthread = CreateThread(0, 0, WorkerThread, (void*)0, 0, 0);
	WaitForSingleObject(hthread, INFINITE);
}

void net_exitSocket()
{
	WSACleanup();
}

void net_CloseSocket(SOCKET sock)
{

}

unsigned long WINAPI WorkerThread(void* pParam)
{
	int retval;

	while (1)
	{
		WSAEVENT event_arr[64];
		int event_size;
		net_vectorToArr(event_arr, &event_size);
		int index = WSAWaitForMultipleEvents(event_size, event_arr, FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED)
			continue;
		index -= WSA_WAIT_EVENT_0;   // �������� �ϸ� ����, �ε������ ��

		WSANETWORKEVENTS NetworkEvents;
		retval = WSAEnumNetworkEvents(SocketInfoArray[index], EventArray[index], &NetworkEvents);
		if (retval == SOCKET_ERROR)
			continue;
		//-------------------------------------------------------------------------

		// FD_ACCEPT �̺�Ʈ ó���� ó���Ѵ�.
		if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
		{
			if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
				continue;

			SOCKADDR_IN clientaddr;
			int addrlen = sizeof(clientaddr);
			SOCKET client_sock = accept(SocketInfoArray[index], (SOCKADDR*)&clientaddr, &addrlen);
			if (client_sock == INVALID_SOCKET)
			{
				continue;
			}
			//----------------------------------------------------------------------------------
			SocketInfoArray.push_back(client_sock);

			WSAEVENT hEvent = WSACreateEvent();
			EventArray.push_back(hEvent);

			//SocketInfoArray[event_size] = client_sock;
			//EventArray[event_size] = hEvent;
			
			retval = WSAEventSelect(client_sock, hEvent, FD_READ | FD_CLOSE);
			if (retval == SOCKET_ERROR)
				break;
		}
		else if (NetworkEvents.lNetworkEvents & FD_READ)
		{
			char msg[100];
			recv(SocketInfoArray[index], msg, (sizeof(POINTS) * 2), 0);

			for (int i = 0; i < SocketInfoArray.size(); i++) //1���� Ŭ���̾�Ʈ�� �� ����Ÿ�� ��� Ŭ���̾�Ʈ���� �Ѹ� ��ε�ĳ��Ʈ?
			{
				SOCKET s = SocketInfoArray[i];
				send(s, msg, sizeof(sizeof(POINTS) * 2), 0);
			}
		}
		else if (NetworkEvents.lNetworkEvents & FD_CLOSE)
		{
			//����, �̺�Ʈ �ݾ��ֱ�
			closesocket(SocketInfoArray[index]);
			WSACloseEvent(EventArray[index]);
			//���� �����̳ʿ��� ����
			SocketInfoArray.erase(SocketInfoArray.begin() + index);
			EventArray.erase(EventArray.begin() + index);
		}
	}
	return 0;
}

