//control.cpp
#include "std.h"

#define SERVER_PORT		9000

vector<STOCK> stocks;

void con_init()
{
	if (net_initlibrary() == false)
	{
		printf("扩加 檬扁拳 角菩\n");
		exit(-1);
	}
	if (net_create_socket(SERVER_PORT) == false)
	{
		printf("家南 积己 坷幅..\n");
		exit(-1);
	}
}

void con_exit()
{
	net_delete_socket();
	net_exitlibrary();
}

void con_server_start()
{
	printf("楷搬 措扁.....................\n");
	HANDLE hthread = CreateThread(0, 0, listen_thread, 0, 0, 0);

	WaitForSingleObject(hthread, INFINITE);
	CloseHandle(hthread);
}

//---------------- 扁瓷 ------------------------------------
int con_msg_parsing(char* buf)
{
	//颇教
	int* flag = (int*)buf;
	switch (*flag)
	{
	case PACKET_ADDSTOCK:		return add_stock((AddStockPacket*)buf);
	case PACKET_SELECTSTOCK:	return select_stock((SelectStockPacket*)buf);
	case PACKET_UPDATESTOCK:	return update_stock((UpdateStockPacket*)buf);
	case PACKET_DELETESTOCK:	return delete_stock((DeleteStockPacket*)buf);
	case PACKET_SELECTALLSTOCK:	return selectall_stock((SelectAllStockPacket*)buf);
	case PACKET_SAVEALLSTOCK:	return saveall_stock((SelectAllStockPacket*)buf);
	}
	return 0;
}

int add_stock(AddStockPacket* packet)
{
	//request 单捞磐 贸府
	STOCK member = stock_createstock(packet->name, packet->made, packet->date, packet->price);
	stocks.push_back(member);
	printf("历厘 肯丰\n");

	//response 贸府
	AddStockAckPacket ack = pack_AddStock(true, member.name);
	memcpy_s(packet, sizeof(AddStockAckPacket), (char*)&ack, sizeof(AddStockAckPacket));
	return sizeof(AddStockAckPacket);
}

int select_stock(SelectStockPacket* packet)
{
	//request 单捞磐 贸府
	STOCK member;
	memset(&member, 0, sizeof(STOCK));
	bool result = find_stock(packet->name, &member);
	printf("八祸 肯丰\n");
	
	//response 贸府
	SelectStockAckPacket ack = pack_SelectStock(result, member.name, member.made, member.date, member.price);
	memcpy_s(packet, sizeof(SelectStockAckPacket), (char*)&ack, sizeof(SelectStockAckPacket));
	return sizeof(SelectStockAckPacket);
}

bool find_stock(const char* name, STOCK* pstock)
{
	for (int i = 0; i < stocks.size(); i++)
	{
		STOCK stock = stocks[i];
		if (strcmp(stock.name, name) == 0)
		{
			*pstock = stock;
			return true;
		}
	}
	return false;
}

int find_stock_idx(const char* name)
{
	for (int i = 0; i < stocks.size(); i++)
	{
		STOCK stock = stocks[i];
		if (strcmp(stock.name, name) == 0)
		{			
			return i;
		}
	}
	return -1;
}

int update_stock(UpdateStockPacket* packet)
{
	//request 单捞磐 贸府
	int idx = find_stock_idx(packet->name);
	if (idx != -1)
	{
		stock_setmade(&stocks[idx], packet->made);
		stock_setdate(&stocks[idx], packet->date);
		stock_setprice(&stocks[idx], packet->price);
	}	
	printf("荐沥 肯丰\n");

	//response 贸府
	UpdateStockAckPacket ack;
	if(idx != -1)
		ack = pack_UpdateStock(true, packet->name);
	else
		ack = pack_UpdateStock(false, packet->name);
	memcpy_s(packet, sizeof(UpdateStockAckPacket), (char*)&ack, sizeof(UpdateStockAckPacket));
	return sizeof(UpdateStockAckPacket);
}

int delete_stock(DeleteStockPacket* packet)
{
	//request 单捞磐 贸府
	int idx = find_stock_idx(packet->name);
	if (idx != -1)
	{
		stocks.erase(stocks.begin() + idx);
	}
	printf("昏力 肯丰\n");

	//response 贸府
	DeleteStockAckPacket ack;
	if (idx != -1)
		ack = pack_DeleteStock(true, packet->name);
	else
		ack = pack_DeleteStock(false, packet->name);
	memcpy_s(packet, sizeof(DeleteStockAckPacket), (char*)&ack, sizeof(DeleteStockAckPacket));
	return sizeof(DeleteStockAckPacket);
}

int selectall_stock(SelectAllStockPacket* packet)
{
	//单捞磐 贸府

	//response 贸府
	SelectAllAckPacket ack;
	ack = pack_SelectAllStock(stocks);

	memcpy_s(packet, sizeof(SelectAllAckPacket), (char*)&ack, sizeof(SelectAllAckPacket));
	return sizeof(SelectAllAckPacket);
}

int saveall_stock(SelectAllStockPacket* packet) // save all stock to file(stocks.txt) client, server both side.
{
	//单捞磐 贸府

	//response 贸府
	SelectAllAckPacket ack;
	ack = pack_SaveAllStock(stocks);

	memcpy_s(packet, sizeof(SelectAllAckPacket), (char*)&ack, sizeof(SelectAllAckPacket));
	return sizeof(SelectAllAckPacket);
}