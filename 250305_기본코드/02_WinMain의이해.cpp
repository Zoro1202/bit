//02_WinMain������.cpp
//windows - �����ڵ� ȯ��

//1. ������Ʈ -> �Ӽ� -> ��Ŀ -> �ý��� : ���� �ý��� -> windows or console
//2. ������Ʈ -> �Ӽ� -> ��� -> ���� : ��Ƽ����Ʈ or �����ڵ�
#include <Windows.h>

int wWinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPWSTR cmdline, int showcmd)
{
	MessageBoxW(NULL, L"Hello,API", L"FIRST", MB_YESNO | MB_ICONQUESTION); //NULL, ����, ĸ��, �޽����ڽ� �÷��� |(or) ������ (��Ʈ�������� �Ѱ� �� �� ����)

	return 0;
}