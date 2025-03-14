//item.cpp
#include "std.h"

void item_setItem(ITEM* item,int id, int type, const TCHAR* name, int price, const TCHAR* spec)
{
	item->id = id;
	item->type = type;
	lstrcpy(item->name, name);
	item->price = price;
	lstrcpy(item->spec, spec);
}
