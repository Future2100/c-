//
//  sniffer_header.cpp
//  pcap
//
//  Created by future on 16/4/12.
//  Copyright © 2016年 future. All rights reserved.
//

#include <stdio.h>
#include "sniffer_header.h"



/*
 * print data in rows of 16 bytes: offset   hex   ascii
 *
 * 00000   47 45 54 20 2f 20 48 54  54 50 2f 31 2e 31 0d 0a   GET / HTTP/1.1..
 */
void
print_hex_ascii_line(const u_char *payload, int len, int offset)
{
    
    int i;
    int gap;
    const u_char *ch;
    
    /* offset */
    printf("%05d   ", offset);
    
    /* hex */
    ch = payload;
    for(i = 0; i < len; i++) {
        printf("%02x ", *ch);
        ch++;
        /* print extra space after 8th byte for visual aid */
        if (i == 7)
            printf(" ");
    }
    /* print space to handle line less than 8 bytes */
    if (len < 8)
        printf(" ");
    
    /* fill hex gap with spaces if not full line */
    if (len < 16) {
        gap = 16 - len;
        for (i = 0; i < gap; i++) {
            printf("   ");
        }
    }
    printf("   ");
    
    /* ascii (if printable) */
    ch = payload;
    for(i = 0; i < len; i++) {
        if (isprint(*ch))
            printf("%c", *ch);
        else
            printf(".");
        ch++;
    }
    
    printf("\n");
    
    return;
}

/*
 * 打印包的有效载荷数据（避免打印二进制数据）
 * print packet payload data (avoid printing binary data)
 */
void print_payload(const u_char *payload, int len)
{
    
    int len_rem = len;
    int line_width = 16;                        /* 每行的字节数 | number of bytes per line */
    int line_len;
    int offset = 0;                     /* 从0开始的偏移计数器 | zero-based offset counter */
    const u_char *ch = payload;
    
    if (len <= 0)
        return;
    
    /* data fits on one line */
    if (len <= line_width) {
        print_hex_ascii_line(ch, len, offset);
        return;
    }
    
    /* 数据跨越多行 data spans multiple lines */
    for ( ;; ) {
        /* 计算当前行的长度 | compute current line length */
        line_len = line_width % len_rem;
        
        /* 显示分割线 | print line */
        print_hex_ascii_line(ch, line_len, offset);
        
        /* 计算总剩余 | compute total remaining */
        len_rem = len_rem - line_len;
        
        /* 转移到打印的剩余字节的指针
         shift pointer to remaining bytes to print */
        ch = ch + line_len;
        
        /* 添加偏移 | add offset */
        offset = offset + line_width;
        
        /* 检查是否有线宽字符或更少
         check if we have line width chars or less */
        if (len_rem <= line_width) {
            /* print last line and get out */
            print_hex_ascii_line(ch, len_rem, offset);
            break;
        }
    }
    
    return;
}


/*
 *显示mac地址
 */

void print_mac_addr(const struct sniff_ethernet *ethernet){
    printf("     src  mac : ");
    for (int i  = 0 ; i < ETHER_ADDR_LEN; ++i) {
        if(i == ETHER_ADDR_LEN -1)
            printf("%x",ethernet->ether_shost[i]);
        else
            printf("%x:",ethernet->ether_shost[i]);
    }
    printf("\n     dest mac : ");
    for (int i  = 0 ; i < ETHER_ADDR_LEN; ++i) {
        if(i == ETHER_ADDR_LEN -1)
            printf("%x",ethernet->ether_dhost[i]);
        else
            printf("%x:",ethernet->ether_dhost[i]);
    }
    printf("\n");
    
}


