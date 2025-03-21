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


//���� �� ���ϳ���
int file_load_filename(vector<BOOK*>& books, TCHAR* fname)
{
	FILE* fp;
	_tfopen_s(&fp, fname, TEXT("rb"));

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
		static BOOK book;
		fread(&book, sizeof(BOOK), 1, fp);
		BOOK* pbook = book_createBook(book.title, book.price, book.author);
		books.push_back(pbook);
	}
	fclose(fp);
	return 1;
}

int file_save_filename(vector<BOOK*>& books, TCHAR* fname)
{
	FILE* fp;
	_tfopen_s(&fp, fname, TEXT("wb"));

	if (fp == NULL) { return -1; }

	int size = (int)books.size();
	fwrite(&size, sizeof(int), 1, fp);
	if (size == 0) return 0;
	for (int i = 0; i < size; i++)
	{
		BOOK itemp = *books[i];
		fwrite(&itemp, sizeof(BOOK), 1, fp);
	}
	fclose(fp);
	return 1;
}

//���̾˷α� â ����
void file_dlg_open(HWND hdlg, vector<BOOK*>& books)
{

	OPENFILENAME ofn;              // ��ȭ���� ������ ��� ����ü
	TCHAR szFile[260] = FILENAME_DEFAULT;      // ���� ��θ� ������ ����

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lpstrTitle = (LPTSTR)TEXT("���� ����");// â ĸ��
	ofn.lStructSize = sizeof(ofn); // ������
	ofn.hwndOwner = hdlg;          //�θ� ������ �ڵ�
	ofn.lpstrFile = szFile;			// ���� ��ΰ� ����� ����
	ofn.nMaxFile = sizeof(szFile); // �� ������ ������
	ofn.lpstrFilter = TEXT("All\0*.*\0txt\0*.txt\0"); // ����
	ofn.nFilterIndex = 2; // �ʱ� ���� �ε���
	ofn.lpstrFileTitle = 0; // ��� ���� ����
	ofn.nMaxFileTitle = 0; // ���� ������
	ofn.lpstrInitialDir = NULL;    // �⺻ ���丮
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // OFN_PATHMUSTEXIST : ������ ��ΰ� ������ �����ؾ� �Ѵٴ� �� ������.
	//  OFN_FILEMUSTEXIST : ������ ���� ��ü�� �����ؾ� �Ѵ�.
   //	  �߸��� ��γ� ���� ���� ������ ����.
	if (GetOpenFileName(&ofn) == TRUE) {
		// ������ ���� ��δ� ofn.lpstrFile �� �����
		MessageBox(hdlg, ofn.lpstrFile, TEXT("����"), MB_OK);
		file_load_filename(books, ofn.lpstrFile);
	}
}

void file_dlg_save(HWND hdlg, vector<BOOK*>& books)
{
	OPENFILENAME ofn;
	TCHAR szFile[260] = FILENAME_DEFAULT; // ������ ��� ����Ǵ� ����
	//�⺻ ���&�̸� ������ ù ���ට �� �̸��� ������

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lpstrTitle = (LPTSTR)TEXT("�ٸ� �̸����� ����"); // â ĸ��
	ofn.lStructSize = sizeof(ofn); // ������
	ofn.lpstrDefExt = (LPTSTR)TEXT("txt"); // Ȯ���
	ofn.hwndOwner = hdlg;  // �θ� ������ �ڵ��� �����ϸ� ��� â���� ��
	ofn.lpstrFile = szFile; // ���� �̸� ��� �� ����Ǵ� ����
	ofn.nMaxFile = sizeof(szFile); // �� ������ ������
	ofn.lpstrFilter = TEXT("All\0*.*\txt\0*.txt\0");  // ���� ����
	ofn.nFilterIndex = 2; // �ʱ� ���� �ε��� 1~
	ofn.lpstrFileTitle = 0; // ��� ���� �����ϴ� ����(NULL �� �ص� ��)
	ofn.nMaxFileTitle = 0; // �� ������ ������
	ofn.lpstrInitialDir = NULL;   // �⺻ ���丮
	ofn.Flags = OFN_OVERWRITEPROMPT;  // ���� ����� ���

	if (GetSaveFileName(&ofn) == TRUE) {
		// ������ ���� ��δ� ofn.lpstrFile�� �����
		MessageBox(hdlg, ofn.lpstrFile, TEXT("����"), MB_OK);
		file_save_filename(books, ofn.lpstrFile);
	}
}
