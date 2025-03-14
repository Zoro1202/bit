//modal.h
#pragma once

#include <Windows.h>
#include <tchar.h>
#include <vector>
using std::vector;

#include "resource.h"
#include "item.h"

INT_PTR ModalProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);
