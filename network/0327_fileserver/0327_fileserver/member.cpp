//member.cpp
#include "std.h"

Member member_createmember(const char* name, const char* phone, int age)
{
	Member member;
	strcpy_s(member.name, sizeof(member.name), name);
	strcpy_s(member.phone, sizeof(member.phone), phone);
	member.age = age;
	return member;
}

void member_setphone(Member* pmember, const char* phone)
{
	strcpy_s(pmember->phone, sizeof(pmember->phone), phone);
}

void member_setage(Member* pmember, int age)
{
	pmember->age = age;
}