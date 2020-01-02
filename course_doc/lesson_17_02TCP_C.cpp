// select_TCP_C.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WSA_Sync.h"

SOCKET Sock;
void Fun(PVOID p)
{
    char S1[2000];
    int i;

    while (1)
    {
        i = recv(Sock, S1, sizeof(S1) - 1, 0);

        if (i > 0)
        {
            S1[i] = 0;
            printf("%s\n", S1);
        }
        else
        {
            closesocket(Sock);
            printf("disconnected");
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    char S1[2000];

    // start tcp client & thread
    Start_TCP_Client(&Sock, 6000, "127.0.0.1");
    _beginthread(Fun, 0, 0);

    // keyboard
    while (1)
    {
        printf("Input = ");
        scanf("%s", S1);
        send(Sock, S1, strlen(S1), 0);
    }
    return 0;
}
