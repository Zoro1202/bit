//dll암시적사용
/*
실행파일 실행 시 dll이 자동으로 실행파일의 메모리에 load
실행파일 종료 시 dll이 자동으로 실행파일의 메모리에 unload

개발단계 : .h, .dll, .lib 를 한 곳에 두고 빌드해야 함
배포단계 : .dll 파일만 실행파일과 같이 있으면 됨
*/
#include <stdio.h>
#include "mycal.h"

#pragma comment(lib, "Dll_mycal.lib")

int main()
{
	printf("%.1f\n", mycal_add(10, 20));
	printf("%.1f\n", mycal_min(10, 20));
	printf("%.1f\n", mycal_mul(10, 20));
	printf("%.1f\n", mycal_div(10, 20));

	printf("%.1f\n", mycal_sample(10, 20));

	char dummy = getchar();

	return 0;
}