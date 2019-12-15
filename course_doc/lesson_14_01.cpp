// FTP_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WSA_Sync.h"
#include "conio.h"
#include "string"

// For FTP command
SOCKET Sock;

// For NLST command, download directory
SOCKET NLST_Sock;
int NLST_Flag = 0, NLST_Port;
char NLST_IP[100];
void NLST_Fun(PVOID p);

// For RETR command, download file
SOCKET RETR_Sock;
int RETR_Flag = 0, RETR_Port;
char RETR_IP[100], RETR_File[100];
void RETR_Fun(PVOID p);
FILE *RETR_In;

// For STOR command, upload file
SOCKET STOR_Sock;
int STOR_Flag = 0, STOR_Port;
char STOR_IP[100], STOR_File[100];
void STOR_Fun(PVOID p);

// receive data, [FTP command]
void Fun(PVOID p)
{
    int i, i1, i2, i3, i4, i5, i6;
    char S1[2000];

    while (1)
    {
        i = recv(Sock, S1, sizeof(S1) - 1, 0);
        if (i > 0)
        {
            S1[i] = 0;
            if (NLST_Flag == 1)
            {
                NLST_Flag = 0;

                // Get_IP/PORT
                sscanf(&S1[26], "(%d,%d,%d,%d,%d,%d).\r\n", &i1, &i2, &i3, &i4, &i5, &i6);
                sprintf(NLST_IP, "%d.%d.%d.%d", i1, i2, i3, i4);
                NLST_Port = (i5 << 8) + i6;

                // start TCP client
                Start_TCP_Client(&NLST_Sock, NLST_Port, NLST_IP);
                _beginthread(NLST_Fun, 0, 0);
                send(Sock, "NLST\r\n", 6, 0);
            }
            else if (RETR_Flag == 1)
            {
                RETR_Flag = 0;

                // Get_IP/PORT
                sscanf(&S1[26], "(%d,%d,%d,%d,%d,%d).\r\n", &i1, &i2, &i3, &i4, &i5, &i6);
                sprintf(RETR_IP, "%d.%d.%d.%d", i1, i2, i3, i4);
                RETR_Port = (i5 << 8) + i6;

                // start TCP client
                Start_TCP_Client(&RETR_Sock, RETR_Port, RETR_IP);
                _beginthread(RETR_Fun, 0, 0);
                sprintf(S1, "RETR %s\r\n", RETR_File);
                send(Sock, S1, strlen(S1), 0);
            }
            else if (STOR_Flag == 1)
            {
                STOR_Flag = 0;

                // Get_IP/PORT
                sscanf(&S1[26], "(%d,%d,%d,%d,%d,%d).\r\n", &i1, &i2, &i3, &i4, &i5, &i6);
                sprintf(STOR_IP, "%d.%d.%d.%d", i1, i2, i3, i4);
                STOR_Port = (i5 << 8) + i6;

                // start TCP client
                Start_TCP_Client(&RETR_Sock, RETR_Port, RETR_IP);
                _beginthread(STOR_Fun, 0, 0);
                sprintf(S1, "STOR %s\r\n", STOR_File);
                send(Sock, S1, strlen(S1), 0);
            }
            else
                printf("%s\r\n", S1);
        }
    }
}

// receive data, [FTP NLST]
void NLST_Fun(PVOID p)
{
    int i, j = 1;
    char S1[2000];

    while (j)
    {
        i = recv(NLST_Sock, S1, sizeof(S1) - 1, 0);
        if (i > 0)
        {
            S1[i] = 0;
            printf("%s\r\n", S1);
        }
        else
        {
            j = 0;
            closesocket(NLST_Sock);
        }
    }
    printf("end NLST thread\n");
}

// get data, [FTP RETR]
void RETR_Fun(PVOID p)
{
    int i, j = 1;
    char S1[2000];

    while (j)
    {
        i = recv(RETR_Sock, S1, sizeof(S1) - 1, 0);
        if (i > 0)
        {
            S1[i] = 0;
            // printf("%s\r\n", S1);
            RETR_In = fopen("0753736.txt", "a");
            fprintf(RETR_In, "%s\r\n", S1);
            fclose(RETR_In);
        }
        else
        {
            j = 0;
            closesocket(RETR_Sock);
        }
    }
    printf("end RETR thread\n");
}

// put data, [FTP STOR]
void STOR_Fun(PVOID p)
{
    int i, j = 1;
    char S1[2000];

    while (j)
    {
        i = recv(STOR_Sock, S1, sizeof(S1) - 1, 0);
        if (i > 0)
        {
            S1[i] = 0;
            printf("%s\r\n", S1);
        }
        else
        {
            j = 0;
            closesocket(STOR_Sock);
        }
    }
    printf("end STOR thread\n");
}

int main(int argc, char *argv[])
{
    system("chcp 65001");
    char S1[2000], ID[100], pass[100];
    char A[100], B[100];

    int i;

    // 連線FTP Server
    Start_TCP_Client(&Sock, 21, "107.175.17.172");
    //Start_TCP_Client(&Sock, 21, "140.113.9.151");
    _beginthread(Fun, 0, 0);
    Sleep(1000);

    // send studrnt ID
    printf("ID = ");
    scanf("%s", ID);
    sprintf(S1, "USER %s\r\n", ID);
    send(Sock, S1, strlen(S1), 0);
    Sleep(1000);

    // send pass
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

    // Read KB & Send Msg
    while (strncmp(S1, "quit", 4)) // input "quit" then stop while loop
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
        strcat(S1, "\r\n");

        // cd > CMD
        if (!strncmp(S1, "cd ", 3))
        {
            sscanf(S1, "%s %s\r\n", A, B);
            sprintf(S1, "CWD %s\r\n", B);
        }

        // mkdir > RMD
        else if (!strncmp(S1, "mkdir ", 6))
        {
            sscanf(S1, "%s %s\r\n", A, B);
            sprintf(S1, "MKD %s\r\n", B);
        }

        // rmdir > RMD
        else if (!strncmp(S1, "rmdir ", 6))
        {
            sscanf(S1, "%s %s\r\n", A, B);
            sprintf(S1, "RMD %s\r\n", B);
        }

        // ls > PASV > get_IP/PORT > start TCP Client > NLST
        else if (!strncmp(S1, "ls", 1))
        {
            strcpy(S1, "PASV\r\n");
            // Indicate NLST process status
            NLST_Flag = 1;
        }

        // get a.c > PASV > get_IP/PORT > start TCP Client > RETR a.c
        else if (!strncmp(S1, "get ", 4))
        {
            sscanf(S1, "%s %s\r\n", A, RETR_File);
            strcpy(S1, "PASV\r\n");
            // Indicate RETR process status
            RETR_Flag = 1;
        }

        // put a.c > PASV > get_IP/PORT > start TCP Client > STOR a.c
        else if (!strncmp(S1, "put ", 4))
        {
            sscanf(S1, "%s %s\r\n", A, STOR_File);
            strcpy(S1, "PASV\r\n");
            // Indicate STOR process status
            STOR_Flag = 1;
        }

        send(Sock, S1, strlen(S1), 0);
        Sleep(1000);
    }

    return 0;
}
