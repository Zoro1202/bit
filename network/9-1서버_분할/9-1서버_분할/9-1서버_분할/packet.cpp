//packet.cpp
#include "std.h"

int msg_parsing(char* buf, vector<MEMBER> &members)
{
	//파싱
	int* flag = (int*)buf;
	if (*flag == PACKET_ADDMEMBER)
	{
		//----- 수신 ------------------------------------------------------
		//패킷 파싱
		AddMemberPacket* packet = (AddMemberPacket*)buf;

		//저장 정보 생성
		AddMemberPacket member;
		strcpy_s(member.name, sizeof(member.name), packet->name);
		strcpy_s(member.phone, sizeof(member.phone), packet->phone);
		member.age = packet->age;

		members.push_back(member);
		printf("저장\n");
		//------------------------------------------------------------------

		//--- 송신 -----------------------------------------------------------
		AddMemberAckPacket ack;
		ack.flag = PACKET_ADDMEMBER_S;
		strcpy_s(ack.name, sizeof(ack.name), member.name);

		//AddMemberAckPacket = 플래그, 이름 buf
		memcpy_s(buf, sizeof(AddMemberPacket), (char*)&ack, sizeof(AddMemberPacket));
		return sizeof(AddMemberPacket);
		//--------------------------------------------------------------------
	}
	else if (*flag == PACKET_SELECTMEMBER)
	{
		SelectMemberPacket* packet = (SelectMemberPacket*)buf;

		AddMemberPacket member = { 0 };
		int result = 0;
		for (int i = 0; i < members.size(); i++)
		{
			member = members[i];
			if (strcmp(member.name, packet->name) == 0)
			{
				printf("검색 성공\n");
				result = 1;
				break;
			}
		}
		if (result == 0)
			printf("검색 실패\n");
		
		//----------------- 전송 ---------------------------------------
		SelectMemberAckPacket ackpacket = { 0 };
		if (result == 1)
			ackpacket.flag = PACKET_SELECTMEMBER_S;
		else
			ackpacket.flag = PACKET_SELECTMEMBER_F;

		strcpy_s(ackpacket.name, sizeof(ackpacket.name), member.name);
		strcpy_s(ackpacket.phone, sizeof(ackpacket.phone), member.phone);
		ackpacket.age = member.age;

		memcpy_s(buf, sizeof(SelectMemberAckPacket), (char*)&ackpacket, sizeof(SelectMemberAckPacket));
		return sizeof(SelectMemberAckPacket);
	}
	else if (*flag == PACKET_SHORTMESSAGE)
	{
		ShortMessagePacket* packet = (ShortMessagePacket*)buf;
		printf("[%s] %s\n", packet->name, packet->msg);
		return sizeof(ShortMessagePacket);
	}
	return 0;
}