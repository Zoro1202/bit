//member.h
#pragma once

typedef struct tagMEMBER
{
	TCHAR name[64]; // name
	int gender; // 1: ³²Male, 2: Female
	TCHAR phone[64]; // phone number
}MEMBER, *PMEMBER;

void member_setMember(MEMBER* pmember, const TCHAR* name, int gender, const TCHAR* phone);

TCHAR* member_getName(MEMBER* pmember);
int member_getGender(MEMBER* pmember);
TCHAR* member_getPhone(MEMBER* pmember);

void member_setName(MEMBER* pmember, TCHAR* name);
void member_setGender(MEMBER* pmember, int gender);
void member_setPhone(MEMBER* pmember, TCHAR* phone);