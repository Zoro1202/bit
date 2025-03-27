#include "std.h"

int file_list(char(*files)[30], int *size)
{

	//파일 이름 불러오기
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	TCHAR fname[MAX_PATH];
	BOOL bResult = TRUE;
	TCHAR Path[MAX_PATH] = {"C:\\00_myfile\\*.*"};

	//GetWindowsDirectory(Path, MAX_PATH);
	hSrch = FindFirstFile(Path, &wfd);
	if (hSrch == INVALID_HANDLE_VALUE) return 0;
	int idx = 0;
	while (bResult) {
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			wsprintf(fname, "[ %s ]", wfd.cFileName);
		}
		else {
			wsprintf(fname, "%s", wfd.cFileName);
			strcpy_s(files[idx++], sizeof(files[idx]), fname);
		}
		//SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)fname);
		bResult = FindNextFile(hSrch, &wfd);
	}
	FindClose(hSrch);

	for (int i = 0; i < idx; i++)
	{
		printf("%s", files[i]);
	}
	printf("저장 완료\n");
	*size = idx;
	return 1;
}