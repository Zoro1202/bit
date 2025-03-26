#pragma once
//packet.h

#define PACKET_ADDMEMBER       1
#define PACKET_SELECTMEMBER    2
#define PACKET_SHORTMESSAGE    3
#define PACKET_UPDATEMEMBER    4
#define PACKET_DELETEMEMBER    5

#define PACKET_ADDMEMBER_S			20
#define PACKET_ADDMEMBER_F			21
#define PACKET_SELECTMEMBER_S		22
#define PACKET_SELECTMEMBER_F		23
#define PACKET_UPDATEMEMBER_S		24
#define PACKET_UPDATEMEMBER_F		25
#define PACKET_DELETEMEMBER_S		26
#define PACKET_DELETEMEMBER_F		27

typedef MEMBER AddMemberPacket, SelectMemberAckPacket, UpdateMemberPacket, UpdateMemberAckPacket, DeleteMemberPacket, DeleteMemberAckPacket;

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

struct SelectAllMemberPacket
{
	int flag;
	MEMBER members[15];
	int size;
};

int msg_parsing(char* buf, vector<AddMemberPacket>& members);