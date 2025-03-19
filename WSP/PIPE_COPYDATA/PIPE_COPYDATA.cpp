#pragma comment (linker, "/subsystem:windows")

#include <Windows.h>
#include <tchar.h>

#include "resource.h"

typedef struct tagPACKETDATA
{
	TCHAR name[20];
	TCHAR msg[100];
	SYSTEMTIME st;
}PACKETDATA, *PPACKETDATA;

HWND hwnd;

void ipc_pipe_init(HWND hdlg)
{
	TCHAR name[20];
	GetDlgItemText(hdlg, IDC_EDIT1, name, _countof(name));
	
	hwnd = FindWindow(0, name);
}

void ipc_setWinTitle(HWND hdlg)
{
	TCHAR name[20];
	GetDlgItemText(hdlg, IDC_EDIT2, name, _countof(name));

	SetWindowText(hdlg, name);
}

void ipc_sendMessage(HWND hdlg)
{
	PACKETDATA mydata;
	GetDlgItemText(hdlg, IDC_EDIT3, mydata.msg, _countof(mydata.msg));
	GetWindowText(hdlg, mydata.name, _countof(mydata.name));
	SYSTEMTIME st;
	GetLocalTime(&st);
	mydata.st = st;

	TCHAR buf[200];
	wsprintf(buf, TEXT("[%s]%s (%02d:%02d:%02d)"), mydata.name, mydata.msg, st.wHour, st.wMinute, st.wSecond);

	DWORD l, r;
	HWND hedit = GetDlgItem(hdlg, IDC_EDIT4);
	SendMessage(hedit, EM_GETSEL, (WPARAM)&l, (LPARAM)&r); //내창에 띄우기
	SendMessage(hedit, EM_REPLACESEL, (WPARAM)r, (LPARAM)buf);
	SendMessage(hedit, EM_REPLACESEL, (WPARAM)r + _countof(buf), (LPARAM)L"\r\n");
	
	//전송
	COPYDATASTRUCT data;
	data.cbData = sizeof(PACKETDATA);
	data.dwData = 1;
	data.lpData = &mydata;

	SendMessage(hwnd, WM_COPYDATA, (WPARAM)hdlg, (LPARAM)&data);

}

void ipc_recvMessage(HWND hdlg, WPARAM wParam, LPARAM lParam)
{
	hwnd = (HWND)wParam;
	COPYDATASTRUCT *cds;
	cds = (COPYDATASTRUCT*)lParam;
	PACKETDATA *pd = (PACKETDATA*)cds->lpData;

	TCHAR buf[200];
	wsprintf(buf, TEXT("[%s]%s (%02d:%02d:%02d)"), pd->name, pd->msg, pd->st.wHour, pd->st.wMinute, pd->st.wSecond);

	HWND hedit = GetDlgItem(hdlg, IDC_EDIT4);
	DWORD l, r;
	SendMessage(hedit, EM_GETSEL, (WPARAM)&l, (LPARAM)&r); //내창에 띄우기
	SendMessage(hedit, EM_REPLACESEL, (WPARAM)r, (LPARAM)buf);
	SendMessage(hedit, EM_REPLACESEL, (WPARAM)r + _tcslen(buf), (LPARAM)TEXT("\r\n"));
	SetFocus(GetDlgItem(hwnd, IDC_EDIT4));
}

INT_PTR CALLBACK DlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hProcess2;
	switch (msg)
	{
	case WM_COPYDATA:
	{
		ipc_recvMessage(hdlg, wParam, lParam);


		return 0;
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