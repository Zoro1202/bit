#include "std.h"

#define FILENAME_DEFAULT TEXT("mem.mem")

//기본 파일 IO
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

//파일 윗 파일네임
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

//다이알로그 창 띄우기
void file_dlg_open(HWND hdlg, vector<MEMBER*>& members)
{
	
	OPENFILENAME ofn;              // 대화상자 정보를 담는 구조체
	TCHAR szFile[260] = FILENAME_DEFAULT;      // 파일 경로를 저장할 버퍼

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lpstrTitle = (LPTSTR)TEXT(".mem 파일 열기");// 창 캡션
	ofn.lStructSize = sizeof(ofn); // 사이즈
	ofn.hwndOwner = hdlg;          //부모 윈도우 핸들
	ofn.lpstrFile = szFile;			// 파일 경로가 저장될 버퍼
	ofn.nMaxFile = sizeof(szFile); // 위 버퍼의 사이즈
	ofn.lpstrFilter = TEXT("All\0*.*\0mem\0*.mem\0"); // 필터
	ofn.nFilterIndex = 2; // 초기 필터 인덱스
	ofn.lpstrFileTitle = 0; // 경로 없는 버퍼
	ofn.nMaxFileTitle = 0; // 버퍼 사이즈
	ofn.lpstrInitialDir = NULL;    // 기본 디렉토리
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; // OFN_PATHMUSTEXIST : 지정한 경로가 실제로 존재해야 한다는 걸 강제함.
													  //  OFN_FILEMUSTEXIST : 선택한 파일 자체가 존재해야 한다.
													 //	  잘못된 경로나 없는 파일 선택을 막기.
	if (GetOpenFileName(&ofn) == TRUE) {
		// 선택한 파일 경로는 ofn.lpstrFile 에 저장됨
		MessageBox(hdlg, ofn.lpstrFile, TEXT("파일"), MB_OK);
		file_load_filename(members, ofn.lpstrFile);
	}
}

void file_dlg_save(HWND hdlg, vector<MEMBER*>& members)
{
	OPENFILENAME ofn;
	TCHAR szFile[260] = FILENAME_DEFAULT; // 파일의 경로 저장되는 버퍼
	//기본 경로&이름 넣으면 첫 실행때 그 이름이 들어가있음

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lpstrTitle = (LPTSTR)TEXT(".mem 파일 저장"); // 창 캡션
	ofn.lStructSize = sizeof(ofn); // 사이즈
	ofn.lpstrDefExt = (LPTSTR)TEXT("mem"); // 확장명
	ofn.hwndOwner = hdlg;  // 부모 윈도우 핸들을 지정하면 모달 창으로 뜸
	ofn.lpstrFile = szFile; // 파일 이름 경로 등 저장되는 버퍼
	ofn.nMaxFile = sizeof(szFile); // 위 버퍼의 사이즈
	ofn.lpstrFilter = TEXT("All\0*.*\0mem\0*.mem\0");  // 필터 설정
	ofn.nFilterIndex = 2; // 초기 필터 인덱스 1~
	ofn.lpstrFileTitle = 0; // 경로 없이 저장하는 버퍼(NULL 로 해도 됨)
	ofn.nMaxFileTitle = 0; // 위 버퍼의 사이즈
	ofn.lpstrInitialDir = NULL;   // 기본 디렉토리
	ofn.Flags = OFN_OVERWRITEPROMPT;  // 파일 덮어쓰기 경고

	if (GetSaveFileName(&ofn) == TRUE) {
		// 선택한 파일 경로는 ofn.lpstrFile에 저장됨
		MessageBox(hdlg, ofn.lpstrFile, TEXT("파일"), MB_OK);
		file_save_filename(members, ofn.lpstrFile);
	}
}
