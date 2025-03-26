#include "std.h"

vector<MEMBER> members;
//vector<MEMBER*> members1;
char buf[1024];
//초기화
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
	MEMBER member = ui_getAddDatafromDlg(hdlg);

	members.push_back(member);
	//서버에 요청
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
	MEMBER member = ui_getUpdateDatafromDlg(hdlg); //select한 멤버를 가져오기
	// UI에서 변경한 데이터를 서버에 요청
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
	send_shortmessage(name, "ㅎㅇㅇ");
}

//클라이언트 측
void msg_parsing(HWND hdlg, char* buf)
{
	//파싱
	int* flag = (int*)buf;
	if (*flag == PACKET_ADDMEMBER_S)
	{
		//----- 수신 ------------------------------------------------------
		//패킷 파싱
		AddMemberAckPacket* packet = (AddMemberAckPacket*)buf;
		char msg[30];
		sprintf_s(msg, "%s님의 회원가입이 성공했습니다.", packet->name);
		MessageBoxA(hdlg, msg, "저장", MB_OK);
	}
	else if (*flag == PACKET_ADDMEMBER_F)
	{
		AddMemberAckPacket* packet = (AddMemberAckPacket*)buf;
		MessageBoxA(hdlg, "저장 실패", "저장", MB_OK);
	}
	else if (*flag == PACKET_SELECTMEMBER_S)
	{
		SelectMemberAckPacket* packet = (SelectMemberAckPacket*)buf;
		//printf("이름 : %s\n", packet->name);
		//printf("전화번호 : %s\n", packet->phone);
		//printf("나이 %d\n", packet->age);
		ui_setUpdateData(hdlg, packet->name, packet->phone, packet->age);
	}
	else if (*flag == PACKET_SELECTMEMBER_F)
	{
		MessageBoxA(hdlg, "검색 실패", "검색", MB_OK);
	}
	else if (*flag == PACKET_SHORTMESSAGE)
	{
		ShortMessagePacket* packet = (ShortMessagePacket*)buf;
		char msg[30];
		sprintf_s(msg, "[%s] %s", packet->name, packet->msg);
		MessageBoxA(hdlg, msg, "테스트 메시지", MB_OK);
	}
	else if (*flag == PACKET_UPDATEMEMBER_S)
	{
		UpdateMemberAckPacket* packet = (UpdateMemberAckPacket*)buf;
		char msg[30];
		sprintf_s(msg, "%s님의 회원정보가 수정되었습니다.", packet->name);
		MessageBoxA(hdlg, msg, "수정", MB_OK);
	}
	else if (*flag == PACKET_UPDATEMEMBER_F)
	{
		MessageBoxA(hdlg, "수정 실패", "수정", MB_OK);
	}
	else if (*flag == PACKET_DELETEMEMBER_S)
	{
		DeleteMemberAckPacket* packet = (DeleteMemberAckPacket*)buf;
		char msg[30];
		sprintf_s(msg, "%s님의 회원정보가 삭제되었습니다.", packet->name);
		MessageBoxA(hdlg, msg, "삭제", MB_OK);
	}
	else if (*flag == PACKET_DELETEMEMBER_F)
	{
		MessageBoxA(hdlg, "삭제 실패", "삭제", MB_OK);
	}
}

