//control.cpp
#include "std.h"

vector<MEMBER> g_members;
//g_members의 주소의 타입 : vector<MEMBER>*
void con_init()
{
	net_initlibrary();
	
	net_create_socket(9000);
}

void con_run()
{
	HANDLE hThread;
	hThread = CreateThread(0, 0, listen_thread, &g_members, 0, 0);

	WaitForSingleObject(hThread, INFINITE);
	//send_data( s,  buf, len, flag);
	//recvn(s, buf, len, flag);
}

void con_exit()
{
	net_delete_socket();
	net_exitlibrary();
}