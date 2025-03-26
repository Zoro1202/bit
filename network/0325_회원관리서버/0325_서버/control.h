//control.h
#pragma once

void con_init();
void con_exit();
void con_server_start();

int con_msg_parsing(char* buf);

int add_stock(AddStockPacket* packet);
int select_stock(SelectStockPacket* packet);
int update_stock(UpdateStockPacket* packet);
int delete_stock(DeleteStockPacket* packet);
int selectall_stock(SelectAllStockPacket* packet);

int saveall_stock(SelectAllStockPacket* packet);

bool find_stock(const char* name, STOCK *pstock);
int find_stock_idx(const char* name);