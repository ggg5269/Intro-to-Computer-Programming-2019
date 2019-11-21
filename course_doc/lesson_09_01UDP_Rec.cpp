#include "stdlib.h"
#include "stdio.h"

// ! for TCP/IP
#include "winsock2.h"
//#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "WS2_32")

int main(int argc, char *argv[])
{
    WSADATA Wsa;
    sockaddr_in Addr;
    SOCKET Sock;
    char S1[2000];

    WSAStartup(0x202, &Wsa);
    Sock = socket(AF_INET, SOCK_DGRAM, 0); // * `socket`: 開啟通道; SOCK_STREAM: TCP; SOCK_DGRAM: UDP
    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(6000);
    Addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    while (1)
    {
        printf("chat room: ");
        scanf("%s", S1);
        sendto(Sock, S1, strlen(S1), 0, (sockaddr *)&Addr, sizeof(sockaddr));
    }
    return 0;
}