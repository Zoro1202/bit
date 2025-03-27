//control.h
#pragma once

void con_init();
void con_exit();
void con_server_start();

unsigned long __stdcall con_start_dataserver(void* p);

int con_msg_parsing(char* buf);

int list_file(FileListPack* packet);

int down_file(FileDownloadPack* packet);
