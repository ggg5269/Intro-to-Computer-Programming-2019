// UDP_S.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//TCPIP-UDP
#include "WSA_Sync.h" // TCPIP

SOCKET SSock;
#define MAX 10
sockaddr SAddr[MAX]; // store clients info.(IP, port), keep at most 10 IPs online
int Cur = 0;         // store current clients number

#define CON(x) ((x >> 8) & 0xFF) + ((x & 0xFF) << 8)
int main(int argc, char *argv[])
{
    char S1[2000];
    int i, j, Len = sizeof(sockaddr);
    sockaddr Addr[10];
    sockaddr_in *lp = (sockaddr_in *)&Addr;

    // activate UDP Server
    Start_UDP_Server(&SSock, 6000);

    // receive message and send to others
    while (1)
    {
        i = recvfrom(SSock, S1, sizeof(S1) - 1, 0, (sockaddr *)&Addr, &Len);
        if (i > 0)
        {
            S1[i] = 0; // end of string

            // check remote user
            for (j = 0; j < Cur; j++)
            {
                if (!memcmp(&Addr, &SAddr[j], Len))
                    break; // compare new client with data we record before
            }

            if (j >= Cur) // client not found, add new user
            {
                memcpy(&SAddr[Cur], &Addr, Len);
                Cur++;
            }
            // send message to others
            for (i = 0; i < Cur; i++)
            {
                if (i != j)
                    sendto(SSock, S1, strlen(S1), 0, &SAddr[i], Len);
            }
            printf("[%d:%d][%s:%d]>%s\n", Cur, j + 1, inet_ntoa(lp->sin_addr), CON(lp->sin_port), S1);
        }
    }
    return 0;
}
