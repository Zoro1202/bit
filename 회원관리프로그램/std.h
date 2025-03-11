#pragma once

#pragma comment (linker, "/subsystem:windows")

//그냥들
#define IDC_BUTTON	1
#define IDC_EDIT	2
#define IDC_RADIO   3
#define IDC_STATIC  5

//저장하기 버튼
#define IDC_SAVE	7
//삭제버튼
#define IDC_DELBTN  13
//리스트박스
#define IDC_LISTBOX 8
//남녀버튼
#define IDC_RADIO_M 10
#define IDC_RADIO_F	11
//리스트전체출력버튼
#define IDC_LISTBTN 12
#include <Windows.h>
#include <tchar.h>
#include <vector>
using std::vector;

#include "handler.h"
#include "member.h"


// control
#include "control.h"