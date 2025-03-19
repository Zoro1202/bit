//mycal.h
#pragma once

#ifdef DLL_SOURCE
	#define DLLFUNC __declspec(dllexport)
#else 
	#define DLLFUNC __declspec(dllimport)
#endif // DLL_SOURCE

extern "C" DLLFUNC float mycal_add(int num1, int num2);
extern "C" DLLFUNC float mycal_min(int num1, int num2);
extern "C" DLLFUNC float mycal_mul(int num1, int num2);
extern "C" DLLFUNC float mycal_div(int num1, int num2);
float mycal_sample(int num1, int num2);