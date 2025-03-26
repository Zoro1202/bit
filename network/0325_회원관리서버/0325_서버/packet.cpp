//packet.cpp
#include "std.h"

AddStockAckPacket pack_AddStock(bool flag, const char* name)
{
	AddStockAckPacket packet;
	if(flag == true)
		packet.flag = PACKET_ADDSTOCK_S;
	else
		packet.flag = PACKET_ADDSTOCK_F;
	strcpy_s(packet.name, sizeof(packet.name), name);

	return packet;
}

SelectStockAckPacket pack_SelectStock(bool flag, const char* name, const char* made, const char* date, int price)
{
	SelectStockAckPacket packet;
	if (flag == true)
		packet.flag = PACKET_SELECTSTOCK_S;
	else
		packet.flag = PACKET_SELECTSTOCK_F;
	strcpy_s(packet.name, sizeof(packet.name), name);
	strcpy_s(packet.made, sizeof(packet.made), made);
	strcpy_s(packet.date, sizeof(packet.date), date);
	packet.price = price;

	return packet;
}

UpdateStockAckPacket pack_UpdateStock(bool flag, const char* name)
{
	UpdateStockAckPacket packet;
	if (flag == true)
		packet.flag = PACKET_UPDATESTOCK_S;
	else
		packet.flag = PACKET_UPDATESTOCK_F;
	strcpy_s(packet.name, sizeof(packet.name), name);

	return packet;
}

DeleteStockAckPacket pack_DeleteStock(bool flag, const char* name)
{
	DeleteStockAckPacket packet;
	if (flag == true)
		packet.flag = PACKET_DELETESTOCK_S;
	else
		packet.flag = PACKET_DELETESTOCK_F;
	strcpy_s(packet.name, sizeof(packet.name), name);

	return packet;
}

SelectAllAckPacket pack_SelectAllStock(vector<STOCK>& stocks)
{
	SelectAllAckPacket packet;

	packet.flag = PACKET_SELECTALLSTOCK;
	packet.size = (int)stocks.size();
	for (int i = 0; i < stocks.size(); i++)
	{
		packet.stocks[i] = stocks[i];
	}

	return packet;
}

SelectAllAckPacket pack_SaveAllStock(vector<STOCK>& stocks)
{
	SelectAllAckPacket packet;

	packet.flag = PACKET_SAVEALLSTOCK;
	packet.size = (int)stocks.size();
	for (int i = 0; i < stocks.size(); i++)
	{
		packet.stocks[i] = stocks[i];
	}

	return packet;
}