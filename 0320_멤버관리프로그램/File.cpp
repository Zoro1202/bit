#include "std.h"

#define FILENAME_DEFAULT TEXT("mem.mem")

//�⺻ ���� IO
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

//���� �� ���ϳ���
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

//���̾˷α� â ����
void file_dlg_open(HWND hdlg, vector<MEMBER*>& members)
{
	
	OPENFILENAME ofn;              // ��ȭ���� ������ ��� ����ü
	TCHAR szFile[260] = FILENAME_DEFAULT;      // ���� ��θ� ������ ����

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lpstrTitle = (LPTSTR)TEXT(".mem ���� ����");// â ĸ��
	ofn.lStructSize = sizeof(ofn); // ������
	ofn.hwndOwner = hdlg;          //�θ� ������ �ڵ�
	ofn.lpstrFile = szFile;			// ���� ��ΰ� ����� ����
	ofn.nMaxFile = sizeof(szFile); // �� ������ ������
	ofn.lpstrFilter = TEXT("All\0*.*\0mem\0*.mem\0"); // ����
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
		file_load_filename(members, ofn.lpstrFile);
	}
}

void file_dlg_save(HWND hdlg, vector<MEMBER*>& members)
{
	OPENFILENAME ofn;
	TCHAR szFile[260] = FILENAME_DEFAULT; // ������ ��� ����Ǵ� ����
	//�⺻ ���&�̸� ������ ù ���ට �� �̸��� ������

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lpstrTitle = (LPTSTR)TEXT(".mem ���� ����"); // â ĸ��
	ofn.lStructSize = sizeof(ofn); // ������
	ofn.lpstrDefExt = (LPTSTR)TEXT("mem"); // Ȯ���
	ofn.hwndOwner = hdlg;  // �θ� ������ �ڵ��� �����ϸ� ��� â���� ��
	ofn.lpstrFile = szFile; // ���� �̸� ��� �� ����Ǵ� ����
	ofn.nMaxFile = sizeof(szFile); // �� ������ ������
	ofn.lpstrFilter = TEXT("All\0*.*\0mem\0*.mem\0");  // ���� ����
	ofn.nFilterIndex = 2; // �ʱ� ���� �ε��� 1~
	ofn.lpstrFileTitle = 0; // ��� ���� �����ϴ� ����(NULL �� �ص� ��)
	ofn.nMaxFileTitle = 0; // �� ������ ������
	ofn.lpstrInitialDir = NULL;   // �⺻ ���丮
	ofn.Flags = OFN_OVERWRITEPROMPT;  // ���� ����� ���

	if (GetSaveFileName(&ofn) == TRUE) {
		// ������ ���� ��δ� ofn.lpstrFile�� �����
		MessageBox(hdlg, ofn.lpstrFile, TEXT("����"), MB_OK);
		file_save_filename(members, ofn.lpstrFile);
	}
}
