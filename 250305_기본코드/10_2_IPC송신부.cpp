//10_2_IPC�۽ź�.cpp
#pragma comment (linker, "/subsystem:console")


#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

#define WM_MYMESSAGE WM_USER+101 // wParam : x��ǥ , lParam : y��ǥ

int main()
{
	HWND h = FindWindow(0, TEXT("IPC ���ź�"));

	if (h != 0)
	{
		printf("ã��\n");
		while (1) {
			int x, y;
			printf("������ X�� �Է� : ");
			scanf_s("%d", &x);
			printf("������ Y�� �Է� : ");
			scanf_s("%d", &y);
			
			BOOL ret = PostMessage(h, WM_MYMESSAGE, x, y);
			if (ret == true)
			{
				printf("������ �޽��� ť�� �� �����ߴ�\n\n");
			}
			else {
				printf("���� ���� \n\n");
			}

		}
	}
	else {
		printf("��ã��\n");
	}

	return 0;
}