//member.h
#pragma once

struct Member
{
	char name[20];
	char phone[20];
	int age;
};

Member member_createmember(const char* name, const char* phone, int age);
void member_setphone(Member* pmember, const char* phone);
void member_setage(Member* pmember, int age);
