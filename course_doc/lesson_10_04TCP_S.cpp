// TCP_S.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WSA_Sync.h"
// for TCP Server
SOCKET Sock;
// for remote user
SOCKET Sock1 = 0, Sock2 = 0, Sock3 = 0, Sock4 = 0;
sockaddr Addr1, Addr2, Addr3, Addr4;

// ! remote thread function
// ! 1-1 sock
// ! define 4 Function for 4 clients
void Fun1(PVOID p)
{
    int i;
    char S1[2000];
    while (1)
    {
        i = recv(Sock1, S1, sizeof(S1) - 1, 0); // in TCP, we use recv
        if (i > 0)
        {
            S1[i] = 0;
            printf(">%s\n", S1);
            send(Sock2, S1, strlen(S1), 0);
            send(Sock3, S1, strlen(S1), 0);
            send(Sock4, S1, strlen(S1), 0);
        }
        else
        {
            printf("disconnected\n");
            break;
        }
    }
}

void Fun2(PVOID p)
{
    int i;
    char S1[2000];
    while (1)
    {
        i = recv(Sock2, S1, sizeof(S1) - 1, 0); // in TCP, we use recv
        if (i > 0)
        {
            S1[i] = 0;
            printf(">%s\n", S1);
            send(Sock1, S1, strlen(S1), 0);
            send(Sock3, S1, strlen(S1), 0);
            send(Sock4, S1, strlen(S1), 0);
        }
        else
        {
            printf("disconnected\n");
            break;
        }
    }
}

void Fun3(PVOID p)
{
    int i;
    char S1[2000];
    while (1)
    {
        i = recv(Sock3, S1, sizeof(S1) - 1, 0); // in TCP, we use recv
        if (i > 0)
        {
            S1[i] = 0;
            printf(">%s\n", S1);
            send(Sock1, S1, strlen(S1), 0);
            send(Sock2, S1, strlen(S1), 0);
            send(Sock4, S1, strlen(S1), 0);
        }
        else
        {
            printf("disconnected\n");
            break;
        }
    }
}

void Fun4(PVOID p)
{
    int i;
    char S1[2000];
    while (1)
    {
        i = recv(Sock4, S1, sizeof(S1) - 1, 0); // in TCP, we use recv
        if (i > 0)
        {
            S1[i] = 0;
            printf(">%s\n", S1);
            send(Sock2, S1, strlen(S1), 0);
            send(Sock3, S1, strlen(S1), 0);
            send(Sock1, S1, strlen(S1), 0);
        }
        else
        {
            printf("disconnected\n");
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    char S1[2000];
    int i, Len = sizeof(sockaddr);
    sockaddr Addr;

    // activate TCP Server
    Start_TCP_Server(&Sock, 6000);
    printf("TCP Server 6000 activated\n");

    // ! accept first connection
    Sock1 = accept(Sock, &Addr1, &Len);
    _beginthread(Fun1, 0, NULL);
    printf("user 01 connected\n");

    // ! accept second connection
    Sock2 = accept(Sock, &Addr2, &Len);
    _beginthread(Fun2, 0, NULL);
    printf("user 02 connected\n");

    // ! accept third connection
    Sock3 = accept(Sock, &Addr3, &Len);
    _beginthread(Fun3, 0, NULL);
    printf("user 03 connected\n");

    // ! accept 4th connection...
    Sock4 = accept(Sock, &Addr4, &Len);
    _beginthread(Fun4, 0, NULL);
    printf("user 04 connected\n");

    scanf("%d", &i); // * halt
    return 0;
}
