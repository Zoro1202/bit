#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#define WIN32_LEAN_AND_MEAN		//windows.h客 winsock2.h 颇老 面倒 规瘤
#pragma comment (linker, "/subsystem:windows")
#include <Windows.h>
#include <tchar.h>
#include <WinSock2.h>
#pragma comment( lib, "ws2_32.lib")
#include "resource.h"
#include<vector>
using std::vector;

#include "member.h"

#include "ui.h"
#include "packet.h"
#include "net.h"
#include "control.h"
#include "app.h"