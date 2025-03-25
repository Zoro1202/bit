#include "std.h"

//서버 측
void msg_parsing(char* buf)
{
	//파싱
	int* flag = (int*)buf;
	if (*flag == PACKET_ADDMEMBER_S)
	{
		//----- 수신 ------------------------------------------------------
		//패킷 파싱
		AddMemberAckPacket* packet = (AddMemberAckPacket*)buf;
		printf("%s님의 회원가입이 성공했습니다.\n", packet->name);
	}
	else if (*flag == PACKET_ADDMEMBER_F)
	{
		AddMemberAckPacket* packet = (AddMemberAckPacket*)buf;
		printf("저장 실패\n");
	}
	else if (*flag == PACKET_SELECTMEMBER_S)
	{
		SelectMemberAckPacket* packet = (SelectMemberAckPacket*)buf;
		printf("이름 : %s\n", packet->name);
		printf("전화번호 : %s\n", packet->phone);
		printf("나이 %d\n", packet->age);
	}
	else if (*flag == PACKET_SELECTMEMBER_F)
	{
		printf("검색 실패\n");
	}
	else if (*flag == PACKET_SHORTMESSAGE)
	{
		ShortMessagePacket* packet = (ShortMessagePacket*)buf;
		printf("[%s] %s\n", packet->name, packet->msg);
	}
}

