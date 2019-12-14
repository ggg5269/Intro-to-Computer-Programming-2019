// FTP_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WSA_Sync.h"
#include "conio.h"
#include "string"

SOCKET Sock;

// receive data
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
            printf("%s\r\n", S1);
        }
    }
}

int main(int argc, char *argv[])
{
    system("chcp 65001");
    char S1[2000], ID[100], pass[100];
    char cwd[] = "cwd";
    char cd[] = "cd";
    char mkd[] = "mkd";
    char mkdir[] = "mkdir";
    char rmd[] = "rmd";
    char rmdir[] = "rmd";
    char *result = NULL;
    int i;

    // * 連線FTP Server
    Start_TCP_Client(&Sock, 21, "107.175.17.172");
    _beginthread(Fun, 0, 0);
    Sleep(1000);

    // * send studrnt ID
    printf("ID = ");
    scanf("%s", ID);
    sprintf(S1, "USER %s\r\n", ID);
    send(Sock, S1, strlen(S1), 0);
    Sleep(1000);

    // * send pass
    /*
	printf("pass = ");
	scanf("%s", pass);
	sprintf(S1, "PASS %s\r\n", pass);
	send(Sock, S1, strlen(S1), 0);
	Sleep(1000);
	*/
    printf("pass = ");
    i = 0;
    do
    {
        pass[i++] = getch();
        printf("*");
    } while (pass[i - 1] != 0x0d);
    pass[i - 1] = 0;
    printf("\r\n");

    sprintf(S1, "PASS %s\r\n", pass);
    send(Sock, S1, strlen(S1), 0);
    Sleep(1000);

    //  * Read KB & Send Msg
    while (1)
    {
        printf("FTP> ");
        // scanf("%s", S1);

        i = 0;
        do
        {
            S1[i++] = getche();
        } while (S1[i - 1] != 0x0d);
        S1[i - 1] = 0;
        printf("\r\n");
        if (!strcmp(S1, "cd 0753736"))
        {
            strcpy(S1, "cwd 0753736");
        }
        if (!strcmp(S1, "mkdir 0753736"))
        {
            strcpy(S1, "mkd 0753736");
        }
        if (!strcmp(S1, "rmdir 0753736"))
        {
            strcpy(S1, "rmd 0753736");
        }
        // ! end of string
        strcat(S1, "\r\n");

        send(Sock, S1, strlen(S1), 0);
        Sleep(1000);
    }

    return 0;
}
