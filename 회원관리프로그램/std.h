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

//�����ϱ� ��ư
#define IDC_SAVE	101
//������ư
#define IDC_DELBTN  102
//����Ʈ�ڽ�
#define IDC_LISTBOX 103
//�����ư
#define IDC_RADIO_M 104
#define IDC_RADIO_F	105
//����Ʈ��ü��¹�ư
#define IDC_LISTBTN 106

#include "handler.h"
#include "member.h"
#include "control.h"