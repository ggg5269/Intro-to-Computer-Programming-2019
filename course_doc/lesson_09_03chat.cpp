//print IP and private chat
// chat.cpp : Defines the entry point for the console application.
//

#include "stdio.h"
#include "WSA_Sync.h"

SOCKET SSock, CSock;
sockaddr_in SAddr, CAddr;

void Fun(PVOID pvoid)
{
	int i, Len = sizeof(sockaddr);
	char S1[2000];
	sockaddr_in Addr;

	while (1)
	{
		i = recvfrom(SSock, S1, sizeof(S1) - 1, 0, (sockaddr *)&Addr, &Len);
		if (i > 0)
		{
			S1[i] = 0;
			printf("Chat(%s):< %s\n", inet_ntoa(Addr.sin_addr), S1);
		}
	}
}

int main(int argc, char *argv[])
{
	int i, Len = sizeof(sockaddr);
	char S1[2000];

	// 啟動 UDP server接收資料
	Start_UDP_Server(&SSock, 6000);
	_beginthread(Fun, 0, NULL); // begin multi-thread

	// 啟動 UDP CLIENT 傳輸資料
	Start_UDP_Client(&CSock, &CAddr, "192.168.13.41", 6000);
	while (1)
	{
		printf("chat:> ");
		scanf("%s", S1);
		sendto(CSock, S1, strlen(S1), 0, (sockaddr *)&CAddr, Len);
	}
	return 0;
}
