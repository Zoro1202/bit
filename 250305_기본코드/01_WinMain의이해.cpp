//01_WinMain������.cpp
// windows - ��Ƽ����Ʈ ȯ��

/*�⺻: console
* ������Ʈ - �Ӽ� - ��Ŀ - �ý��� - ���� �ý���  :  console or windows
console : main
gui		: WinMain
*/

// �⺻ : unicode
// ������Ʈ - ���� - ���� �Ӽ� - ��� - ���� ���� : �����ڵ� or ��Ƽ����Ʈ
// �����ڵ�   : wchar, wchar*
// ��Ƽ����Ʈ : char,  char*
#include <Windows.h>
/*
HINSTANCE : �ν��Ͻ� �ڵ�. ���α׷� ��ü�� ���´� ������. ���α׷� ���� -> �޸� ���� -> �ν��Ͻ� ����
		��, �ν��Ͻ��� ������ ���α׷�(���μ���)�� �ڵ��̴�.
*/
int WinMain(HINSTANCE hInst, HINSTANCE hprevInst, LPSTR cmdLine, int showcmd)
{
	MessageBoxA(NULL, "Hello,API", "FIRST", MB_YESNO | MB_ICONQUESTION); //NULL, ����, ĸ��, �޽����ڽ� �÷��� |(or) ������ (��Ʈ�������� �Ѱ� �� �� ����)
																			//#define MB_OK                       0x00000000L
																			//#define MB_OKCANCEL                 0x00000001L
																			//#define MB_ABORTRETRYIGNORE         0x00000002L
																			//#define MB_YESNOCANCEL              0x00000003L
																			//#define MB_YESNO                    0x00000004L
																			//#define MB_RETRYCANCEL              0x00000005L

																			//#define MB_ICONHAND                 0x00000010L
																			//#define MB_ICONQUESTION             0x00000020L
																			//#define MB_ICONEXCLAMATION          0x00000030L
																			//#define MB_ICONASTERISK             0x00000040L
	return 0;
}