#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>  // Project => Setting => LINK  => Library=ws2_32.lib
#include <process.h>  // Project => Setting => C/C++ => Category=Code Generation => Use Runtime Library=Debug Multithreaded

// ==================  �Ұ� TCP Server(�ϥ�thread�����s�u�P�������)   ===
int  Start_TCP_Server(SOCKET *psockfd,WORD Port)
{
WSADATA  wsadata; int      err;
struct   sockaddr_in  tcpserver;
  // 1. �}�� TCP Server
  if ((err=WSAStartup(0x202,&wsadata))!=0) return -1;
  if ((*psockfd=socket(AF_INET,SOCK_STREAM,0))<0) return -1;
  tcpserver.sin_family=AF_INET;
  tcpserver.sin_port=htons(Port);
  tcpserver.sin_addr.s_addr=htonl(INADDR_ANY);
  if (bind(*psockfd,(struct sockaddr *)&tcpserver,sizeof(tcpserver))<0) return -1;
  if ((err=listen(*psockfd,SOMAXCONN))<0) return -1;
  return 0;
}

// ==================  �Ұ� TCP Client   =================================
int Start_TCP_Client(SOCKET *psockfd,WORD R_Port,char *IP)
{
WSADATA  wsadata;
int      err;
sockaddr_in  tcpclient;

  if ((err=WSAStartup(0x202,&wsadata))!=0) return -1;
  if ((*psockfd=socket(AF_INET,SOCK_STREAM,0))<0) return -1;
  tcpclient.sin_family=AF_INET;
  tcpclient.sin_port=htons(R_Port);
  tcpclient.sin_addr.s_addr=inet_addr(IP);
  if (err=connect(*psockfd,(sockaddr *)&tcpclient,sizeof(tcpclient))<0) return -1;
  return 0;
}

// ==================  �Ұ� UDP Client   =================================
void Start_UDP_Client(SOCKET *Socket,sockaddr_in *lpAddr,char *IP,int Port)
{
WSADATA     wsadata;

  WSAStartup(0x202,&wsadata);            // �Ұ�Winsock
  *Socket=socket(AF_INET,SOCK_DGRAM,0);  // TCP socket open
  lpAddr->sin_family=AF_INET;
  lpAddr->sin_port=htons(Port);
  lpAddr->sin_addr.s_addr=inet_addr(IP);
}

// ==================  �Ұ� UDP Server   ============
void Start_UDP_Server(SOCKET *Socket,int Port)
{
WSADATA      wsadata;
sockaddr_in  Addr;

  // 1. �Ұ� UDP Server
  WSAStartup(0x202,&wsadata);
  *Socket=socket(AF_INET,SOCK_DGRAM,0);
  Addr.sin_family     =AF_INET;
  Addr.sin_port       =htons(Port);
  Addr.sin_addr.s_addr=htonl(INADDR_ANY);
  bind(*Socket,(sockaddr *)&Addr,sizeof(sockaddr));
}