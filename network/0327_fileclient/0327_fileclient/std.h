//std.h
#pragma once
#pragma comment(linker, "/subsystem:windows")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#pragma comment( lib, "ws2_32.lib")
#include <Windows.h>

#include <commctrl.h>
#include <tchar.h>
#include "resource.h"
#include <vector>
using namespace std; 

#include "packet.h"		//***
#include "net.h"		//***
#include "ui.h"
#include "control.h"
#include "handler.h"
#include "file.h"