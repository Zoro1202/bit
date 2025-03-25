//packet.h
#pragma once

#define PACKET_ADDMEMBER       1
#define PACKET_SELECTMEMBER    2
#define PACKET_SHORTMESSAGE    3

#define PACKET_ADDMEMBER_S			20
#define PACKET_ADDMEMBER_F			21
#define PACKET_SELECTMEMBER_S		22
#define PACKET_SELECTMEMBER_F		23

typedef struct tagMEMBERPacket
{
	int flag;
	char name[20];
	char phone[20];
	int age;
}AddMemberPacket, SelectMemberAckPacket;

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

void msg_parsing(char* buf);