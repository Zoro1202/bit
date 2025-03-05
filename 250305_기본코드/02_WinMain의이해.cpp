//02_WinMain의이해.cpp
//windows - 유니코드 환경

//1. 프로젝트 -> 속성 -> 링커 -> 시스템 : 하위 시스템 -> windows or console
//2. 프로젝트 -> 속성 -> 고급 -> 문자 : 멀티바이트 or 유니코드
#include <Windows.h>

int wWinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPWSTR cmdline, int showcmd)
{
	MessageBoxW(NULL, L"Hello,API", L"FIRST", MB_YESNO | MB_ICONQUESTION); //NULL, 내용, 캡션, 메시지박스 플래그 |(or) 아이콘 (비트연산으로 켜고 끌 수 있음)

	return 0;
}