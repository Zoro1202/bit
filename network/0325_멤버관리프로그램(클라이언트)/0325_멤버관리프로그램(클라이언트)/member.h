#pragma once

typedef struct tagMEMBER
{
	char name[20];
	char phone[20];
	int age;
}MEMBER;

MEMBER* member_createMember(char* name, char* phone, int age);

void member_updateMember(MEMBER* member, char* name, char* phone, int age);
