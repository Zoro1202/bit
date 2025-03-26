//packet.h
#pragma once

#define PACKET_ADDSTOCK       1			 //flag, �̸�, ��ȭ��ȣ, ����
#define PACKET_SELECTSTOCK    2			 //flag, �̸�
#define PACKET_UPDATESTOCK    3			 //flag, �̸�,  up��ȭ��ȣ, up����
#define PACKET_DELETESTOCK    4			 //flag, �̸�
#define PACKET_SELECTALLSTOCK 5			 //flag, ��û�ѻ���̸�
#define PACKET_SAVEALLSTOCK	  6			 //flag, ��û�ѻ���̸�

#define PACKET_ADDSTOCK_S			20		//flag, ����, �̸�
#define PACKET_ADDSTOCK_F			21		//flag  ����, �̸�
#define PACKET_SELECTSTOCK_S		22		//flag, ����, �̸�, ��ȭ��ȣ, ����
#define PACKET_SELECTSTOCK_F		23		//flag, ����, X, X, X
#define PACKET_UPDATESTOCK_S		24		//flag, ����, �̸�
#define PACKET_UPDATESTOCK_F		25		//flag, ����, �̸�
#define PACKET_DELETESTOCK_S		26		//flag, ����, �̸�
#define PACKET_DELETESTOCK_F		27		//flag, ����, �̸�
//#define PACKET_SELECTALLSTOCK 5			//������ ��Ŷ �÷��׿� �����ϰ�

//request(��û) : Clinet -> Server
//PACKET_ADDSTOCK
struct AddStockPacket
{
	int   flag;
	char name[20];
	char made[20];
	char date[20];
	int price;
};

//PACKET_SELECTSTOCK
struct SelectStockPacket {
	int flag;
	char name[20];
};

//PACKET_UPDATESTOCK
typedef AddStockPacket UpdateStockPacket;

//PACKET_DELETESTOCK
typedef SelectStockPacket DeleteStockPacket;

//PACKET_SELECTALLSTOCK
typedef SelectStockPacket SelectAllStockPacket;


//response(����) : Clinet -> Server
//PACKET_ADDSTOCK_S / F
struct AddStockAckPacket
{
	int flag;
	char name[20];
};

//PACKET_SELECTSTOCK_S / F
typedef AddStockPacket SelectStockAckPacket;

//PACKET_UPDATESTOCK_S / F
typedef AddStockAckPacket UpdateStockAckPacket;

//PACKET_DELETESTOCK_S / F
typedef AddStockAckPacket DeleteStockAckPacket;

//PACKET_SELECTALLSTOCK
struct SelectAllAckPacket
{
	int flag;
	STOCK stocks[15];
	int size;
};

AddStockAckPacket pack_AddStock(bool flag, const char* name);
SelectStockAckPacket pack_SelectStock(bool flag, const char* name, const char* made, const char* date, int price);
UpdateStockAckPacket pack_UpdateStock(bool flag, const char* name);
DeleteStockAckPacket pack_DeleteStock(bool flag, const char* name);
SelectAllAckPacket pack_SelectAllStock(vector<STOCK>& stocks);
SelectAllAckPacket pack_SaveAllStock(vector<STOCK>& stocks);
