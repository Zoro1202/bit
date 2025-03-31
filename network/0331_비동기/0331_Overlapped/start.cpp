#include <stdio.h>

#include "overlapped1.h"

int main(int argc, char* argv[])
{
	if (net_initSocket() == -1)
	{
		printf("초기화 오류\n");
		return -1;
	}
	
	net_run();

	net_exit();
	
	return 0;
}
