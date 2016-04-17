#ifndef SNI_HEADER_H_INCLUDED
#define SNI_HEADER_H_INCLUDED

#include <iostream>
#include "winsock2.h"
#include "mstcpip.h "
#pragma commemt(lib,"ws2_32lib")

using namespace std;

/************IP分组首部结构*****************/
typedef struct _IPHeader
{
    unsigned char iphVerLen;
    unsigned char ipTos;
    unsigned short ipLength;
    unsigned short ipId;
    unsigned short ipFlags;
    unsigned char ipTTL;
    unsigned char ipProtocol;
    unsigned short ipChecksum;
    unsigned long  ipSource;
    unsigned short ipDestination;
}IPHeader,*PIPHeader;

/**************ICMP包头部*************************/
typedef struct _ICMPHeader
{
    char icType;
    char icCode;
    unsigned short icCksum;
    unsigned short icId;
    unsigned short icSeq;
    unsigned long timeStamp;
}ICMPHeader;

/*****************UDP包头部结构***************************/
typedef struct _UDPHeader
{
    unsigned short sourcePort;
    unsigned short destinationPort;
    unsigned short len;
    unsigned short checksum;
}UDPHeader;

/*****************TCP包头部结构***********************/
typedef struct _TCPHeader
{
    unsigned short sourcePort;
    unsigned short destinationPort;
    unsigned long sequenceNumber;
    unsigned long acknowledgeNumber;
    char dataoffset;
    char flags;
    unsigned short windows;
    unsigned short checksum;
    unsigned short urgentPointer;
}TCPHeader;
/******************TCP包解析函数********************************/
void DecodeTCPPacket(char *pData)
{
    TCPHeader *pTCPHdr = (TCPHeader *)pData;
    cout<<"TCP源端口："<<ntohs(pTCPHdr ->sourcePort)<<endl;
    cout<<"目的端口："<<ntohs(pTCPHdr->destinationPort)<<endl;
}

/******************UDP包解析函数********************************/
void DecodeUDPPacket(char *pData)
{
    UDPHeader *pUDPHdr = (UDPHeader *)pData;
    cout<<"UDP源端口："<<ntohs(pUDPHdr ->sourcePort)<<endl;
    cout<<"目的端口："<<ntohs(pUDPHdr->destinationPort)<<endl;
}

/******************ICMP包解析函数********************************/
void DecodeICMPPacket(char *pData)
{
    ICMPHeader *pICMPHdr = (ICMPHeader *)pData;
    cout<<"ICMP类型："<<pICMPHdr->icType<<"代码："<<pICMPHdr->icCode<<endl;
    switch(pICMPHdr ->icType)
    {
    case 0 :
        cout<<"回显响应。\n";break;
    case 8 :
        cout<<"回显请求。\n";break;
    case 3 :
        cout<<"目标不可达。\n";break;
    case 11:
        cout<<"数据报超时（TTL = 0）.\n";break;
    }
}

/*****************IP分组解析函数*********************/
void DecodeIPPacket(char *pData)
{
    IPHeader *pIPHdr = (IPHeader*)pData;
    in_addr source,dest;
    char szSourceIp[32],szDestIp[32];

    /****************从ip头取出源ip地址和目的ip地址***********************/
    source.S_un.S_addr = pIPHdr ->ipSource;
    dest.S_un.S_addr = pIPHdr ->ipDestination;
    strcpy(szSourceIp , inet_ntoa(source));
    strcpy(szDestIp , inet_ntoa(dest));
    cout<<"源IP："<<szSourceIp<<endl;
    cout<<"目的IP："<<szDestIp<<endl;
    int nHeaderLen = (pIPHdr ->iphVerLen &0xf) * sizeof(ULONG);
    switch(pIPHdr ->ipProtocol)
    {
    case IPPROTO_TCP:
        DecodeTCPPacket(pData + nHeaderLen);
        break;
    case IPPROTO_UDP:
        DecodeUDPPacket(pData + nHeaderLen);
        break;
    case IPPROTO_ICMP:
        DecodeICMPPacket(pData + nHeaderLen);
        break;
    default:
        cout<<"协议号：",pIPHdr->ipProtocol;

    }
}

/******************TCP包解析函数********************************
void DecodeTCPPacket(char *pData)
{
    TCPHeader *pTCPHdr = (TCPHeader *)pData;
    cout<<"TCP源端口："<<ntohs(pTCPHdr ->sourcePort)<<endl;
    cout<<"目的端口："<<notohs(pTCPHdr->destinationPort)<<endl;
}
*/

/******************UDP包解析函数********************************
void DecodeUDPPacket(char *pData)
{
    UDPHeader *pUDPHdr = (UDPHeader *)pData;
    cout<<"UDP源端口："<<ntohs(pUDPHdr ->sourcePort)<<endl;
    cout<<"目的端口："<<notohs(pUDPHdr->destinationPort)<<endl;
}

/******************ICMP包解析函数********************************
void DecodeICMPPacket(char *pData)
{
    ICMPHeader *pICMPHdr = (ICMPHeader *)pData;
    cout<<"ICMP类型："<<pICMPHdr->icType<<"代码："<<pICMPHdr->icCode<<endl;
    switch(pICMPHdr ->icType)
    {
    case 0 :
        cout<<"回显响应。\n";break;
    case 8 :
        cout<<"回显请求。\n";break;
    case 3 :
        cout<<"目标不可达。\n";break;
    case 11:
        cout<<"数据报超时（TTL = 0）.\n";break;
    }
}

*/

#endif // SNI_HEADER_H_INCLUDED
