//control.cpp
#include "std.h"

#define SERVER_PORT		9000

vector<STOCK> stocks;

void con_init()
{
	if (net_initlibrary() == false)
	{
		printf("���� �ʱ�ȭ ����\n");
		exit(-1);
	}
	if (net_create_socket(SERVER_PORT) == false)
	{
		printf("���� ���� ����..\n");
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
	printf("���� ���.....................\n");
	HANDLE hthread = CreateThread(0, 0, listen_thread, 0, 0, 0);

	WaitForSingleObject(hthread, INFINITE);
	CloseHandle(hthread);
}

//---------------- ��� ------------------------------------
int con_msg_parsing(char* buf)
{
	//�Ľ�
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
	//request ������ ó��
	STOCK member = stock_createstock(packet->name, packet->made, packet->date, packet->price);
	stocks.push_back(member);
	printf("���� �Ϸ�\n");

	//response ó��
	AddStockAckPacket ack = pack_AddStock(true, member.name);
	memcpy_s(packet, sizeof(AddStockAckPacket), (char*)&ack, sizeof(AddStockAckPacket));
	return sizeof(AddStockAckPacket);
}

int select_stock(SelectStockPacket* packet)
{
	//request ������ ó��
	STOCK member;
	memset(&member, 0, sizeof(STOCK));
	bool result = find_stock(packet->name, &member);
	printf("�˻� �Ϸ�\n");
	
	//response ó��
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
	//request ������ ó��
	int idx = find_stock_idx(packet->name);
	if (idx != -1)
	{
		stock_setmade(&stocks[idx], packet->made);
		stock_setdate(&stocks[idx], packet->date);
		stock_setprice(&stocks[idx], packet->price);
	}	
	printf("���� �Ϸ�\n");

	//response ó��
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
	//request ������ ó��
	int idx = find_stock_idx(packet->name);
	if (idx != -1)
	{
		stocks.erase(stocks.begin() + idx);
	}
	printf("���� �Ϸ�\n");

	//response ó��
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
	//������ ó��

	//response ó��
	SelectAllAckPacket ack;
	ack = pack_SelectAllStock(stocks);

	memcpy_s(packet, sizeof(SelectAllAckPacket), (char*)&ack, sizeof(SelectAllAckPacket));
	return sizeof(SelectAllAckPacket);
}

int saveall_stock(SelectAllStockPacket* packet) // save all stock to file(stocks.txt) client, server both side.
{
	//������ ó��

	//response ó��
	SelectAllAckPacket ack;
	ack = pack_SaveAllStock(stocks);

	memcpy_s(packet, sizeof(SelectAllAckPacket), (char*)&ack, sizeof(SelectAllAckPacket));
	return sizeof(SelectAllAckPacket);
}