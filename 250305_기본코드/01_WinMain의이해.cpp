//01_WinMain의이해.cpp
// windows - 멀티바이트 환경

/*기본: console
* 프로젝트 - 속성 - 링커 - 시스템 - 하위 시스템  :  console or windows
console : main
gui		: WinMain
*/

// 기본 : unicode
// 프로젝트 - 설정 - 구성 속성 - 고급 - 문자 집합 : 유니코드 or 멀티바이트
// 유니코드   : wchar, wchar*
// 멀티바이트 : char,  char*
#include <Windows.h>
/*
HINSTANCE : 인스턴스 핸들. 프로그램 자체를 일컫는 정수값. 프로그램 실행 -> 메모리 생성 -> 인스턴스 생성
		즉, 인스턴스는 생성된 프로그램(프로세스)의 핸들이다.
*/
int WinMain(HINSTANCE hInst, HINSTANCE hprevInst, LPSTR cmdLine, int showcmd)
{
	MessageBoxA(NULL, "Hello,API", "FIRST", MB_YESNO | MB_ICONQUESTION); //NULL, 내용, 캡션, 메시지박스 플래그 |(or) 아이콘 (비트연산으로 켜고 끌 수 있음)
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