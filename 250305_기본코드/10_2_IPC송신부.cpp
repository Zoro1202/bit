//10_2_IPC송신부.cpp
#pragma comment (linker, "/subsystem:console")


#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

#define WM_MYMESSAGE WM_USER+101 // wParam : x좌표 , lParam : y좌표

int main()
{
	HWND h = FindWindow(0, TEXT("IPC 수신부"));

	if (h != 0)
	{
		printf("찾음\n");
		while (1) {
			int x, y;
			printf("전송할 X값 입력 : ");
			scanf_s("%d", &x);
			printf("전송할 Y값 입력 : ");
			scanf_s("%d", &y);
			
			BOOL ret = PostMessage(h, WM_MYMESSAGE, x, y);
			if (ret == true)
			{
				printf("상대방의 메시지 큐에 잘 전달했다\n\n");
			}
			else {
				printf("전달 오류 \n\n");
			}

		}
	}
	else {
		printf("못찾음\n");
	}

	return 0;
}