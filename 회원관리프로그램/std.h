#pragma once

#pragma comment (linker, "/subsystem:windows")
#include <Windows.h>
#include <tchar.h>
#include <vector>
using std::vector;


#define IDC_BUTTON	1
#define IDC_EDIT	2
#define IDC_RADIO   3
#define IDC_STATIC  5

//저장하기 버튼
#define IDC_SAVE	101
//삭제버튼
#define IDC_DELBTN  102
//리스트박스
#define IDC_LISTBOX 103
//남녀버튼
#define IDC_RADIO_M 104
#define IDC_RADIO_F	105
//리스트전체출력버튼
#define IDC_LISTBTN 106

#include "handler.h"
#include "member.h"
#include "control.h"