#pragma once
//std.h
#define WIN32_LEAN_AND_MEAN		//windows.h客 winsock2.h 颇老 面倒 规瘤
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <WinSock2.h>
#pragma comment( lib, "ws2_32.lib")
#include <vector>
using namespace std;

#include "app.h"
#include "control.h"
#include "net.h"
#include "member.h"
#include "packet.h"



