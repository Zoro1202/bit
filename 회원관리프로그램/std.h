#pragma once

#pragma comment (linker, "/subsystem:windows")

//�׳ɵ�
#define IDC_BUTTON	1
#define IDC_EDIT	2
#define IDC_RADIO   3
#define IDC_STATIC  5

//�����ϱ� ��ư
#define IDC_SAVE	7
//������ư
#define IDC_DELBTN  13
//����Ʈ�ڽ�
#define IDC_LISTBOX 8
//�����ư
#define IDC_RADIO_M 10
#define IDC_RADIO_F	11
//����Ʈ��ü��¹�ư
#define IDC_LISTBTN 12
#include <Windows.h>
#include <tchar.h>
#include <vector>
using std::vector;

#include "handler.h"
#include "member.h"


// control
#include "control.h"