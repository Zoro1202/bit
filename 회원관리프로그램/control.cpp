//control.cpp
#include "std.h"

MEMBER g_curmember; // global value : shape
vector<MEMBER> g_member;

HWND hEditName, hBtnM, hBtnFM, hEditHP, hBtnSave, hBtnM_Sel, hBtnFM_Sel, hEditHP_Sel, hEditName_Sel, hBtnPrintall, hBtnDel;//입력 박스들
HWND hListBox1; // vector 값을 여기 저장

void con_init(HWND hwnd)
{
	member_setMember(&g_curmember, TEXT("김민석"), 0, TEXT("010-1234-5678"));
	g_member.push_back(g_curmember);
	member_setMember(&g_curmember, TEXT("이민재"), 0, TEXT("010-9245-9439"));
	g_member.push_back(g_curmember);
	member_setMember(&g_curmember, TEXT("김민재"), 0, TEXT("010-5245-7439"));
	g_member.push_back(g_curmember);
}

void con_insert(HWND hwnd)
{
	TCHAR name[64];
	int gender;
	TCHAR phone[64];
	if(!GetWindowText(hEditName, name, 64)) return;
	if (SendMessage(hBtnM, BM_GETCHECK, 0, 0)) gender = 1;
	else if (SendMessage(hBtnFM, BM_GETCHECK, 0, 0)) gender = 0;
	else return;
	if(!GetWindowText(hEditHP, phone, 64)) return;
	MEMBER tmemp;
	member_setMember(&tmemp, name, gender, phone);
	g_member.push_back(tmemp);
	int index = (int)g_member.size() - 1;
	SetWindowText(hEditName_Sel, g_member[index].name);
	if (g_member[index].gender == 1) {
		SendMessage(hBtnM_Sel, BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(hBtnFM_Sel, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else {
		SendMessage(hBtnM_Sel, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(hBtnFM_Sel, BM_SETCHECK, BST_CHECKED, 0);
	}
	SetWindowText(hEditHP_Sel, g_member[index].phone);
}

void con_printall(HWND hwnd)
{
	SendMessage(hListBox1, LB_RESETCONTENT, 0, 0);
	for (int i = 0; i < g_member.size(); i++)
	{
		TCHAR buf[128];
		wsprintf(buf, TEXT("%s %s %s"), 
			g_member[i].name, 
			g_member[i].gender == 1 ? TEXT("남") : TEXT("여"),
			g_member[i].phone);
		SendMessage(hListBox1, LB_ADDSTRING, 0, (LPARAM)buf);
	}
}

void con_select(HWND hwnd)
{
	int index = (int)SendMessage(hListBox1, LB_GETCURSEL, 0, 0);
	if (index == LB_ERR) {
		SetWindowText(hEditName_Sel, NULL);
		SendMessage(hBtnM_Sel, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(hBtnFM_Sel, BM_SETCHECK, BST_UNCHECKED, 0);
		SetWindowText(hEditHP_Sel, NULL);
		return;
	}
	g_curmember = g_member[index];
	SetWindowText(hEditName_Sel, g_member[index].name);
	if (g_member[index].gender == 1) {
		SendMessage(hBtnM_Sel, BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(hBtnFM_Sel, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else {
		SendMessage(hBtnM_Sel, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(hBtnFM_Sel, BM_SETCHECK, BST_CHECKED, 0);
	}
	SetWindowText(hEditHP_Sel, g_member[index].phone);
}

void con_delete(HWND hwnd)
{
	if (g_member.size() <= 0) return;
	int ret;
	vector<MEMBER>::iterator imem;
	for (imem = g_member.begin(); imem != g_member.end(); ) {
		MEMBER tmemp = *imem;
		ret = memcmp(&tmemp, &g_curmember, sizeof(tmemp));
		if (ret == 0) {
			imem = g_member.erase(imem);
			//g_member.pop_back();
			break;
		}
		else {
			++imem;
		}
	}
	// ----------  삭제 하면 검색창 초기화 ----------------
	SetWindowText(hEditName_Sel, NULL);
	SendMessage(hBtnM_Sel, BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(hBtnFM_Sel, BM_SETCHECK, BST_UNCHECKED, 0);
	SetWindowText(hEditHP_Sel, NULL);
	// --------------------------------------------------
	con_printall(hwnd);
}

void con_printControls(HWND hwnd)
{
	//----------------입력 박스---------------
	//그룹 박스
	CreateWindow(TEXT("button"), TEXT("입력"), WS_CHILD | WS_VISIBLE |
		BS_GROUPBOX, 5, 5, 300, 400, hwnd, (HMENU)0, 0, NULL);
	//name
	CreateWindow(TEXT("static"), TEXT("이름"), WS_CHILD | WS_VISIBLE,
		20, 40, 90, 20, hwnd, (HMENU)-1, 0, NULL);
	hEditName = CreateWindow(TEXT("Edit"), TEXT(""),
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		120, 40, 90 + 30, 20, hwnd, (HMENU)IDC_EDIT, 0, 0);
	// gender
	//남
	CreateWindow(TEXT("static"), TEXT("성별"), WS_CHILD | WS_VISIBLE,
		20, 70, 90, 20, hwnd, (HMENU)-1, 0, NULL);
	hBtnM = CreateWindow(TEXT("button"), TEXT("남"), BS_AUTORADIOBUTTON  | WS_GROUP | WS_CHILD | WS_VISIBLE ,
		120, 70, 40, 20, hwnd, (HMENU)IDC_RADIO_M, 0, NULL);
	//여
	hBtnFM = CreateWindow(TEXT("button"), TEXT("여"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		170, 70, 40, 20, hwnd, (HMENU)IDC_RADIO_F, 0, NULL);
	CheckRadioButton(hwnd, IDC_RADIO_M, IDC_RADIO_F, IDC_RADIO_M);
	//phone
	CreateWindow(TEXT("static"), TEXT("전화번호"), WS_CHILD | WS_VISIBLE,
		20, 100, 90, 20, hwnd, (HMENU)-1, 0, NULL);
	hEditHP = CreateWindow(TEXT("Edit"), TEXT(""),
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		120, 100, 90 + 30, 20, hwnd, (HMENU)IDC_EDIT, 0, 0);
	//button
	hBtnSave = CreateWindow(TEXT("button"), TEXT("저장하기"), WS_CHILD | WS_VISIBLE |
		BS_PUSHBUTTON, 140, 150, 100, 25, hwnd, (HMENU)IDC_SAVE, 0, NULL);
	//-------------검색 박스------------------
	//그룹박스
	CreateWindow(TEXT("button"), TEXT("검색"), WS_CHILD | WS_VISIBLE |
		BS_GROUPBOX, 400, 5, 300, 400, hwnd, (HMENU)1, 0, NULL);
	//name
	CreateWindow(TEXT("static"), TEXT("이름"), WS_CHILD | WS_VISIBLE,
		20 + 395, 40, 90, 20, hwnd, (HMENU)-1, 0, NULL);
	hEditName_Sel = CreateWindow(TEXT("Edit"), TEXT(""),
		WS_CHILD | WS_BORDER | WS_VISIBLE | WS_DISABLED,
		120 + 395, 40, 90 + 30, 20, hwnd, (HMENU)IDC_EDIT, 0, 0);
	// gender
	//남
	CreateWindow(TEXT("static"), TEXT("성별"), WS_CHILD | WS_VISIBLE,
		20 + 395, 70, 90, 20, hwnd, (HMENU)-1, 0, NULL);
	hBtnM_Sel = CreateWindow(TEXT("button"), TEXT("남"), WS_CHILD | WS_VISIBLE |
		BS_AUTORADIOBUTTON | WS_GROUP | WS_DISABLED,
		120 + 395, 70, 40, 20, hwnd, (HMENU)IDC_RADIO, 0, NULL);
	//여
	hBtnFM_Sel = CreateWindow(TEXT("button"), TEXT("여"), WS_CHILD | WS_VISIBLE |
		BS_AUTORADIOBUTTON | WS_DISABLED,
		170 + 395, 70, 40, 20, hwnd, (HMENU)IDC_RADIO, 0, NULL);
	//phone
	CreateWindow(TEXT("static"), TEXT("전화번호"), WS_CHILD | WS_VISIBLE,
		20 + 395, 100, 90, 20, hwnd, (HMENU)-1, 0, NULL);
	hEditHP_Sel = CreateWindow(TEXT("Edit"), TEXT(""),
		WS_CHILD | WS_BORDER | WS_VISIBLE | WS_DISABLED,
		120 + 395, 100, 90 + 30, 20, hwnd, (HMENU)IDC_EDIT, 0, 0);
	hBtnDel = CreateWindow(TEXT("button"), TEXT("삭제하기"), WS_CHILD | WS_VISIBLE |
		BS_PUSHBUTTON, 140 + 395, 150, 100, 25, hwnd, (HMENU)IDC_DELBTN, 0, NULL);
	// ---------------멤버 리스트 박스 ----------------
	hListBox1 = CreateWindow(TEXT("listbox"), 0,
		WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
		800, 10, 300, 400, hwnd, (HMENU)IDC_LISTBOX, 0, 0);
	hBtnPrintall = CreateWindow(TEXT("button"), TEXT("전체 출력"), WS_CHILD | WS_VISIBLE |
		BS_PUSHBUTTON, 900, 420, 100, 25, hwnd, (HMENU)IDC_LISTBTN, 0, NULL);
}