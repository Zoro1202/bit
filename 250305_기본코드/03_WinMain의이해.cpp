//03_WinMain의이해.cpp
//범용타입 사용
// 멀티바이트   : char	    "aaa"
// 유니코드(w)  : wchar_t	L"aaa"
// 범용타입(t)  : TCHAR	    TEXT("aaa")

// windows - 유니코드나 멀티바이트 환경 모두에서 에러가 없어야 한다.
#pragma comment (linker, "/subsystem:windows")
//#pragma comment (linker, "/subsystem:console")
#include <Windows.h>
#include <tchar.h>
// WINAPI == __stdcall
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPTSTR cmdline, int showcmd)
{
	MessageBox(NULL, TEXT("Hello, API"), TEXT("FIRST"), MB_YESNO | MB_ICONQUESTION); //NULL, 내용, 캡션, 메시지박스 플래그 |(or) 아이콘 (비트연산으로 켜고 끌 수 있음)

	return 0;
}