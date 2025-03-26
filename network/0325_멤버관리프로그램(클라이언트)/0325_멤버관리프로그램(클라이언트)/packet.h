//packet.h
#pragma once

#define PACKET_ADDMEMBER       1
#define PACKET_SELECTMEMBER    2
#define PACKET_SHORTMESSAGE    3
#define PACKET_UPDATEMEMBER    4
#define PACKET_DELETEMEMBER    4

#define PACKET_ADDMEMBER_S			20
#define PACKET_ADDMEMBER_F			21
#define PACKET_SELECTMEMBER_S		22
#define PACKET_SELECTMEMBER_F		23
#define PACKET_UPDATEMEMBER_S		24
#define PACKET_UPDATEMEMBER_F		25
#define PACKET_DELETEMEMBER_S		26
#define PACKET_DELETEMEMBER_F		27

typedef struct tagMEMBERPacket
{
	int flag;
	char name[20];
	char phone[20];
	int age;
}AddMemberPacket, SelectMemberAckPacket, 
UpdateMemberPacket, UpdateMemberAckPacket, 
DeleteMemberPacket, DeleteMemberAckPacket;

typedef struct tagSELECT_MEMBERPacket
{
	int flag;
	char name[20];
}SelectMemberPacket, AddMemberAckPacket;

struct ShortMessagePacket {
	int flag;
	char name[20];
	char msg[100];
};

struct SelectAllMemberPacket
{
	int flag;
	MEMBER members[15];
	int size;
};