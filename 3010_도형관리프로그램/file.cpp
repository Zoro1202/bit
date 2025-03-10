//file.cpp
#include "std.h"

void file_save(vector<SHAPE> &shape, HWND hwnd)
{
	FILE* fp;
	const char FILENAME[] = "filename.txt";
	int ret = fopen_s(&fp, FILENAME, "w");
	if (fp == NULL) return;

	int size = shape.size();
	fprintf_s(fp, "%d ", size);
	for (int i = 0; i < size; i++)
	{
		fprintf_s(fp, "%d %d %d %d %d ",
			shape[i].type,
			shape[i].color,
			shape[i].pt.x, shape[i].pt.y,
			shape[i].size);
	}
	fclose(fp);
}

void file_load(vector<SHAPE> &shape, HWND hwnd)
{
	FILE* fp;
	const char FILENAME[] = "filename.txt";
	int ret = fopen_s(&fp, FILENAME, "r");
	if (fp == NULL) return;

	shape.clear();

	int size; fscanf_s(fp, "%d", &size);
	for (int i = 0; i < size; i++) {
		SHAPE sh;
		fscanf_s(fp, "%d %d %d %d %d",
			&sh.type,
			&sh.color,
			&sh.pt.x, &sh.pt.y,
			&sh.size);
		shape.push_back(sh);
	}
	fclose(fp);
}
