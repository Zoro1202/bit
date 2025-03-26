//member.h
#pragma once

typedef struct tagSTOCK
{
	char name[20];
	char made[20];
	char date[20];
	int price;
}STOCK, *PSTOCK;

STOCK stock_createstock(const char* name, const char* made, const char* date, int price);
void stock_setmade(STOCK* pstock, const char* made);
void stock_setdate(STOCK* pstock, const char* date);
void stock_setprice(STOCK* pstock, int price);
