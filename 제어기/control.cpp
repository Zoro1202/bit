//control.cpp
#include "std.h"

void con_init(HWND hdlg)
{
	ui_GetControlHandle(hdlg);
	ui_InitDataControl(hdlg);
	ipc_init(hdlg);  
}

void con_ipc_new(HWND hdlg)
{
	ipc_new(hdlg);
}

void con_ipc_exit(HWND hdlg)
{
	ipc_exit(hdlg);
}

void con_ipc_color(HWND hdlg)
{
	ipc_color(hdlg, ui_getColor(hdlg));
}

void con_ipc_Point(HWND hdlg, WPARAM w)
{
	POINT pt = ui_getPosition(hdlg);
	if (w == IDC_BUTTON4) 
	{
		pt.y -= 5;
		ui_setPosition(hdlg, pt.x, pt.y);
		ipc_up(hdlg);
	}
	else if (w == IDC_BUTTON7) 
	{
		pt.y += 5;
		ui_setPosition(hdlg, pt.x, pt.y);
		ipc_down(hdlg);
	}
	else if (w == IDC_BUTTON5) 
	{
		pt.x -= 5;
		ui_setPosition(hdlg, pt.x, pt.y);
		ipc_left(hdlg);
	}
	else if (w == IDC_BUTTON6) 
	{
		pt.x += 5;
		ui_setPosition(hdlg, pt.x, pt.y);
		ipc_right(hdlg);
	}
}
