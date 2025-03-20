#include "std.h"

vector<MEMBER*> g_member;

HWND g_hdlg;
TCHAR g_id[20];

//�ʱ�ȭ
void con_init(HWND hdlg)
{
	ui_initControl(hdlg);
}
//file
void con_savefile(HWND hdlg)
{
	file_save(g_member);
}
void con_loadfile(HWND hdlg)
{
	file_load(g_member);
	ui_printMember(hdlg, g_member);
}

//file Dialog
void con_fileOpenDial(HWND hdlg)
{
	file_dlg_open(hdlg, g_member);
	ui_printMember(hdlg, g_member);
}
void con_fileSaveDial(HWND hdlg)
{
	file_dlg_save(hdlg, g_member);
	ui_printMember(hdlg, g_member);
}

//----------------���â���� ���� �͵�---------------
void con_InsertMember_Modal(HWND hdlg)
{
	MEMBER temp_data;
	INT_PTR ret = DialogBoxParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2), hdlg ,ModalProc, (LPARAM)&temp_data);
	if (ret == IDOK)
	{
		MEMBER* pmember = member_createmember(temp_data.id, temp_data.pw, temp_data.name, temp_data.phone, temp_data.age); // ���� ���� // �ذ���
		g_member.push_back(pmember);
		ui_printMember(hdlg, g_member);
	}
}

void con_selectMember_Modaless(HWND hdlg)
{
	if (g_hdlg == 0)
	{
		g_hdlg = CreateDialogParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG3), hdlg, ModalselectProc, (LPARAM)g_id);
		ShowWindow(g_hdlg, SW_SHOW);
	}
	else
	{
		SetFocus(g_hdlg);
	}
}

void con_OnChildDestroy(HWND hdlg)
{
	//��� �˻� ����� �����.
	g_hdlg = 0;
}

void con_OnApply(HWND hdlg)
{
	//��� �˻� ��޿��� select ��ư ����.
	MEMBER* pmember = checkid(hdlg, g_id);
	MessageBox(hdlg, TEXT("����"), TEXT("Apply"), MB_OK);
	ui_setSelectMember(hdlg, pmember);
}

void con_login(HWND hdlg)
{
	TCHAR id[20], pw[20];
	try
	{
		ui_getLoginData(hdlg, id, _countof(id), pw, _countof(pw));
		checkLogin(hdlg, id, pw);
		MessageBox(hdlg, TEXT("����"), TEXT("select"), MB_OK);
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hdlg, msg, TEXT("login"), MB_OK);
	}
}
//----------------���� â���� ���� �͵�---------------

//���� â���� ��� �߰��ϱ�(ȸ������)
void con_insertMember(HWND hdlg)
{
	TCHAR id[20], pw[20], name[20], phone[20];
	int age = 0;
	try
	{
		ui_getMemberData(hdlg,
			id, _countof(id),
			pw, _countof(pw),
			name, _countof(name),
			phone, _countof(phone),
			&age);
		MEMBER* pmember = member_createmember(id, pw, name, phone, age); // ���� ���� // �ذ���
		MessageBox(hdlg, TEXT("����"), TEXT("insert"), MB_OK);
		g_member.push_back(pmember);
		ui_printMember(hdlg, g_member);
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hdlg, msg, TEXT("register"), MB_OK);
	}
}
//[ui]�˻����� ȹ��
//[control] ��ġ ���� Ȯ�� -> ���� �Լ��� ó��
//          ���� �޽��� ���
//			[ui]������ �˻� ��� ���
void con_selectMember(HWND hdlg)
{
	TCHAR id[20];
	try
	{
		ui_getSelectData(hdlg, id, _countof(id));
		MEMBER * pmember = checkid(hdlg, id);
		MessageBox(hdlg, TEXT("����"), TEXT("select"), MB_OK);
		ui_setSelectMember(hdlg, pmember);
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hdlg, msg, TEXT("select"), MB_OK);
	}
}

void con_updateMember(HWND hdlg)
{
	TCHAR id[20],phone[20];
	int age;
	try
	{
		ui_getUpdateData(hdlg, id, _countof(id), phone, _countof(phone), &age); 
		MEMBER *pmember = checkid(hdlg, id);
		MessageBox(hdlg, TEXT("����"), TEXT("update"), MB_OK);
		member_setdata(pmember, phone, age);
		ui_printMember(hdlg, g_member);
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hdlg, msg, TEXT("update"), MB_OK);
	}
}

void con_deleteMember(HWND hdlg)
{
	TCHAR id[20];
	try
	{
		ui_getSelectData(hdlg, id, _countof(id));
		int i = checkid_idx(hdlg, id);
		MessageBox(hdlg, TEXT("����"), TEXT("delete"), MB_OK);
		g_member.erase(g_member.begin()+i);
		ui_printMember(hdlg, g_member);
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hdlg, msg, TEXT("delete"), MB_OK);
	}
}

//----------------------

//�α��� �� üũ
MEMBER *checkLogin(HWND hdlg, TCHAR* id, TCHAR* pw)
{
	for (int i = 0; i < g_member.size(); i++)
	{
		MEMBER* pmember = g_member[i];
		if (_tcscmp(pmember->id, id) == 0 && _tcscmp(pmember->pw, pw) == 0)
		{
			return pmember;
		}
	}
	throw TEXT("idpw����ġ");
}
//id check to member
MEMBER* checkid(HWND hdlg, TCHAR* id)
{
	for (int i = 0; i < g_member.size(); i++)
	{
		MEMBER* pmember = g_member[i];
		if (_tcscmp(pmember->id, id) == 0)
		{
			return pmember;
		}
	}
	throw TEXT("id����ġ");
}
//id check to idx
int checkid_idx(HWND hdlg, TCHAR* id)
{
	for (int i = 0; i < g_member.size(); i++)
	{
		MEMBER* pmember = g_member[i];
		if (_tcscmp(pmember->id, id) == 0)
		{
			return i;
		}
	}
	throw TEXT("id����ġ");
}