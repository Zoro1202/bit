#include "std.h"

#define FILENAME_DEFAULT TEXT("books.txt")

//�⺻ ���� IO
int file_load(vector<BOOK*>& books)
{
	FILE* fp;
	_tfopen_s(&fp, FILENAME_DEFAULT, TEXT("rb"));

	if (fp == NULL) { return -1; }

	for (int i = 0; i < books.size(); i++) // �޸� ����
	{
		free(books[i]);
	}
	books.clear();

	int size;
	fread(&size, sizeof(int), 1, fp);
	if (size == 0) return 0;
	for (int i = 0; i < size; i++)
	{
		BOOK itemp;
		fread(&itemp, sizeof(BOOK), 1, fp);
		BOOK* pmem = book_createBook(itemp.title, itemp.price, itemp.author);
		books.push_back(pmem);
	}
	fclose(fp);
	return 1;
}

int file_save(vector<BOOK*>& members)
{
	FILE* fp;
	_tfopen_s(&fp, FILENAME_DEFAULT, TEXT("wb"));

	if (fp == NULL) { return -1; }

	int size = (int)members.size();
	fwrite(&size, sizeof(int), 1, fp);
	if (size == 0) return 0;
	for (int i = 0; i < size; i++)
	{
		BOOK itemp = *members[i];
		fwrite(&itemp, sizeof(BOOK), 1, fp);
	}
	fclose(fp);
	return 1;
}
