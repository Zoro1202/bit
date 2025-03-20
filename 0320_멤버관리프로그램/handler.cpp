//handler.cpp
#include "std.h"

BOOL OnInitDialog(HWND hdlg, WPARAM wParam, LPARAM lParam)
{
	con_init(hdlg);
	return TRUE;
}

BOOL OnCommand(HWND hdlg, WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(wParam) == IDCANCEL)
	{
		EndDialog(hdlg, IDCANCEL);
		return TRUE;
	}
	/// --------------------��ư------------------------
	else if (LOWORD(wParam) == IDC_BUTTON1) // ��� �Է� ��ư
	{
		con_insertMember(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON2) // �α��� ��ư
	{
		con_login(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON3) // ��� �˻�
	{
		con_selectMember(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON4) // ��� ���� ��ư
	{
		con_updateMember(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON5) // ��� ���� ��ư
	{
		con_deleteMember(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON6) // ���� ���� ��ư
	{
		con_savefile(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == IDC_BUTTON7) // ���� �ҷ����� ��ư
	{
		con_loadfile(hdlg);
		return TRUE;
	}
	///-------------------------�޴�--------------------------
	else if (LOWORD(wParam) == ID_40001) // ��� �ҷ�����
	{
		// ���� ���� ���̾�α�... ���� ���ϴ� ������ �о� ������
		con_fileOpenDial(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == ID_40002) // ��� ����
	{
		// ���� ���� ���̾�α�... ���� ���ϴ� ���Ͽ� ������ �� �ֵ���
		con_fileSaveDial(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == ID_40003) // ���α׷� ����
	{
		// ENDDialog
		SendMessage(hdlg, WM_CLOSE, 0, 0);
		return TRUE;
	}
	else if (LOWORD(wParam) == ID_40004) // ��� ����
	{
		// ��� â ����
		con_InsertMember_Modal(hdlg);
		return TRUE;
	}
	else if (LOWORD(wParam) == ID_40005) // ��� �˻�
	{
		//��޸��� â ����
		con_selectMember_Modaless(hdlg);
		return TRUE;
	}
	return FALSE;
}


BOOL OnChildDestroy(HWND hdlg)
{
	con_OnChildDestroy(hdlg);
	return TRUE;
}

BOOL OnAPPLY(HWND hdlg)
{
	//��� �˻� ��޿��� select ��ư ����
	con_OnApply(hdlg);
	return TRUE;
}
