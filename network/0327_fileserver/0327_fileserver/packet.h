//packet.h
#pragma once

#define PACKET_FILE_LIST			1 //flag
#define PACKET_FILE_LIST_ACK		2 //flag 파일명 리스트

#define PACKET_FILE_DOWNLOAD		3 //flag 파일명
#define PACKET_FILE_DOWNLOAD_ACK	4 //flag 파일명, 파일크기, 파일 데이터

#define PACKET_FILE_DATA			5 //flag, data

//request요청 패킷
struct FileListPack
{
	int flag;
};

//response응답 패킷
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