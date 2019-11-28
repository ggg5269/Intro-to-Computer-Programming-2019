#include "stdafx.h"
#include "WSA_Sync.h"
#include "conio.h"
// 120.92.212.76
SOCKET Sock;

void Fun(PVOID p)
{
    int i;
    char S1[2000];
    while (1)
    {
        i = recv(Sock, S1, sizeof(S1) - 1, 0);
        if (i > 0)
        {
            S1[i] = 0;
            printf("%s", S1);
        }
    }
}

void key_up()
{
    unsigned char c1, c2, c3;
    c1 = 0x1b;
    c2 = 0x5b;
    c3 = 0x41;
    send(Sock, (char *)&c1, 1, 0);
    send(Sock, (char *)&c2, 1, 0);
    send(Sock, (char *)&c3, 1, 0);
}

void key_down()
{
    unsigned char c1, c2, c3;
    c1 = 0x1b;
    c2 = 0x5b;
    c3 = 0x42;
    send(Sock, (char *)&c1, 1, 0);
    send(Sock, (char *)&c2, 1, 0);
    send(Sock, (char *)&c3, 1, 0);
}

void key_left()
{
    unsigned char c1, c2, c3;
    c1 = 0x1b;
    c2 = 0x5b;
    c3 = 0x44;
    send(Sock, (char *)&c1, 1, 0);
    send(Sock, (char *)&c2, 1, 0);
    send(Sock, (char *)&c3, 1, 0);
}

void key_right()
{
    unsigned char c1, c2, c3;
    c1 = 0x1b;
    c2 = 0x5b;
    c3 = 0x43;
    send(Sock, (char *)&c1, 1, 0);
    send(Sock, (char *)&c2, 1, 0);
    send(Sock, (char *)&c3, 1, 0);
}

int main(int argc, char *argv[])
{
    unsigned char c1, c2;
    char Buf[10];
    int flag = 0;

    // ! 設定螢幕顏色控制
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hCon, &mode);
    mode |= 0x0004;
    SetConsoleMode(hCon, mode);

    // * BBS Terminal (TCP Client)
    // BBS server: 61.31.92.42:23

    Start_TCP_Client(&Sock, 23, "61.31.92.42");

    // * multithread
    _beginthread(Fun, 0, 0);

    // read keyboard & send message
    while (1)
    {
        c1 = getch();
        if (c1 == 0xe0)
        {
            c2 = getch();
            if (c2 == 0x48)
                key_up();
            else if (c2 == 0x50)
                key_down();
            else if (c2 == 0x4b)
                key_left();
            else if (c2 == 0x4d)
                key_right();
        }
        else
        {
            //printf("c1 = %x\n", c1);
            send(Sock, (char *)&c1, 1, 0);
        }
    }
    return 0;
}
