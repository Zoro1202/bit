#pragma once
//std.h
#define WIN32_LEAN_AND_MEAN		//windows.h와 winsock2.h 파일 충돌 방지
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



