//
//  Header.h
//  pcap
//
//  Created by future on 16/4/12.
//  Copyright © 2016年 future. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <pcap/pcap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* 默认捕获长度 (每个包捕获的最大长度)
 default snap length (maximum bytes per packet to capture) */
#define SNAP_LEN 1518

/* 以太网头部14个字节
 ethernet headers are always exactly 14 bytes [1] */
#define SIZE_ETHERNET 14

/* 以太网地址6个字节
 Ethernet addresses are 6 bytes */
#define ETHER_ADDR_LEN        6

#define EPT_IP   0x0800         /* type: IP */
#define EPT_ARP   0x0806        /* type: ARP */
#define EPT_RARP 0x8035         /* type: RARP */


/* Ethernet header */
struct sniff_ethernet {
    u_char  ether_dhost[ETHER_ADDR_LEN];    /* destination host address */
    u_char  ether_shost[ETHER_ADDR_LEN];    /* source host address */
    u_short ether_type;                     /* IP? ARP? RARP? etc */
};

/* IP header */
struct sniff_ip {
    u_char  ip_vhl;                 /* version << 4 | header length >> 2 */
    u_char  ip_tos;                 /* type of service */
    u_short ip_len;                 /* total length */
    u_short ip_id;                  /* identification */
    u_short ip_off;                 /* fragment offset field */
#define IP_RF 0x8000            /* reserved fragment flag */
#define IP_DF 0x4000            /* dont fragment flag */
#define IP_MF 0x2000            /* more fragments flag */
#define IP_OFFMASK 0x1fff       /* mask for fragmenting bits */
    u_char  ip_ttl;                 /* time to live */
    u_char  ip_p;                   /* protocol */
    u_short ip_sum;                 /* checksum */
    struct  in_addr ip_src,ip_dst;  /* source and dest address */
};
#define IP_HL(ip)               (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)                (((ip)->ip_vhl) >> 4)

/* TCP header */
typedef u_int tcp_seq;

struct sniff_tcp {
    u_short th_sport;               /* source port */
    u_short th_dport;               /* destination port */
    tcp_seq th_seq;                 /* sequence number */
    tcp_seq th_ack;                 /* acknowledgement number */
    u_char  th_offx2;               /* data offset, rsvd */
#define TH_OFF(th)      (((th)->th_offx2 & 0xf0) >> 4)
    u_char  th_flags;
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20
#define TH_ECE  0x40
#define TH_CWR  0x80
#define TH_FLAGS        (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
    u_short th_win;                 /* window */
    u_short th_sum;                 /* checksum */
    u_short th_urp;                 /* urgent pointer */
};


struct sniff_udp
{
    u_short m_usSourPort;    // 源端口号16bit
    u_short m_usDestPort;    // 目的端口号16bit
    u_short m_usLength;    // 数据包长度16bit
    u_short m_usCheckSum;    // 校验和16bit
} ;


struct sniff_arp

{
    u_short     arp_hrd;            /* format of hardware address */
    u_short     arp_pro;            /* format of protocol address */
    u_short     arp_hln;            /* length of hardware address */
    u_short     arp_pln;            /* length of protocol address */
    u_short     arp_op;             /* ARP/RARP operation */
    u_short     arp_sha[6];         /* sender hardware address */
    u_short     arp_spa;            /* sender protocol address */
    u_short     arp_tha[6];         /* target hardware address */
    u_short     arp_tpa;            /* target protocol address */
    
};


void
got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

void
print_payload(const u_char *payload, int len);

void
print_hex_ascii_line(const u_char *payload, int len, int offset);




#endif /* Header_h */
