#include "stdlib.h"
#include "stdio.h"

// ! for TCP/IP
#include "winsock2.h"
#pragma comment(lib, "Ws2_32.lib")
//#pragma comment(lib, "lws2_32.lib")

int main(int argc, char *argv[])
{
    WSADATA Wsa;
    SOCKADDR_IN Addr;
    SOCKADDR_IN Addr1;
    SOCKET Sock;
    char S1[2000];
    int i, Len = sizeof(SOCKADDR);

    WSAStartup(0x202, &Wsa);
    Sock = socket(AF_INET, SOCK_DGRAM, 0); // * `socket`: 開啟通道; SOCK_STREAM: TCP; SOCK_DGRAM: UDP
    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(6000);
    Addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(Sock, (SOCKADDR *)&Addr, Len);

    while (1)
    {
        i = recvfrom(Sock, S1, sizeof(S1) - 1, 0, (SOCKADDR *)&Addr1, &Len); // ! `-1` for substract EOF
        if (i > 0)
        {
            S1[i] = 0;
            printf("chat(%s):<%s", inet_ntoa(Addr1.sin_addr), S1);
        }
    }
    return 0;
}