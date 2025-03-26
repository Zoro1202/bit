#include "std.h"

vector<MEMBER> members;
//vector<MEMBER*> members1;
char buf[1024];
//�ʱ�ȭ
void con_init(HWND hdlg)
{
	net_initlibrary(hdlg);
}
void con_connect(HWND hdlg)
{
	char ip[30];
	int port;
	ui_getipport(hdlg, ip, &port);
	if (net_create_socket(ip, port, buf) == FALSE)
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
	MEMBER member = ui_getAddDatafromDlg(hdlg);

	members.push_back(member);
	//������ ��û
	send_addmember(member.name, member.phone, member.age);

}

void con_selectMember(HWND hdlg)
{
	char name[20];
	ui_getSelectNamefromDlg(hdlg, name);
	send_selectmember(name); //
}

void con_updateMember(HWND hdlg)
{
	MEMBER member = ui_getUpdateDatafromDlg(hdlg); //select�� ����� ��������
	// UI���� ������ �����͸� ������ ��û
	send_updatemember(member.name, member.phone, member.age);
}

void con_deleteMember(HWND hdlg)
{
	char name[20];
	ui_getDeleteNamefromDlg(hdlg, name);
	send_deletemember(name);
}

//test
void con_sendmessage(HWND hdlg)
{
	char name[20];
	ui_getSelectNamefromDlg(hdlg, name);
	send_shortmessage(name, "������");
}

//Ŭ���̾�Ʈ ��
void msg_parsing(HWND hdlg, char* buf)
{
	//�Ľ�
	int* flag = (int*)buf;
	if (*flag == PACKET_ADDMEMBER_S)
	{
		//----- ���� ------------------------------------------------------
		//��Ŷ �Ľ�
		AddMemberAckPacket* packet = (AddMemberAckPacket*)buf;
		char msg[30];
		sprintf_s(msg, "%s���� ȸ�������� �����߽��ϴ�.", packet->name);
		MessageBoxA(hdlg, msg, "����", MB_OK);
	}
	else if (*flag == PACKET_ADDMEMBER_F)
	{
		AddMemberAckPacket* packet = (AddMemberAckPacket*)buf;
		MessageBoxA(hdlg, "���� ����", "����", MB_OK);
	}
	else if (*flag == PACKET_SELECTMEMBER_S)
	{
		SelectMemberAckPacket* packet = (SelectMemberAckPacket*)buf;
		//printf("�̸� : %s\n", packet->name);
		//printf("��ȭ��ȣ : %s\n", packet->phone);
		//printf("���� %d\n", packet->age);
		ui_setUpdateData(hdlg, packet->name, packet->phone, packet->age);
	}
	else if (*flag == PACKET_SELECTMEMBER_F)
	{
		MessageBoxA(hdlg, "�˻� ����", "�˻�", MB_OK);
	}
	else if (*flag == PACKET_SHORTMESSAGE)
	{
		ShortMessagePacket* packet = (ShortMessagePacket*)buf;
		char msg[30];
		sprintf_s(msg, "[%s] %s", packet->name, packet->msg);
		MessageBoxA(hdlg, msg, "�׽�Ʈ �޽���", MB_OK);
	}
	else if (*flag == PACKET_UPDATEMEMBER_S)
	{
		UpdateMemberAckPacket* packet = (UpdateMemberAckPacket*)buf;
		char msg[30];
		sprintf_s(msg, "%s���� ȸ�������� �����Ǿ����ϴ�.", packet->name);
		MessageBoxA(hdlg, msg, "����", MB_OK);
	}
	else if (*flag == PACKET_UPDATEMEMBER_F)
	{
		MessageBoxA(hdlg, "���� ����", "����", MB_OK);
	}
	else if (*flag == PACKET_DELETEMEMBER_S)
	{
		DeleteMemberAckPacket* packet = (DeleteMemberAckPacket*)buf;
		char msg[30];
		sprintf_s(msg, "%s���� ȸ�������� �����Ǿ����ϴ�.", packet->name);
		MessageBoxA(hdlg, msg, "����", MB_OK);
	}
	else if (*flag == PACKET_DELETEMEMBER_F)
	{
		MessageBoxA(hdlg, "���� ����", "����", MB_OK);
	}
}

