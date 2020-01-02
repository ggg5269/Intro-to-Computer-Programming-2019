// select_TCP_S.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WSA_Sync.h"
#define MAX 100

SOCKET SSock, CSock[MAX];

struct DATA
{
	int Flag;
	SOCKET Sock;	// TCP socket
	int Port;		// Port number
	char IP[100];   // IP adress
	char Msg[1000]; // last msg
	int Up;			// uplink data
	int Down;		// downlink data
};

DATA Data[MAX];
int Data_No = 0;

// manage TCP terminal
int Init_Data()
{
	// initial Data Structure
	for (int i = 0; i < MAX; i++)
	{
		Data[i].Flag = 0;
		Data[i].Up = Data[i].Down = 0;
		Data[i].Sock = Data[i].Port = 0;
		Data[i].IP[0] = Data[i].Msg[i] = 0;
	}
	Data_No = 0;
	return 0;
}

int Search_Data(SOCKET Sock)
{
	int i;

	for (i = 0; i < MAX; i++)
	{
		if ((Data[i].Flag) && (Sock == Data[i].Sock))
			break;
	}
	if (i < MAX)
		return i; // i == ith socket
	else
		return -1;
}

int Add_Data(SOCKET Sock, sockaddr *lp)
{
	int i;
	sockaddr_in *lp1 = (sockaddr_in *)lp;

	i = Search_Data(Sock);
	if (i >= 0)
		return i;
	for (i = 0; i < MAX; i++)
		if (!Data[i].Flag)
			break;
	if (i < MAX)
	{
		Data[i].Flag = 1;
		Data_No++;
		Data[i].Sock = Sock;
		strcpy(Data[i].IP, inet_ntoa(lp1->sin_addr));
		Data[i].Port = lp1->sin_port;
		Data[i].Up = Data[i].Down = Data[i].Msg[0] = 0;
		return i;
	}
	else
		return -1; // buffer(MAX) Full
}
int Delete_Data(SOCKET Sock)
{
	int i;
	i = Search_Data(Sock);
	if (i >= 0)
	{
		Data[i].Flag = Data[i].Sock = Data[i].Up = Data[i].Down = 0;
		Data[i].IP[0] = Data[i].Msg[0] = Data[i].Port = 0;
		Data_No--;
		return i;
	}
	else
		return -1;
}

int Print_Data()
{
	int i;
	DATA *lp;

	system("cls");
	for (i = 0; i < MAX; i++)
	{
		if (Data[i].Flag == 1)
		{
			lp = &Data[i];
			printf("%2d Sock = %4d [%10s:%5d] [U:%d/D:%d] Msg = %s\n",
				   i + 1, lp->Sock, lp->IP, lp->Port, lp->Up, lp->Down, lp->Msg);
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{

	fd_set fd_src, fd_tmp;
	SOCKET wParam;
	int i, k, Len = sizeof(sockaddr), CSock_No = 0;
	char S1[2000], S2[2000];
	sockaddr Addr;

	// Init
	Init_Data();
	FD_ZERO(&fd_src);

	// start TCP SERVER
	Start_TCP_Server(&SSock, 6000);
	FD_SET(SSock, &fd_src);
	printf("TCP_SERVER START\n");

	// check socket status
	while (1)
	{
		fd_tmp = fd_src;
		i = select(0, &fd_tmp, 0, 0, 0);
		if (i < 0)
			break;
		wParam = fd_tmp.fd_array[0];

		//wParam = fd_src.fd_array[i];
		if (FD_ISSET(wParam, &fd_tmp))
		{
			// request connect
			if (wParam == SSock)
			{
				// accept()
				CSock[CSock_No] = accept(wParam, &Addr, &Len);
				Add_Data(CSock[CSock_No], &Addr);
				FD_SET(CSock[CSock_No], &fd_src);
				CSock_No++;
				Print_Data();
				// printf("%d connected, %d clients online\n", CSock[CSock_No - 1], CSock_No);
			}
			else
			{
				// recv message
				i = recv(wParam, S1, sizeof(S1) - 1, 0);
				if (i > 0)
				{
					S1[i] = 0;
					k = Search_Data(wParam);
					if (k < MAX)
					{
						Data[k].Down += i;
						strcpy(Data[k].Msg, S1);

						sprintf(S2, "recv(%s)", S1);
						i = send(wParam, S2, strlen(S2), 0);
						Data[k].Up += i;
						Print_Data();
					}
					// printf("RECV(%d) = %s\n", wParam, S1);
				}
				else
				{
					closesocket(wParam);
					FD_CLR(wParam, &fd_src);
					Delete_Data(wParam);
					// printf("disconnected(%d)\n", wParam);
					Print_Data();
				}
			}
		}
	}
	return 0;
}
