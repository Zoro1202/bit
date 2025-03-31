#pragma once
#include <stdio.h>
#include "Event_server.h"
#include <windows.h>


struct LINE
{
	POINTS ptFrom;
	POINTS ptTo;
};

int main()
{
	if (net_initSocket() == false)
	{
		printf("대기 소켓 오류\n");
		return -1;
	}

	net_run();


	net_exitSocket();

	return 0;
}


