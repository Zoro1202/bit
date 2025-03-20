#include "std.h"

#define FILENAME_DEFAULT TEXT("mem.mem")

int file_load(vector<MEMBER*>& members)
{
	FILE* fp;
	_tfopen_s(&fp, FILENAME_DEFAULT, TEXT("rb"));

	if (fp == NULL) { return -1; }

	for (int i = 0; i < members.size(); i++) // �޸� ����
	{
		free(members[i]);
	}
	members.clear();

	int size;
	fread(&size, sizeof(int), 1, fp);
	if (size == 0) return 0;
	for (int i = 0; i < size; i++)
	{
		static MEMBER itemp;
		fread(&itemp, sizeof(MEMBER), 1, fp);
		MEMBER* pmem = member_createmember(itemp.id, itemp.pw, itemp.name, itemp.phone, itemp.age);
		members.push_back(pmem);
	}
	fclose(fp);
	return 1;
}

int file_save(vector<MEMBER*>& members)
{
	FILE* fp;
	_tfopen_s(&fp, FILENAME_DEFAULT, TEXT("wb"));

	if (fp == NULL) { return -1; }

	int size = (int)members.size();
	fwrite(&size, sizeof(int), 1, fp);
	if (size == 0) return 0;
	for (int i = 0; i < size; i++)
	{
		MEMBER itemp = *members[i];
		fwrite(&itemp, sizeof(MEMBER), 1, fp);
	}
	fclose(fp);
	return 1;
}

int file_load_filename(vector<MEMBER*>& members, TCHAR* fname)
{
	FILE* fp;
	_tfopen_s(&fp, fname, TEXT("rb"));

	if (fp == NULL) { return -1; }

	for (int i = 0; i < members.size(); i++) // �޸� ����
	{
		free(members[i]);
	}
	members.clear();

	int size;
	fread(&size, sizeof(int), 1, fp);
	if (size == 0) return 0;
	for (int i = 0; i < size; i++)
	{
		static MEMBER itemp;
		fread(&itemp, sizeof(MEMBER), 1, fp);
		MEMBER* pmem = member_createmember(itemp.id, itemp.pw, itemp.name, itemp.phone, itemp.age);
		members.push_back(pmem);
	}
	fclose(fp);
	return 1;
}

int file_save_filename(vector<MEMBER*>& members, TCHAR* fname)
{
	FILE* fp;
	_tfopen_s(&fp, fname, TEXT("wb"));

	if (fp == NULL) { return -1; }

	int size = (int)members.size();
	fwrite(&size, sizeof(int), 1, fp);
	if (size == 0) return 0;
	for (int i = 0; i < size; i++)
	{
		MEMBER itemp = *members[i];
		fwrite(&itemp, sizeof(MEMBER), 1, fp);
	}
	fclose(fp);
	return 1;
}

void file_dlg_open(HWND hdlg, vector<MEMBER*>& members)
{
	
	OPENFILENAME ofn;              // ��ȭ���� ������ ��� ����ü
	TCHAR szFile[260] = { 0 };      // ���� ��θ� ������ ����

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hdlg;          // ���� â �ڵ��� �ִٸ� �־��൵ ��
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = TEXT("All\0*.*\0mem\0*.mem\0");  // ���� ����
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = (LPTSTR)TEXT("mem.mem");
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;    // �⺻ ���丮
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE) {
		// ������ ���� ��δ� ofn.lpstrFile �� �����
		MessageBox(hdlg, ofn.lpstrFile, TEXT("����"), MB_OK);
		file_load_filename(members, ofn.lpstrFile);
	}
}

void file_dlg_save(HWND hdlg, vector<MEMBER*>& members)
{
	OPENFILENAME ofn;
	TCHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hdlg;  // �θ� ������ �ڵ��� �����ϸ� ��� â���� ��
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = TEXT("All\0*.*\0mem\0*.mem\0");  // ���� ����
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;   // �⺻ ���丮
	ofn.Flags = OFN_OVERWRITEPROMPT;  // ���� ����� ���

	if (GetSaveFileName(&ofn) == TRUE) {
		// ������ ���� ��δ� ofn.lpstrFile�� �����
		MessageBox(hdlg, ofn.lpstrFile, TEXT("����"), MB_OK);
		file_save_filename(members, ofn.lpstrFile);
	}
}