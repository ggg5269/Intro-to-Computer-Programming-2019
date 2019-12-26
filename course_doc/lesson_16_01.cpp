// game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include "WSA_Sync.h"

SOCKET SSock;    //TCP server
SOCKET CSock;    //TCP client
SOCKET ASock;    //TCP server: accept
SOCKET Sock = 0; //Used

enum STATE
{
    READY,
    PLAY,
    STOP
};
STATE state;
int Flag = 0;

#define W 80 // width
#define H 40 // height

char T[W][H]; // game status
int V[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
// 五子棋

void gotoxy(int xpos, int ypos, int color)
{
    // color: 1(B) 2(G) 4(R) 8(I)
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
    SetConsoleTextAttribute(hOuput, color);
}

// check3 blue:1(B) + 8(L)
void Check3(unsigned char c)
{
    int x, y;
    int x1, y1;
    int i, j, k3 = 0;

    for (y = 0; y < H; y += 2)
    {
        for (x = 0; x < W; x += 2)
        {
            for (i = 0; i < 8; i++) // 8 direction
            {
                for (k3 = 0, j = 0; j < 6; j += 2) // 3
                {
                    x1 = x + j * V[i][0];
                    y1 = y + j * V[i][1];

                    if ((x1 >= 0) && (x1 < W) && (y1 >= 0) && (y1 < H))
                    {
                        if (T[x1][y1] == c)
                            k3++;
                        else
                            k3 = 0;
                        if (k3 == 3 && (T[x - 2 * V[i][0]][y - 2 * V[i][1]] == 0x20) && (T[x1 + 2 * V[i][0]][y1 + 2 * V[i][1]] == 0x20))
                        {
                            for (j = 4; j >= 0; j -= 2)
                            {
                                x1 = x + j * V[i][0];
                                y1 = y + j * V[i][1];

                                gotoxy(x1, y1, 9);
                                printf("%c", c);
                            }
                            gotoxy(0, H, 7);
                            printf("活三　　");
                        }
                    }
                    else
                        k3 = 0;
                }
            }
        }
    }
}

// check4 green:2(G) + 8(L)
void Check4(unsigned char c)
{
    int x, y;
    int x1, y1;
    int i, j, k3 = 0;

    for (y = 0; y < H; y += 2)
    {
        for (x = 0; x < W; x += 2)
        {
            for (i = 0; i < 8; i++) // 8 direction
            {
                for (k3 = 0, j = 0; j < 8; j += 2) // 4
                {
                    x1 = x + j * V[i][0];
                    y1 = y + j * V[i][1];

                    if ((x1 >= 0) && (x1 < W) && (y1 >= 0) && (y1 < H))
                    {
                        if (T[x1][y1] == c)
                            k3++;
                        else
                            k3 = 0;
                        if (k3 == 4 && (T[x - 2 * V[i][0]][y - 2 * V[i][1]] != c) && (T[x - 2 * V[i][0]][y - 2 * V[i][1]] != 0x20) && (T[x1 + 2 * V[i][0]][y1 + 2 * V[i][1]] == 0x20))
                        {
                            for (j = 6; j >= 0; j -= 2)
                            {
                                x1 = x + j * V[i][0];
                                y1 = y + j * V[i][1];

                                gotoxy(x1, y1, 10);
                                printf("%c", c);
                            }
                            gotoxy(0, H, 7);
                            printf("絕四　　");
                        }
                    }
                    else
                        k3 = 0;
                }
            }
        }
    }
}

// check5 red:4(R) + 8(L)
void Check5(unsigned char c)
{
    int x, y;
    int x1, y1;
    int i, j, k = 0;

    for (y = 0; y < H; y += 2)
    {
        for (x = 0; x < W; x += 2)
        {
            for (i = 0; i < 8; i++) // 8 direction
            {
                for (k = 0, j = 0; j < 10; j += 2) // 5
                {
                    x1 = x + j * V[i][0];
                    y1 = y + j * V[i][1];

                    if ((x1 >= 0) && (x1 < W) && (y1 >= 0) && (y1 < H))
                    {
                        if (T[x1][y1] == c)
                            k++;
                        else
                            k = 0;
                        if (k == 5)
                        {
                            for (j = 8; j >= 0; j -= 2)
                            {
                                x1 = x + j * V[i][0];
                                y1 = y + j * V[i][1];

                                gotoxy(x1, y1, 12);
                                printf("%c", c);
                            }
                            gotoxy(0, H, 7);
                            printf("五子連線");
                        }
                    }
                    else
                        k = 0;
                }
            }
        }
    }
}

void SFun(PVOID p)
{
    sockaddr Addr;
    int Len = sizeof(sockaddr);
    int i, x, y;
    char S1[2000];

    ASock = accept(SSock, &Addr, &Len);
    gotoxy(0, H + 1, 15);
    printf("connected");
    Sock = ASock;

    while (1)
    {
        i = recv(ASock, S1, sizeof(S1) - 1, 0);
        gotoxy(0, H + 1, 15);
        if (i > 0)
        {
            if (!strncmp(S1, "MSG:", 4))
            {
                gotoxy(0, H, 15);
                S1[i] = 0;
                printf("message: %s", &S1[4]);
            }
            else if (Flag == 0)
            {
                S1[i] = 0;
                // printf("%s", S1);
                sscanf(S1, "(%d, %d)", &x, &y);
                gotoxy(x, y, 15);
                printf("X");
                Flag = 1;
                gotoxy(0, H + 1, 15);
                printf("your turn now...");
                T[x][y] = 'X';
                Check3('O');
                Check4('O');
                Check5('O');
                Check3('X');
                Check4('X');
                Check5('X');
            }
        }
        else
        {
            printf("disconnected");
        }
    }
}

void CFun(PVOID p)
{
    char S1[2000];
    int i, x, y;

    while (1)
    {
        i = recv(CSock, S1, sizeof(S1) - 1, 0);
        gotoxy(0, H + 1, 15);
        if (i > 0)
        {
            if (!strncmp(S1, "MSG:", 4))
            {
                gotoxy(0, H, 15);
                S1[i] = 0;
                printf("message: %s", &S1[4]);
            }
            else if (Flag == 0)
            {
                S1[i] = 0;
                // printf("%s", S1);
                sscanf(S1, "(%d, %d)", &x, &y);
                gotoxy(x, y, 15);
                printf("X");
                Flag = 1;
                gotoxy(0, H + 1, 15);
                printf("your turn now...");
                T[x][y] = 'X';
                Check3('O');
                Check4('O');
                Check5('O');
                Check3('X');
                Check4('X');
                Check5('X');
            }
        }
        else
        {
            printf("disconnected");
        }
    }
}

int main(int argc, char *argv[])
{
    int x, y, rx, ry;
    int cx, cy;
    int x1 = 0, y1 = 0;
    unsigned char c;
    char IP[100], S1[2000], MSG[2000];

    // print board
    for (y = 1; y < H; y++)
    {
        for (x = 1; x < W; x++)
        {
            T[x][y] = 0x20;
            gotoxy(x, y, 7);
            if ((y % 2) && (x % 2))
                printf("+");
            else if (y % 2)
                printf("-");
            else if (x % 2)
                printf("|");
        }
    }
    // 1.5 啟動TCP SERVER
    Start_TCP_Server(&SSock, 6000);
    _beginthread(SFun, 0, 0);

    // process keyboard
    cx = W / 2;
    cy = H / 2; // cursor position
    gotoxy(cx, cy, 7);

    do
    {

        c = getch();
        // printf("%02x\n", c);

        // move cursor
        if (c == 0x4d)
            cx += 2; // move right
        else if (c == 0x4b)
            cx -= 2; // move left
        else if (c == 0x50)
            cy += 2; // move down
        else if (c == 0x48)
            cy -= 2; // move up

        // set boundry
        if (cx <= 0)
            cx = 2;
        else if (cx > W - 2)
            cx = W - 2;
        if (cy <= 0)
            cy = 2;
        else if (cy > H - 2)
            cy = H - 2;
        /*
		cx %= W;
		cy %= H;
		*/
        gotoxy(cx, cy, 7);

        // put 'O'
        if ((c == 0x0d) && (Flag == 1))
        {
            T[cx][cy] = 'O';
            printf("O");
            sprintf(S1, "(%d, %d)", cx, cy);
            if (Sock != 0)
                send(Sock, S1, strlen(S1), 0);
            Flag = 0;
            gotoxy(0, H + 1, 15);
            printf("wait...");
        }
        /*// space
        else if (c == 0x20)
        {
            T[cx][cy] = 'X';
            printf("X");
            sprintf(S1, "(%d, %d)", cx, cy);
            if (Sock != 0)
                send(Sock, S1, strlen(S1), 0);
        }
		*/
        else if (c == 'c')
        {
            gotoxy(0, H + 1, 15);
            printf("IP= ");
            scanf("%s", IP);
            Start_TCP_Client(&CSock, 6000, IP);
            _beginthread(CFun, 0, 0);
            Sock = CSock;
            Flag = 1;
            gotoxy(0, H + 1, 15);
            printf("your turn now...");
        }

        else if (c == 'm')
        {
            gotoxy(0, H, 15);
            printf("message = ");
            scanf("%s", MSG);
            sprintf(S1, "MSG: %s", MSG);
            send(Sock, S1, strlen(S1), 0);
        }
        // check
        rx = cx;
        ry = cy;
        for (x1 = 2; x1 < W; x1 += 2)
        {
            for (y1 = 2; y1 < H; y1 += 2)
            {
                gotoxy(x1, y1, 7);
                printf("%c", T[x1][y1]);
            }
        }

        gotoxy(0, H, 7);
        printf("　　　　");
        Check3('O');
        Check4('O');
        Check5('O');
        Check3('X');
        Check4('X');
        Check5('X');

        gotoxy(rx, ry, 7);

    } while (c != 'q');
    gotoxy(0, H, 7);
    printf("End\n");
    return 0;
}
