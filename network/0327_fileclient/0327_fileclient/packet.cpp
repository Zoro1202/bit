//packet.cpp
#include "std.h"

FileListPack pack_filelist()
{
	FileListPack packet;
	
	packet.flag = PACKET_FILE_LIST;

	return packet;
}

FileDownloadPack pack_filedown(char * filename)
{
	FileDownloadPack packet;
	
	packet.flag = PACKET_FILE_DOWNLOAD;
	strcpy_s(packet.filename, sizeof(packet.filename), filename);
	return packet;
}