void print_tcp_packet(const u_char* packet,int ip_len){
    /*
     *  好，这个包是TCP.
     *  OK, this packet is TCP.
     */
    
    /* 定义/计算 TCP 头部偏移
     define/compute tcp header offset */
    
    const struct sniff_tcp * tcp = (struct sniff_tcp*)(packet);
    
    int size_tcp = TH_OFF(tcp)*4;
    if (size_tcp < 20) {
        printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
        return;
    }
    
    printf("     Src port : %d\n", ntohs(tcp->th_sport));
    printf("     Dst port : %d\n", ntohs(tcp->th_dport));
    
    /* 定义/计算TCP有效载荷（段）偏移
     define/compute tcp payload (segment) offset */
    u_char *payload = (u_char*)(packet  + size_tcp);
    
    /* 计算TCP有效载荷（段）的大小
     compute tcp payload (segment) size */
    
    int size_payload = ip_len - (size_tcp + sizeof(struct sniff_ip));
    
    /*
     * 打印有效载荷数据，它可能是二进制的，所以不要只把它作为一个字符串。
     * Print payload data; it might be binary, so don't just
     * treat it as a string.
     */
    if (size_payload > 0) {
        printf("   Payload (%d bytes):\n", size_payload);
        print_payload(payload, size_payload);
    }
    
}


void print_udp_packet(const u_char* packet){
    /*
     *  好，这个包是TCP.
     *  OK, this packet is TCP.
     */
    
    /* 定义/计算 TCP 头部偏移
     define/compute tcp header offset */
    
    const struct sniff_udp * udp = (struct sniff_udp*)(packet);
    
    int size_udp = htons(udp->m_usLength);
    if (size_udp < 8) {
        printf("   * Invalid UDP header length: %u bytes\n", size_udp);
        return;
    }
    
    printf("     Src port : %d\n", ntohs(udp->m_usSourPort));
    printf("     Dst port : %d\n", ntohs(udp->m_usDestPort));
    
    /* 定义/计算TCP有效载荷（段）偏移
     define/compute tcp payload (segment) offset */
    u_char *payload = (u_char*)(packet  + sizeof(sniff_udp));
    
    /* 计算TCP有效载荷（段）的大小
     compute tcp payload (segment) size */
    
    int size_payload = size_udp - sizeof(sniff_udp);
    
    /*
     * 打印有效载荷数据，它可能是二进制的，所以不要只把它作为一个字符串。
     * Print payload data; it might be binary, so don't just
     * treat it as a string.
     */
    if (size_payload > 0) {
        printf("   Payload (%d bytes):\n", size_payload);
        print_payload(payload, size_payload);
    }
    
}

/*
 * 解析/显示 包
 * dissect/print packet
 */
void
got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    
    static int count = 1;                   /* 包计数器                | packet counter */
    
    /* declare pointers to packet headers */
    const struct sniff_ethernet *ethernet;  /* 以太网头部        | The ethernet header [1] */
    const struct sniff_ip *ip;              /* IP 头部                | The IP header */
    
    
    
    int size_ip;
    
    /* 显示包总数 */
    printf("\nPacket number %d:\n", count);
    count++;
    
    /* 定义以太网头部
     define ethernet header */
    
    ethernet = (struct sniff_ethernet*)(packet);
    print_mac_addr(ethernet);
    
    switch(htons(ethernet->ether_type)){
        case EPT_IP:
        {
            ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
            size_ip = IP_HL(ip)*4;
            if (size_ip < 20) {
                printf("   * Invalid IP header length: %u bytes\n", size_ip);
                return;
            }
            /* 显示源IP和目的IP*/
            printf("         From : %s\n", inet_ntoa(ip->ip_src));
            printf("           To : %s\n", inet_ntoa(ip->ip_dst));
            switch(ip->ip_p) {
                case IPPROTO_TCP:
                    printf("     Protocol : TCP\n");
                    print_tcp_packet(packet + size_ip + SIZE_ETHERNET,htons(ip->ip_len));
                    return;
                case IPPROTO_UDP:
                    printf("     Protocol : UDP\n");
                    print_udp_packet(packet + size_ip + SIZE_ETHERNET);
                    return;
                case IPPROTO_ICMP:
                    printf("     Protocol : ICMP\n");
                    return;
                case IPPROTO_IP:
                    printf("     Protocol : IP\n");
                    return;
                default:
                    printf("     Protocol : unknown\n");
                    return;
            }

        }
        break;
        case EPT_ARP:
            printf("\t\tarp\n");
            break;
        case EPT_RARP:
            printf("\t\trarp\n");
            break;
        default:
            printf("\t\tother type \n");
            break;
    }
    
    return;
}

