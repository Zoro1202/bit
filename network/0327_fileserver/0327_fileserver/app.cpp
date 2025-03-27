//app.cpp
#include "std.h"

void app_init()
{
	con_init();
}

void app_run()
{
	con_server_start();
}

void app_exit()
{
	con_exit();
}