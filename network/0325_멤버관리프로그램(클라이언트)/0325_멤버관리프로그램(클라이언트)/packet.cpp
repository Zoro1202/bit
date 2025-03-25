#include "std.h"

//���� ��
void msg_parsing(char* buf)
{
	//�Ľ�
	int* flag = (int*)buf;
	if (*flag == PACKET_ADDMEMBER_S)
	{
		//----- ���� ------------------------------------------------------
		//��Ŷ �Ľ�
		AddMemberAckPacket* packet = (AddMemberAckPacket*)buf;
		printf("%s���� ȸ�������� �����߽��ϴ�.\n", packet->name);
	}
	else if (*flag == PACKET_ADDMEMBER_F)
	{
		AddMemberAckPacket* packet = (AddMemberAckPacket*)buf;
		printf("���� ����\n");
	}
	else if (*flag == PACKET_SELECTMEMBER_S)
	{
		SelectMemberAckPacket* packet = (SelectMemberAckPacket*)buf;
		printf("�̸� : %s\n", packet->name);
		printf("��ȭ��ȣ : %s\n", packet->phone);
		printf("���� %d\n", packet->age);
	}
	else if (*flag == PACKET_SELECTMEMBER_F)
	{
		printf("�˻� ����\n");
	}
	else if (*flag == PACKET_SHORTMESSAGE)
	{
		ShortMessagePacket* packet = (ShortMessagePacket*)buf;
		printf("[%s] %s\n", packet->name, packet->msg);
	}
}

