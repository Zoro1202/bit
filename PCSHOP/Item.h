//item.h
#pragma once

typedef struct tagITEM
{
	int id;
	int type;
	TCHAR name[20];
	int price;
	TCHAR spec[100];
}ITEM;

void item_setItem(ITEM* item, int id, int type, const TCHAR* name, int price, const TCHAR* spec);