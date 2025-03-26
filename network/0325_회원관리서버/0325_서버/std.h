//std.h
#pragma once

//#define WIN32_LEAN_AND_MEAN		//windows.h客 winsock2.h 颇老 面倒 规瘤
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#pragma comment( lib, "ws2_32.lib")
#include <Windows.h>
#include <vector>
using namespace std;

#include "stock.h"
#include "packet.h"
#include "net.h"
#include "control.h"
#include "app.h"
