#include "std.h"
/*
typedef struct tagMEMBER
{
	char name[20];
	char phone[20];
	int age;
}MEMBER;
*/

MEMBER* member_createMember(char* name, char* phone, int age)
{
	MEMBER* mem = (MEMBER*)malloc(sizeof(MEMBER));
	if (mem == NULL) return NULL;
	strcpy_s(mem->name, sizeof(mem->name), name);
	strcpy_s(mem->phone, sizeof(mem->phone), phone);
	mem->age = age;
	return mem;
}

void member_updateMember(MEMBER* member, char* name, char* phone, int age)
{
	strcpy_s(member->name, sizeof(member->name), name);
	strcpy_s(member->phone, sizeof(member->phone), phone);
	member->age = age;
}
