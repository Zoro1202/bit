//FILE.cpp
#include "std.h"

int file_load(vector<ITEM>& items)
{
	FILE* fp;
	fopen_s(&fp, "ITEM.txt", "r");

	if (fp == NULL)	{return 0;}

	items.clear();

	int size;
	_ftscanf_s(fp, TEXT("%d"), &size);
	if (size == 0) return 0;
	for (int i = 0; i < size; i++)
	{
		static ITEM itemp;
		itemp.id = -1;
		_ftscanf_s(fp, TEXT("%d %s %d %s"),
			&itemp.type,
			itemp.name, (unsigned)sizeof(itemp.name), 
			&itemp.price,
			itemp.spec, (unsigned)sizeof(itemp.spec));
		items.push_back(itemp);
	}
	return size;

}
