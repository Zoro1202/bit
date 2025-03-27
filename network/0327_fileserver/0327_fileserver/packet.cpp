//packet.cpp
#include "std.h"

FileListAckPack pack_filelist(char(*files)[30], int size)
{
	FileListAckPack packet;
	packet.flag = PACKET_FILE_LIST_ACK;
	packet.count = size;
	for (int i = 0; i < packet.count; i++)
	{
		strcpy_s(packet.filename[i], sizeof(packet.filename[i]), files[i]);
		//lstrcpy(packet.filename[i], files[i]);
	}

	return packet;
}

FileDownloadPackAck pack_fileDown(char* filename, int size)
{
	FileDownloadPackAck packet;
	packet.flag = PACKET_FILE_DOWNLOAD_ACK;
	packet.filesize = size;
	strcpy_s(packet.filename, sizeof(packet.filename), filename);

	return packet;
}
