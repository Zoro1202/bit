//mycal.cpp
#define DLL_SOURCE
#include "mycal.h"

float mycal_add(int num1, int num2)
{
    return (float)num1 + num2;
}

float mycal_min(int num1, int num2)
{
    return (float)num1 - num2;
}

float mycal_mul(int num1, int num2)
{
    return (float)num1 * num2;
}

float mycal_div(int num1, int num2)
{
    return (float)num1 / num2;
}

float mycal_sample(int num1, int num2)
{
    return 3.141592f;
}
