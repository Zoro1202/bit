//member.cpp
#include "std.h"

void member_setMember(MEMBER* pmember, const TCHAR* name, int gender, const TCHAR* phone)
{
	lstrcpyn(pmember->name, name, _countof(pmember->name));
	pmember->gender = gender;
	lstrcpyn(pmember->phone, phone, _countof(pmember->phone));
}

TCHAR* member_getName(MEMBER* pmember)
{
	return 	pmember->name;
}
int member_getGender(MEMBER* pmember)
{
	return pmember->gender;
}
TCHAR* member_getPhone(MEMBER* pmember)
{
	return pmember->phone;
}
void member_setName(MEMBER* pmember, TCHAR* name)
{
	lstrcpyn(pmember->name, name, _countof(pmember->name));
}
void member_setGender(MEMBER* pmember, int gender)
{
	pmember->gender = gender;
}
void member_setPhone(MEMBER* pmember, TCHAR* phone)
{
	lstrcpyn(pmember->phone, phone, _countof(pmember->phone));
}
