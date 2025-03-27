//packet.h
#pragma once

#define PACKET_FILE_LIST			1 //flag
#define PACKET_FILE_LIST_ACK		2 //flag ���ϸ� ����Ʈ

#define PACKET_FILE_DOWNLOAD		3 //flag ���ϸ�
#define PACKET_FILE_DOWNLOAD_ACK	4 //flag ���ϸ�, ����ũ��, ���� ������

#define PACKET_FILE_DATA			5 //flag, data

//request��û ��Ŷ
struct FileListPack
{
	int flag;
};

//response���� ��Ŷ
struct FileListAckPack
{
	int flag;
	char filename[50][30];
	int count;
};
struct FileDownloadPack
{
	int flag;
	char filename[30];
};
struct FileDownloadPackAck
{
	int flag;
	char filename[30];
	int filesize;
};

FileListAckPack pack_filelist(char(*files)[30], int size);
FileDownloadPackAck pack_fileDown(char * filename, int size);