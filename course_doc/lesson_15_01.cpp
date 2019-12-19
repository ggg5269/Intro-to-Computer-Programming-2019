// game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "conio.h"

#define W 32 // width
#define H 32 // height

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

    // check vertical direction
    /*
	for (x=0;x<W;x+=2)
	{
		z = 0;
		for(y = 0;y < H; y += 2)
		{
			if (T[x][y] == 'O') z++; else z = 0;
			if (z == 5) 
			{
				for (y1 = y; y1 > y - 10; y1 -= 2)
				{
					gotoxy(x, y1, 12);
					printf("O");
				}
				gotoxy(0, H, 7); printf("五子連線");
			}
		}
	}
	*/
}

int main(int argc, char *argv[])
{
    int x, y, rx, ry;
    int cx, cy;
    int x1 = 0, y1 = 0;
    unsigned char c;

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
        if (c == 0x0d)
        {
            T[cx][cy] = 'O';
            printf("O");
        }
        else if (c == 0x20)
        {
            T[cx][cy] = 'X';
            printf("X");
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
