#pragma once
//packet.h

#define PACKET_ADDMEMBER       1
#define PACKET_SELECTMEMBER    2
#define PACKET_SHORTMESSAGE    3

#define PACKET_ADDMEMBER_S			20
#define PACKET_ADDMEMBER_F			21
#define PACKET_SELECTMEMBER_S		22
#define PACKET_SELECTMEMBER_F		23


typedef MEMBER AddMemberPacket, SelectMemberAckPacket;

struct SelectMemberPacket {
	int flag;
	char name[20];
};
struct ShortMessagePacket {
	int flag;
	char name[20];
	char msg[100];
};

struct AddMemberAckPacket
{
	int flag;
	char name[20];
};


int msg_parsing(char* buf, vector<AddMemberPacket>& members);