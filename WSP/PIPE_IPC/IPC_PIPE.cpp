#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

#include "resource.h"

#define WM_USER_PIPE WM_USER + 101
#define WM_USER_SENDMESSAGE WM_USER + 102
#define WM_USER_IMYOURMASTER WM_USER + 103
#define WM_USER_YESMASTER WM_USER + 104


HWND hservo; // 상대방 핸들한테 메시지 보내려고 가지고 있을거임
HANDLE hRead1, hRead2;
HANDLE hWrite1, hWrite2;

BOOL isImSlave = FALSE;

void ipc_pipe_init(HWND hdlg)
{
	TCHAR name[20];
	GetDlgItemText(hdlg, IDC_EDIT1, name, _countof(name));
	//파이프 생성
	//윈도우 이름 >> 윈도우 핸들 HWND  >> PID >> 프로세서 HANDLE
	//창의 이름으로 핸들 얻어오기
	hservo = FindWindow(0, name);
	//핸들으로 PID 가져오기 겸사겸사 TID도(스레드 아이디, 쓸모없다)
	DWORD pid;
	DWORD tid = GetWindowThreadProcessId(hservo, &pid);
	//PID로 프로세서 핸들 얻기
	HANDLE hProcessor = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

	BOOL b = CreatePipe(&hRead1, &hWrite1, 0, 4096);
	if (!b) {
		MessageBox(NULL, _T("파이프 생성 실패!"), _T("오류"), MB_OK);
		CloseHandle(hRead1); // 핸들들 삭제
		CloseHandle(hWrite1);
		CloseHandle(hProcessor);
		return;
	}
	b = CreatePipe(&hRead2, &hWrite2, 0, 4096);
	if (!b) {
		MessageBox(NULL, _T("파이프 생성 실패!"), _T("오류"), MB_OK);
		CloseHandle(hRead2); // 핸들들 삭제
		CloseHandle(hWrite2);
		CloseHandle(hProcessor);
		return;
	}

	HANDLE sendRead, sendWrite;
	b = DuplicateHandle(GetCurrentProcess(), hRead1, hProcessor, &sendRead, 0, FALSE, DUPLICATE_SAME_ACCESS);
	if (!b) {
		MessageBox(NULL, _T("DuplicateReadHandle 실패!"), _T("오류"), MB_OK);
		CloseHandle(hRead1); // 핸들들 삭제
		CloseHandle(hWrite1);
	}
	//CloseHandle(hRead1);
	b = DuplicateHandle(GetCurrentProcess(), hWrite2, hProcessor, &sendWrite, 0, FALSE, DUPLICATE_SAME_ACCESS);
	if (!b) {
		MessageBox(NULL, _T("DuplicateWriteHandle 실패!"), _T("오류"), MB_OK);
		CloseHandle(hRead2); // 핸들들 삭제
		CloseHandle(hWrite2);
		CloseHandle(hProcessor);
		return;
	}
	CloseHandle((isImSlave) ? hWrite1 : hWrite2);
	CloseHandle((isImSlave) ? hRead2 : hRead1);
	SendMessage(hservo, WM_USER_PIPE, (WPARAM)sendWrite, (LPARAM)sendRead);
	SendMessage(hservo, WM_USER_IMYOURMASTER, 0, (LPARAM)hdlg);
	CloseHandle(hProcessor);

}

void ipc_pipe_initservo(HWND hdlg, HWND master)
{
	if ((__int64)master < 0)
	{
		isImSlave = FALSE;
	}
	hservo = master;
	HWND hBtn = GetDlgItem(hdlg, IDC_BUTTON1);
	EnableWindow(hBtn, FALSE);
}

void ipc_setWinTitle(HWND hdlg)
{
	TCHAR name[20];
	GetDlgItemText(hdlg, IDC_EDIT2, name, _countof(name));

	SetWindowText(hdlg, name);
}

