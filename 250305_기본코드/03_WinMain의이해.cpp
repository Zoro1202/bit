//03_WinMain������.cpp
//����Ÿ�� ���
// ��Ƽ����Ʈ   : char	    "aaa"
// �����ڵ�(w)  : wchar_t	L"aaa"
// ����Ÿ��(t)  : TCHAR	    TEXT("aaa")

// windows - �����ڵ峪 ��Ƽ����Ʈ ȯ�� ��ο��� ������ ����� �Ѵ�.
#pragma comment (linker, "/subsystem:windows")
//#pragma comment (linker, "/subsystem:console")
#include <Windows.h>
#include <tchar.h>
// WINAPI == __stdcall
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPTSTR cmdline, int showcmd)
{
	MessageBox(NULL, TEXT("Hello, API"), TEXT("FIRST"), MB_YESNO | MB_ICONQUESTION); //NULL, ����, ĸ��, �޽����ڽ� �÷��� |(or) ������ (��Ʈ�������� �Ѱ� �� �� ����)

	return 0;
}