//overlapped1.cpp

#include "overlapped1.h"

int nTotalSockets = 0;
SOCKETINFO* SocketInfoArray[WSA_MAXIMUM_WAIT_EVENTS];
WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];
CRITICAL_SECTION cs;
SOCKET listen_sock;

int net_initSocket()
{
	int retval;
	InitializeCriticalSection(&cs);

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	// socket()
	listen_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(6000);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// listen()
	retval = listen(listen_sock, SOMAXCONN);
	if (retval == SOCKET_ERROR) err_quit("listen()");

	// ����(dummy) �̺�Ʈ ��ü ����
	WSAEVENT hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT)
		err_quit("WSACreateEvent()");
	EventArray[nTotalSockets++] = hEvent;

	return 0;
}

void net_run()
{

	HANDLE hThread1 = CreateThread(NULL, 0, ListenThread,
		NULL, 0, 0);
	if (hThread1 == NULL) return;

	HANDLE hThread2 = CreateThread(NULL, 0, WorkerThread,
		NULL, 0, 0);
	if (hThread2 == NULL) return;


	HANDLE hThreads[2] = { hThread1 , hThread2 };
	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
	CloseHandle(hThread1);
	CloseHandle(hThread2);
}
void net_exit()		
{
	// ���� ����
	WSACleanup();
	DeleteCriticalSection(&cs);
}

//��� ������
DWORD WINAPI ListenThread(LPVOID arg)
{
	while (1) {
		// accept()
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		SOCKET client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);
		if (client_sock == INVALID_SOCKET) {
			err_display("accept()");
			continue;
		}
		printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		// ���� ���� �߰�
		if (AddSocketInfo(client_sock) == FALSE) {
			closesocket(client_sock);
			printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
				inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
			continue;
		}

		// �񵿱� ����� ����
		SOCKETINFO* ptr = SocketInfoArray[nTotalSockets - 1];
		DWORD size;
		DWORD flags = 0;
		int retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &size,
			&flags, &(ptr->overlapped), NULL);
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				err_display("WSARecv()");
				RemoveSocketInfo(nTotalSockets - 1);
				continue;
			}
		}

		// ������ ����(nTotalSockets) ��ȭ�� �˸� // <<���ΰ�ħ>>
		if (WSASetEvent(EventArray[0]) == FALSE) {
			err_display("WSASetEvent()");
			break;
		}
	}
	return 0;
}

// �񵿱� ����� ó��
DWORD WINAPI WorkerThread(LPVOID arg)
{
	int retval;

	while (1) {
		// �̺�Ʈ ��ü ����
		DWORD index = WSAWaitForMultipleEvents(nTotalSockets,
			EventArray, FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED) {
			err_display("WSAWaitForMultipleEvents()");
			continue;
		}
		index -= WSA_WAIT_EVENT_0;
		WSAResetEvent(EventArray[index]);
		if (index == 0) continue;

		//1. Ŭ���̾�Ʈ ���� ���
		SOCKETINFO* ptr = SocketInfoArray[index];
		SOCKADDR_IN clientaddr;
		int addrlen = sizeof(clientaddr);
		getpeername(ptr->sock, (SOCKADDR*)&clientaddr, &addrlen);

		//2. �񵿱� ����� ��� Ȯ��
		DWORD cbTransferred, flags;
		retval = WSAGetOverlappedResult(ptr->sock, &(ptr->overlapped),
			&cbTransferred, FALSE, &flags);

		//3. ������ ���� Ȯ��
		LINE * pLine = (LINE*)ptr->buf;
		printf("������ ���� : %d, %d -> %d, %d\n", pLine->ptFrom.x, pLine->ptFrom.y, pLine->ptTo.x, pLine->ptTo.y);

		//4. ������ �۽�
		send(ptr->sock, (char*)ptr->buf, sizeof(LINE), 0);

		//ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
		//ptr->overlapped.hEvent = EventArray[index];
		//ptr->wsabuf.buf = ptr->buf;
		//ptr->wsabuf.len = sizeof(LINE);

		//DWORD sendbytes;
		//retval = WSASend(ptr->sock, &(ptr->wsabuf), 1, &sendbytes,
		//	0, &(ptr->overlapped), NULL);
		//if (retval == SOCKET_ERROR) {
		//	if (WSAGetLastError() != WSA_IO_PENDING) {
		//		err_display("WSASend()");
		//	}
		//	continue;
		//}

		//ptr->size = 0;
		//// ������ �ޱ�
		//ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
		//ptr->overlapped.hEvent = EventArray[index];
		//ptr->wsabuf.buf = ptr->buf;
		//ptr->wsabuf.len = sizeof(LINE);

		//5. Ŭ���̾�Ʈ�κ��� ���ο� �����͸� �����ϱ� ���� �񵿱� ȣ��
		DWORD size;
		flags = 0;
		retval = WSARecv(ptr->sock, &(ptr->wsabuf), 1, &size,&flags, &(ptr->overlapped), NULL);
		if (retval == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				err_display("WSARecv()");
			}
			continue;
		}
		
	}
}

// ���� ���� �߰�
BOOL AddSocketInfo(SOCKET sock)
{
	EnterCriticalSection(&cs);

	if (nTotalSockets >= WSA_MAXIMUM_WAIT_EVENTS) {
		printf("[����] ���� ������ �߰��� �� �����ϴ�!\n");
		LeaveCriticalSection(&cs);
		return FALSE;
	}

	SOCKETINFO* ptr = new SOCKETINFO;
	if (ptr == NULL) {
		printf("[����] �޸𸮰� �����մϴ�!\n");
		LeaveCriticalSection(&cs);
		return FALSE;
	}

	WSAEVENT hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT) {
		err_display("WSACreateEvent()");
		LeaveCriticalSection(&cs);
		return FALSE;
	}

	ZeroMemory(&(ptr->overlapped), sizeof(ptr->overlapped));
	ptr->overlapped.hEvent = hEvent;
	ptr->sock = sock;
	ptr->size = 0;
	//ptr->sendbytes = 0;
	ptr->wsabuf.buf = ptr->buf;
	ptr->wsabuf.len = sizeof(LINE);
	SocketInfoArray[nTotalSockets] = ptr;
	EventArray[nTotalSockets] = hEvent;
	nTotalSockets++;

	LeaveCriticalSection(&cs);
	return TRUE;
}

// ���� ���� ����
void RemoveSocketInfo(int index)
{
	EnterCriticalSection(&cs);

	SOCKETINFO* ptr = SocketInfoArray[index];
	closesocket(ptr->sock);
	delete ptr;
	WSACloseEvent(EventArray[index]);

	for (int i = index; i < nTotalSockets; i++) {
		SocketInfoArray[i] = SocketInfoArray[i + 1];
		EventArray[i] = EventArray[i + 1];
	}
	nTotalSockets--;

	LeaveCriticalSection(&cs);
}

// ���� �Լ� ���� ��� �� ����
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(-1);
}

// ���� �Լ� ���� ���
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}