void ipc_sendMessage(HWND hdlg)
{
	TCHAR msg[100];
	GetDlgItemText(hdlg, IDC_EDIT3, msg, _countof(msg));
	TCHAR name[20];
	GetWindowText(hdlg, name, _countof(name));

	SYSTEMTIME st;
	GetLocalTime(&st);

	HANDLE wh = (!isImSlave) ? hWrite1 : hWrite2;

	TCHAR buf[200];
	wsprintf(buf, TEXT("[%s]%s (%02d:%02d:%02d)"), name, msg, st.wHour, st.wMinute, st.wSecond);

	DWORD bytesWritten;
	BOOL b = WriteFile(wh, buf, _tcslen(buf) * sizeof(TCHAR), &bytesWritten, NULL);
	if (b)
	{
		//MessageBox(hdlg, TEXT("안녕..?"), TEXT("창1"), MB_OK | MB_ICONWARNING); // 성공
	}
	else {
		//MessageBox(hdlg, TEXT("Tlqkf;"), TEXT("창1"), MB_OK | MB_ICONWARNING); // 실패
	}
	HWND hedit = GetDlgItem(hdlg, IDC_EDIT4);
	DWORD l, r;
	SendMessage(hservo, WM_USER_SENDMESSAGE, 0, 0); // 메시지 받아라! 라고 메시지 보내기!
	SendMessage(hedit, EM_GETSEL, (WPARAM)&l, (LPARAM)&r); //내창에 띄우기
	SendMessage(hedit, EM_REPLACESEL, (WPARAM)r, (LPARAM)buf);
	SendMessage(hedit, EM_REPLACESEL, (WPARAM)r + _countof(buf), (LPARAM)L"\r\n");
}

void ipc_recvMessage(HWND hdlg)
{
	TCHAR buf[4096];
	memset(buf, 0, 4096);
	DWORD bytesRead;
	HANDLE hr = (isImSlave) ? hRead1 : hRead2;
	BOOL b = ReadFile(hr, buf, 4096, &bytesRead, NULL);
	if (b)
	{
		//MessageBox(hdlg, TEXT("안녕..?"), TEXT("창1"), MB_OK | MB_ICONWARNING); // 성공
	}
	else {
		//MessageBox(hdlg, TEXT("Tlqkf;"), TEXT("창1"), MB_OK | MB_ICONWARNING); // 실패
	}
	HWND hedit = GetDlgItem(hdlg, IDC_EDIT4);
	DWORD l, r;
	SendMessage(hedit, EM_GETSEL, (WPARAM)&l, (LPARAM)&r); //내창에 띄우기
	SendMessage(hedit, EM_REPLACESEL, (WPARAM)r, (LPARAM)buf);
	SendMessage(hedit, EM_REPLACESEL, (WPARAM)r + _tcslen(buf), (LPARAM)TEXT("\r\n"));
	SetFocus(GetDlgItem(hservo, IDC_EDIT4));
}

INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hProcess2;
	switch (msg)
	{
	case WM_USER_IMYOURMASTER:
		ipc_pipe_initservo(hdlg, (HWND)lParam);
		return TRUE;
	case WM_USER_SENDMESSAGE:
	{
		ipc_recvMessage(hdlg);
		return TRUE;
	}
	case WM_USER_PIPE:
	{
		hWrite2 = (HANDLE)wParam;
		hRead1 = (HANDLE)lParam;
		isImSlave = TRUE;
		return 1;
	}
	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hdlg, &ps);


	//	EndPaint(hdlg, &ps);
	//	return TRUE;
	//}
	case WM_INITDIALOG:
	{
		
		return TRUE;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDCANCEL)
		{
			if (isImSlave)
			{
				CloseHandle(hWrite2);
				CloseHandle(hRead1);
			}
			else {
				CloseHandle(hWrite1);
				CloseHandle(hRead2);
				//버튼 다시 활성화 시켜주기
				HWND hBtn = GetDlgItem(hservo, IDC_BUTTON1);
				SendMessage(hservo, WM_USER_IMYOURMASTER, 0, -1);
				EnableWindow(hBtn, TRUE);
			}
			EndDialog(hdlg, IDCANCEL);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON1)
		{
			ipc_pipe_init(hdlg);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON2)
		{
			ipc_setWinTitle(hdlg);
			return TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON3)
		{
			ipc_sendMessage(hdlg);
			return TRUE;
		}
	}
	}

	return FALSE;
}

//시작 함수
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPTSTR cmdline, int showcmd)
{
	INT_PTR ret = DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc);

	return 0;
}