//member.cpp
#include "std.h"

STOCK stock_createstock(const char* name, const char* made, const char* date, int price)
{
	STOCK member;
	strcpy_s(member.name, sizeof(member.name), name);
	strcpy_s(member.made, sizeof(member.made), made);
	strcpy_s(member.date, sizeof(member.date), date);
	member.price = price;
	return member;
}


void stock_setmade(STOCK* pstock, const char* made)
{
	strcpy_s(pstock->made, sizeof(pstock->made), made);
}

void stock_setdate(STOCK* pstock, const char* date)
{
	strcpy_s(pstock->date, sizeof(pstock->date), date);
}

void stock_setprice(STOCK* pstock, int price)
{
	pstock->price = price;
}