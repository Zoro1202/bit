#include "std.h"

vector<MEMBER*> g_member;

HWND g_hdlg;
TCHAR g_id[20];

//초기화
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

//----------------모달창에서 쓰는 것들---------------
void con_InsertMember_Modal(HWND hdlg)
{
	MEMBER temp_data;
	INT_PTR ret = DialogBoxParam(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2), hdlg ,ModalProc, (LPARAM)&temp_data);
	if (ret == IDOK)
	{
		MEMBER* pmember = member_createmember(temp_data.id, temp_data.pw, temp_data.name, temp_data.phone, temp_data.age); // 문제 있음 // 해결함
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
	//멤버 검색 모달이 종료됨.
	g_hdlg = 0;
}

void con_OnApply(HWND hdlg)
{
	//멤버 검색 모달에서 select 버튼 누름.
	MEMBER* pmember = checkid(hdlg, g_id);
	MessageBox(hdlg, TEXT("성공"), TEXT("Apply"), MB_OK);
	ui_setSelectMember(hdlg, pmember);
}

void con_login(HWND hdlg)
{
	TCHAR id[20], pw[20];
	try
	{
		ui_getLoginData(hdlg, id, _countof(id), pw, _countof(pw));
		checkLogin(hdlg, id, pw);
		MessageBox(hdlg, TEXT("성공"), TEXT("select"), MB_OK);
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hdlg, msg, TEXT("login"), MB_OK);
	}
}
//----------------메인 창에서 쓰는 것들---------------

//메인 창에서 멤버 추가하기(회원가입)
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
		MEMBER* pmember = member_createmember(id, pw, name, phone, age); // 문제 있음 // 해결함
		MessageBox(hdlg, TEXT("성공"), TEXT("insert"), MB_OK);
		g_member.push_back(pmember);
		ui_printMember(hdlg, g_member);
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hdlg, msg, TEXT("register"), MB_OK);
	}
}
//[ui]검색정보 획득
//[control] 일치 여부 확인 -> 별도 함수로 처리
//          실패 메시지 출력
//			[ui]성공시 검색 결과 출력
void con_selectMember(HWND hdlg)
{
	TCHAR id[20];
	try
	{
		ui_getSelectData(hdlg, id, _countof(id));
		MEMBER * pmember = checkid(hdlg, id);
		MessageBox(hdlg, TEXT("성공"), TEXT("select"), MB_OK);
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
		MessageBox(hdlg, TEXT("성공"), TEXT("update"), MB_OK);
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
		MessageBox(hdlg, TEXT("성공"), TEXT("delete"), MB_OK);
		g_member.erase(g_member.begin()+i);
		ui_printMember(hdlg, g_member);
	}
	catch (const TCHAR* msg)
	{
		MessageBox(hdlg, msg, TEXT("delete"), MB_OK);
	}
}

//----------------------

//로그인 시 체크
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
	throw TEXT("idpw불일치");
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
	throw TEXT("id불일치");
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
	throw TEXT("id불일치");
}