#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")//���ÿ��ļ�
using namespace std;



SOCKADDR_IN addrSrv;
WSADATA wsaData;
char buff[5];
SOCKET sockClient;
char buffs[5];
int numbuff[5];
char objIP[15];

void changeint(int num[5])
{
	for (int i = 0; i < 5; i++)
		buffs[i] = num[i] + 48;
}

void changchar()
{
	for (int i = 0; i < 5; i++)
		numbuff[i] = buffs[i] - 48;
}


int initnet()
{
	//�����׽���
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(8888);//�˿ں�
	addrSrv.sin_addr.S_un.S_addr = inet_addr(objIP);//IP��ַ



	memset(buff, 0, sizeof(buff));

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 0;
	}


	//�����׽���
	sockClient = socket(AF_INET, SOCK_STREAM, 0);//�����׽���
	if (SOCKET_ERROR == sockClient) {
		return 0;
	}

	//�������������������
	if (connect(sockClient, (struct  sockaddr*)&addrSrv, sizeof(addrSrv)) == INVALID_SOCKET)
	{
		return 0;
	}
	return 1;
}


void endnet()
{
	//�ر��׽���
	closesocket(sockClient);
	WSACleanup();//�ͷų�ʼ��Ws2_32.dll���������Դ��
}