// TCP_C.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WSA_Sync.h"
SOCKET Sock;

void Fun(PVOID p)
{
    int i;
    char S1[2000];
    while (1)
    {
        i = recv(Sock, S1, sizeof(S1) - 1, 0); // ! in TCP, we use recv function instead of recvfrom
        if (i > 0)
        {
            S1[i] = 0;
            printf(">%s\n", S1);
        }
        else
        {
            printf("server disconnected\n");
            closesocket(Sock);
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    char S1[2000];

    // * activate TCP Client
    Start_TCP_Client(&Sock, 6000, "127.0.0.1");
    printf("connected\n");
    _beginthread(Fun, 0, NULL);

    // * scan & send message
    while (1)
    {
        printf("> ");
        scanf("%s", S1);
        send(Sock, S1, strlen(S1), 0); // use send function
    }
    return 0;
}
