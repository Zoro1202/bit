#pragma once


typedef struct tagMEMBER
{
	TCHAR id[20];
	TCHAR pw[20];
	TCHAR name[20];
	TCHAR phone[20];
	int age;
}MEMBER, *PMEMBER;

MEMBER* member_createmember(TCHAR* id, TCHAR* pw, TCHAR* name, TCHAR* phone, int age);

void member_setdata(MEMBER* pmember, TCHAR* phone, int age);
