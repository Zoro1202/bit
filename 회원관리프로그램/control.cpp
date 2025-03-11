//control.cpp
#include "std.h"

MEMBER g_curmember; // global value : shape
vector<MEMBER> g_member;

HWND hEdit1, hEdit2, hEdit3, hEdit4, hEdit5, hEdit6, hEdit7, hEdit8, hEdit9, hEdit10, hEdit11;//입력 박스들
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
	if(!GetWindowText(hEdit1, name, 64)) return;
	if (SendMessage(hEdit2, BM_GETCHECK, 0, 0)) gender = 1;
	else if (SendMessage(hEdit3, BM_GETCHECK, 0, 0)) gender = 0;
	else return;
	if(!GetWindowText(hEdit4, phone, 64)) return;
	MEMBER tmemp;
	member_setMember(&tmemp, name, gender, phone);
	g_member.push_back(tmemp);
	int index = g_member.size() - 1;
	SetWindowText(hEdit9, g_member[index].name);
	if (g_member[index].gender == 1) {
		SendMessage(hEdit6, BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(hEdit7, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else {
		SendMessage(hEdit6, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(hEdit7, BM_SETCHECK, BST_CHECKED, 0);
	}
	SetWindowText(hEdit8, g_member[index].phone);
}

void con_printall(HWND hwnd)
{
	SendMessage(hListBox1, LB_RESETCONTENT, 0, 0);
	for (int i = 0; i < g_member.size(); i++)
	{
		TCHAR buf[128];
		wsprintf(buf, TEXT("%s %c %s"), 
			g_member[i].name, 
			g_member[i].gender == 1 ? 'M' : 'F', 
			g_member[i].phone);
		SendMessage(hListBox1, LB_ADDSTRING, 0, (LPARAM)buf);
	}
}

void con_select(HWND hwnd)
{
	int index = SendMessage(hListBox1, LB_GETCURSEL, 0, 0);
	if (index == LB_ERR) {
		SetWindowText(hEdit9, NULL);
		SendMessage(hEdit6, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(hEdit7, BM_SETCHECK, BST_UNCHECKED, 0);
		SetWindowText(hEdit8, NULL);
		return;
	}
	g_curmember = g_member[index];
	SetWindowText(hEdit9, g_member[index].name);
	if (g_member[index].gender == 1) {
		SendMessage(hEdit6, BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(hEdit7, BM_SETCHECK, BST_UNCHECKED, 0);
	}
	else {
		SendMessage(hEdit6, BM_SETCHECK, BST_UNCHECKED, 0);
		SendMessage(hEdit7, BM_SETCHECK, BST_CHECKED, 0);
	}
	SetWindowText(hEdit8, g_member[index].phone);
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
	SetWindowText(hEdit9, NULL);
	SendMessage(hEdit6, BM_SETCHECK, BST_UNCHECKED, 0);
	SendMessage(hEdit7, BM_SETCHECK, BST_UNCHECKED, 0);
	SetWindowText(hEdit8, NULL);
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
	hEdit1 = CreateWindow(TEXT("Edit"), TEXT(""),
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		120, 40, 90 + 30, 20, hwnd, (HMENU)IDC_EDIT, 0, 0);
	// gender
	//남
	CreateWindow(TEXT("static"), TEXT("성별"), WS_CHILD | WS_VISIBLE,
		20, 70, 90, 20, hwnd, (HMENU)-1, 0, NULL);
	hEdit2 = CreateWindow(TEXT("button"), TEXT("남"), BS_AUTORADIOBUTTON  | WS_GROUP | WS_CHILD | WS_VISIBLE ,
		120, 70, 40, 20, hwnd, (HMENU)IDC_RADIO_M, 0, NULL);
	//여
	hEdit3 = CreateWindow(TEXT("button"), TEXT("여"), BS_AUTORADIOBUTTON | WS_CHILD | WS_VISIBLE,
		170, 70, 40, 20, hwnd, (HMENU)IDC_RADIO_F, 0, NULL);
	CheckRadioButton(hwnd, IDC_RADIO_M, IDC_RADIO_F, IDC_RADIO_M);
	//phone
	CreateWindow(TEXT("static"), TEXT("전화번호"), WS_CHILD | WS_VISIBLE,
		20, 100, 90, 20, hwnd, (HMENU)-1, 0, NULL);
	hEdit4 = CreateWindow(TEXT("Edit"), TEXT(""),
		WS_CHILD | WS_BORDER | WS_VISIBLE,
		120, 100, 90 + 30, 20, hwnd, (HMENU)IDC_EDIT, 0, 0);
	//button
	hEdit5 = CreateWindow(TEXT("button"), TEXT("저장하기"), WS_CHILD | WS_VISIBLE |
		BS_PUSHBUTTON, 140, 150, 100, 25, hwnd, (HMENU)IDC_SAVE, 0, NULL);
	//-------------검색 박스------------------
	//그룹박스
	CreateWindow(TEXT("button"), TEXT("검색"), WS_CHILD | WS_VISIBLE |
		BS_GROUPBOX, 400, 5, 300, 400, hwnd, (HMENU)1, 0, NULL);
	//name
	CreateWindow(TEXT("static"), TEXT("이름"), WS_CHILD | WS_VISIBLE,
		20 + 395, 40, 90, 20, hwnd, (HMENU)-1, 0, NULL);
	hEdit9 = CreateWindow(TEXT("Edit"), TEXT(""),
		WS_CHILD | WS_BORDER | WS_VISIBLE | WS_DISABLED,
		120 + 395, 40, 90 + 30, 20, hwnd, (HMENU)IDC_EDIT, 0, 0);
	// gender
	//남
	CreateWindow(TEXT("static"), TEXT("성별"), WS_CHILD | WS_VISIBLE,
		20 + 395, 70, 90, 20, hwnd, (HMENU)-1, 0, NULL);
	hEdit6 = CreateWindow(TEXT("button"), TEXT("남"), WS_CHILD | WS_VISIBLE |
		BS_AUTORADIOBUTTON | WS_GROUP | WS_DISABLED,
		120 + 395, 70, 40, 20, hwnd, (HMENU)IDC_RADIO, 0, NULL);
	//여
	hEdit7 = CreateWindow(TEXT("button"), TEXT("여"), WS_CHILD | WS_VISIBLE |
		BS_AUTORADIOBUTTON | WS_DISABLED,
		170 + 395, 70, 40, 20, hwnd, (HMENU)IDC_RADIO, 0, NULL);
	//phone
	CreateWindow(TEXT("static"), TEXT("전화번호"), WS_CHILD | WS_VISIBLE,
		20 + 395, 100, 90, 20, hwnd, (HMENU)-1, 0, NULL);
	hEdit8 = CreateWindow(TEXT("Edit"), TEXT(""),
		WS_CHILD | WS_BORDER | WS_VISIBLE | WS_DISABLED,
		120 + 395, 100, 90 + 30, 20, hwnd, (HMENU)IDC_EDIT, 0, 0);
	hEdit10 = CreateWindow(TEXT("button"), TEXT("삭제하기"), WS_CHILD | WS_VISIBLE |
		BS_PUSHBUTTON, 140 + 395, 150, 100, 25, hwnd, (HMENU)IDC_DELBTN, 0, NULL);
	// ---------------멤버 리스트 박스 ----------------
	hListBox1 = CreateWindow(TEXT("listbox"), 0,
		WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
		800, 10, 300, 400, hwnd, (HMENU)IDC_LISTBOX, 0, 0);
	hEdit10 = CreateWindow(TEXT("button"), TEXT("전체 출력"), WS_CHILD | WS_VISIBLE |
		BS_PUSHBUTTON, 900, 420, 100, 25, hwnd, (HMENU)IDC_LISTBTN, 0, NULL);
}