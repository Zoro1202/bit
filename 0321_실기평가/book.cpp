#include "std.h"

BOOK* book_createBook(TCHAR* title, int price, TCHAR* author)
{
	BOOK* book = (BOOK*)malloc(sizeof(BOOK));
	if (book == NULL) return NULL;
	_tcscpy_s(book->title, _countof(book->title), title);
	book->price = price;
	_tcscpy_s(book->author, _countof(book->author), author);
	return book;
}

void book_setData(BOOK* pbook, int price, TCHAR* author)
{
	_tcscpy_s(pbook->author, _countof(pbook->author), author);

	pbook->price = price;
}