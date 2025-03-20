#include "std.h"

#define FILENAME_DEFAULT TEXT("mem.mem")

int file_load(vector<MEMBER*>& members)
{
	FILE* fp;
	_tfopen_s(&fp, FILENAME_DEFAULT, TEXT("rb"));

	if (fp == NULL) { return -1; }

	for (int i = 0; i < members.size(); i++) // 메모리 해제
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

	for (int i = 0; i < members.size(); i++) // 메모리 해제
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
	
	OPENFILENAME ofn;              // 대화상자 정보를 담는 구조체
	TCHAR szFile[260] = { 0 };      // 파일 경로를 저장할 버퍼

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hdlg;          // 만약 창 핸들이 있다면 넣어줘도 돼
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = TEXT("All\0*.*\0mem\0*.mem\0");  // 필터 설정
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = (LPTSTR)TEXT("mem.mem");
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;    // 기본 디렉토리
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE) {
		// 선택한 파일 경로는 ofn.lpstrFile 에 저장됨
		MessageBox(hdlg, ofn.lpstrFile, TEXT("파일"), MB_OK);
		file_load_filename(members, ofn.lpstrFile);
	}
}

void file_dlg_save(HWND hdlg, vector<MEMBER*>& members)
{
	OPENFILENAME ofn;
	TCHAR szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hdlg;  // 부모 윈도우 핸들을 지정하면 모달 창으로 뜸
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = TEXT("All\0*.*\0mem\0*.mem\0");  // 필터 설정
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;   // 기본 디렉토리
	ofn.Flags = OFN_OVERWRITEPROMPT;  // 파일 덮어쓰기 경고

	if (GetSaveFileName(&ofn) == TRUE) {
		// 선택한 파일 경로는 ofn.lpstrFile에 저장됨
		MessageBox(hdlg, ofn.lpstrFile, TEXT("파일"), MB_OK);
		file_save_filename(members, ofn.lpstrFile);
	}
}