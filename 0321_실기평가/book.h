#pragma once

typedef struct tagBOOK
{
	TCHAR title[30];
	int price;
	TCHAR author[30];
}BOOK;

BOOK* book_createBook(TCHAR* title, int price, TCHAR* author);

void book_setData(BOOK* pbook, int price, TCHAR* author);
