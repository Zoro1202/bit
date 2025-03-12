#include "std.h"
/*
WM_MYSHOW
w : 핸들
l : 1 or 0
WM_MYCOLOR
w : 핸들
l : RGB
WM_MYPOSITION
w : 핸들
l : 1, 2, 3, 4
*/
#define WM_MYSHOW WM_USER + 101
#define WM_MYCOLOR WM_USER + 102
#define WM_MYPOSITION WM_USER + 103
HWND ipc;
void ipc_init(HWND hdlg)
{
	ipc = FindWindow(0, TEXT("ipccc"));
	if (ipc == NULL) MessageBox(hdlg, TEXT("찾을수없음"), TEXT("창"), MB_OK);
	else if (ipc != NULL) MessageBox(hdlg, TEXT("찾음"), TEXT("창"), MB_OK);
}
void ipc_new(HWND hdlg)
{
	//SendMessage
	BOOL ret = SendMessage(ipc, WM_MYSHOW, (WPARAM)hdlg, (LPARAM)1);
}
void ipc_exit(HWND hdlg)
{
	BOOL ret = PostMessage(ipc, WM_MYSHOW, (WPARAM)hdlg, (LPARAM)0);
}
void ipc_color(HWND hdlg, COLORREF color)
{
	BOOL ret = PostMessage(ipc, WM_MYCOLOR, (WPARAM)hdlg, (LPARAM)color);
}
void ipc_up(HWND hdlg)
{
	BOOL ret = PostMessage(ipc, WM_MYPOSITION, (WPARAM)hdlg, (LPARAM)1);
}
void ipc_down(HWND hdlg)
{
	BOOL ret = PostMessage(ipc, WM_MYPOSITION, (WPARAM)hdlg, (LPARAM)2);
}
void ipc_right(HWND hdlg)
{
	BOOL ret = PostMessage(ipc, WM_MYPOSITION, (WPARAM)hdlg, (LPARAM)3);
}
void ipc_left(HWND hdlg)
{
	BOOL ret = PostMessage(ipc, WM_MYPOSITION, (WPARAM)hdlg, (LPARAM)4);
}