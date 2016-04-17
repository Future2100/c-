#ifndef SNI_HEADER_H_INCLUDED
#define SNI_HEADER_H_INCLUDED

#include <iostream>
#include "winsock2.h"
#include "mstcpip.h "
#pragma commemt(lib,"ws2_32lib")

using namespace std;

/************IP�����ײ��ṹ*****************/
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

/**************ICMP��ͷ��*************************/
typedef struct _ICMPHeader
{
    char icType;
    char icCode;
    unsigned short icCksum;
    unsigned short icId;
    unsigned short icSeq;
    unsigned long timeStamp;
}ICMPHeader;

/*****************UDP��ͷ���ṹ***************************/
typedef struct _UDPHeader
{
    unsigned short sourcePort;
    unsigned short destinationPort;
    unsigned short len;
    unsigned short checksum;
}UDPHeader;

/*****************TCP��ͷ���ṹ***********************/
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
/******************TCP����������********************************/
void DecodeTCPPacket(char *pData)
{
    TCPHeader *pTCPHdr = (TCPHeader *)pData;
    cout<<"TCPԴ�˿ڣ�"<<ntohs(pTCPHdr ->sourcePort)<<endl;
    cout<<"Ŀ�Ķ˿ڣ�"<<ntohs(pTCPHdr->destinationPort)<<endl;
}

/******************UDP����������********************************/
void DecodeUDPPacket(char *pData)
{
    UDPHeader *pUDPHdr = (UDPHeader *)pData;
    cout<<"UDPԴ�˿ڣ�"<<ntohs(pUDPHdr ->sourcePort)<<endl;
    cout<<"Ŀ�Ķ˿ڣ�"<<ntohs(pUDPHdr->destinationPort)<<endl;
}

/******************ICMP����������********************************/
void DecodeICMPPacket(char *pData)
{
    ICMPHeader *pICMPHdr = (ICMPHeader *)pData;
    cout<<"ICMP���ͣ�"<<pICMPHdr->icType<<"���룺"<<pICMPHdr->icCode<<endl;
    switch(pICMPHdr ->icType)
    {
    case 0 :
        cout<<"������Ӧ��\n";break;
    case 8 :
        cout<<"��������\n";break;
    case 3 :
        cout<<"Ŀ�겻�ɴ\n";break;
    case 11:
        cout<<"���ݱ���ʱ��TTL = 0��.\n";break;
    }
}

/*****************IP�����������*********************/
void DecodeIPPacket(char *pData)
{
    IPHeader *pIPHdr = (IPHeader*)pData;
    in_addr source,dest;
    char szSourceIp[32],szDestIp[32];

    /****************��ipͷȡ��Դip��ַ��Ŀ��ip��ַ***********************/
    source.S_un.S_addr = pIPHdr ->ipSource;
    dest.S_un.S_addr = pIPHdr ->ipDestination;
    strcpy(szSourceIp , inet_ntoa(source));
    strcpy(szDestIp , inet_ntoa(dest));
    cout<<"ԴIP��"<<szSourceIp<<endl;
    cout<<"Ŀ��IP��"<<szDestIp<<endl;
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
        cout<<"Э��ţ�",pIPHdr->ipProtocol;

    }
}

/******************TCP����������********************************
void DecodeTCPPacket(char *pData)
{
    TCPHeader *pTCPHdr = (TCPHeader *)pData;
    cout<<"TCPԴ�˿ڣ�"<<ntohs(pTCPHdr ->sourcePort)<<endl;
    cout<<"Ŀ�Ķ˿ڣ�"<<notohs(pTCPHdr->destinationPort)<<endl;
}
*/

/******************UDP����������********************************
void DecodeUDPPacket(char *pData)
{
    UDPHeader *pUDPHdr = (UDPHeader *)pData;
    cout<<"UDPԴ�˿ڣ�"<<ntohs(pUDPHdr ->sourcePort)<<endl;
    cout<<"Ŀ�Ķ˿ڣ�"<<notohs(pUDPHdr->destinationPort)<<endl;
}

/******************ICMP����������********************************
void DecodeICMPPacket(char *pData)
{
    ICMPHeader *pICMPHdr = (ICMPHeader *)pData;
    cout<<"ICMP���ͣ�"<<pICMPHdr->icType<<"���룺"<<pICMPHdr->icCode<<endl;
    switch(pICMPHdr ->icType)
    {
    case 0 :
        cout<<"������Ӧ��\n";break;
    case 8 :
        cout<<"��������\n";break;
    case 3 :
        cout<<"Ŀ�겻�ɴ\n";break;
    case 11:
        cout<<"���ݱ���ʱ��TTL = 0��.\n";break;
    }
}

*/

#endif // SNI_HEADER_H_INCLUDED
