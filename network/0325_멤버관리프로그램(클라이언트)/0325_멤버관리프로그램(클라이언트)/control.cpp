#include "std.h"

vector<MEMBER> members;
//vector<MEMBER*> members1;

//초기화
void con_init(HWND hdlg)
{
	net_initlibrary();
}
void con_connect(HWND hdlg)
{
	char ip[30];
	int port;
	ui_getipport(hdlg, ip, &port);
	if (net_create_socket(ip, port) == FALSE)
	{
		MessageBoxA(hdlg, "오류!!", "창", MB_OK);
	}
	
}

void con_exit(HWND hdlg)
{
	net_exitlibrary();
	net_delete_socket();
}

void con_insertMember(HWND hdlg)
{
	MEMBER member = ui_getDatafromDlg(hdlg);

	members.push_back(member);
	//서버에 요청
	send_addmember(member.name, member.phone, member.age);
}

void con_selectMember(HWND hdlg)
{
	char name[20];
	ui_getname(hdlg, name);
	send_selectmember(name); //
}

void con_updateMember(HWND hdlg)
{
	MEMBER member; //select한 멤버를 가져오기
	// UI에서 변경한 데이터를 서버에 요청

}

//test
void con_sendmessage(HWND hdlg)
{
	char name[20];
	ui_getname(hdlg, name);
	send_shortmessage(name, "ㅎㅇㅇ");
}