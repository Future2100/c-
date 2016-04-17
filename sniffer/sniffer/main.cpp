//
//  main.cpp
//  sniffer
//
//  Created by future on 16/4/9.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <strings.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/in_systm.h>
#include <netinet/if_ether.h>


using namespace std;
/*
 1.创建原始套接字、
 2.设置套接字选项
 3.创建并填充相应协议头
 */


void sys_error(const char *msg){
    perror(msg);
    exit(1);
}


int main(int argc, const char * argv[]) {
 
    int listenfd = socket(AF_INET, SOCK_RAW, 0);
    
//    struct sockaddr_in listenaddr;
//    bzero(&listenaddr, sizeof listenaddr);
//    listenaddr.sin_port = htons(0);
//    listenaddr.sin_family = AF_INET;
//    listenaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
//    if(::bind(listenfd,(sockaddr*)&listenaddr,sizeof listenaddr) < 0){
//        perror("bind");
//    }
    struct ifreq ethreq;
    strncpy(ethreq.ifr_name,"en0",IFNAMSIZ);
    ioctl(listenfd, SIOCGIFFLAGS, &ethreq);
    ethreq.ifr_flags |= IFF_PROMISC;
    if( -1 == ioctl(listenfd, SIOCSIFFLAGS, &ethreq)){
        sys_error("ioctl");
    }
    
  //  u_long value = 1;
//    if(ioctl(listenfd, SIOCGIFFLAGS,&value) != 0){
//        perror("IOCTL");
//    }
    
    
    char buf[4096] = {0};
    while (1) {
        ssize_t   ret = recvfrom (listenfd, buf, sizeof (buf), 0, NULL, NULL);//recv(listenfd, buf, sizeof buf , 0);
        if(ret < 0){
            perror("recvfrom");
        }

        if( strlen(buf) > 0){
            char *ethhead = buf;
            printf("Source MAC address: "
                   "%02x:%02x:%02x:%02x:%02x:%02x\n",
                   ethhead[0],ethhead[1],ethhead[2],
                   ethhead[3],ethhead[4],ethhead[5]);
            printf("Destination MAC address: "
                   "%02x:%02x:%02x:%02x:%02x:%02x\n",
                   ethhead[6],ethhead[7],ethhead[8],
                   ethhead[9],ethhead[10],ethhead[11]);
            
            char *iphead = buf+14; /* Skip Ethernet header */
            if (*iphead==0x45) { /* Double check for IPv4
                                  * and no options present */
                printf("Source host %d.%d.%d.%d\n",
                       iphead[12],iphead[13],
                       iphead[14],iphead[15]);
                printf("Dest host %d.%d.%d.%d\n",
                       iphead[16],iphead[17],
                       iphead[18],iphead[19]);
                printf("Source,Dest ports %d,%d\n",
                       (iphead[20]<<8)+iphead[21],
                       (iphead[22]<<8)+iphead[23]);
                printf("Layer-4 protocol %d\n",iphead[9]);
                
        }

        
        }
    }
    
    
    return 0;
}
