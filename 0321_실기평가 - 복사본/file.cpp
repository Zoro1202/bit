#include "std.h"

#define FILENAME_DEFAULT TEXT("books.txt")

//기본 파일 IO
int file_load(vector<BOOK*>& books)
{
	FILE* fp;
	_tfopen_s(&fp, FILENAME_DEFAULT, TEXT("rb"));

	if (fp == NULL) { return -1; }

	for (int i = 0; i < books.size(); i++) // 메모리 해제
	{
		free(books[i]);
	}
	books.clear();

	int size;
	fread(&size, sizeof(int), 1, fp);
	if (size == 0) return 0;
	for (int i = 0; i < size; i++)
	{
		BOOK book;
		fread(&book, sizeof(BOOK), 1, fp);
		BOOK* pbook = book_createBook(book.title, book.price, book.author);
		books.push_back(pbook);
	}
	fclose(fp);
	return 1;
}

int file_save(vector<BOOK*>& books)
{
	FILE* fp;
	_tfopen_s(&fp, FILENAME_DEFAULT, TEXT("wb"));

	if (fp == NULL) { return -1; }

	int size = (int)books.size();
	fwrite(&size, sizeof(int), 1, fp);
	if (size == 0) return 0;
	for (int i = 0; i < size; i++)
	{
		BOOK book = *books[i];
		fwrite(&book, sizeof(BOOK), 1, fp);
	}
	fclose(fp);
	return 1;
}
