// UDP_C.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//TCPIP-UDP
#include "WSA_Sync.h" // TCPIP

SOCKET CSock;
sockaddr_in CAddr;

// * receive message
void Fun(PVOID P)
{
    int i, Len = sizeof(sockaddr);
    char S1[2000];
    sockaddr Addr;

    while (1)
    {
        i = recvfrom(CSock, S1, sizeof(S1) - 1, 0, &Addr, &Len);
        if (i > 0)
        {
            S1[i] = 0;
            printf("> %s\n", S1);
        }
    }
}

int main(int argc, char *argv[])
{
    char S1[2000];
    int Len = sizeof(sockaddr);

    // activate UDP Client
    Start_UDP_Client(&CSock, &CAddr, "127.0.0.1", 6000);
    _beginthread(Fun, 0, NULL);

    // * read keyboard & send message
    while (1)
    {
        printf("input> ");
        scanf("%s", S1);
        sendto(CSock, S1, strlen(S1), 0, (sockaddr *)&CAddr, Len);
    }

    return 0;
}
