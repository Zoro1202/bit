#include "std.h"

vector<MEMBER> members;
//vector<MEMBER*> members1;

//�ʱ�ȭ
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
		MessageBoxA(hdlg, "����!!", "â", MB_OK);
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
	//������ ��û
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
	MEMBER member; //select�� ����� ��������
	// UI���� ������ �����͸� ������ ��û

}

//test
void con_sendmessage(HWND hdlg)
{
	char name[20];
	ui_getname(hdlg, name);
	send_shortmessage(name, "������");
}