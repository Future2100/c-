//
//  main.cpp
//  tcp_listen
//
//  Created by future on 16/3/25.
//  Copyright © 2016年 future. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/errno.h>
#include <arpa/inet.h>

int tcp_listen(const char *host,const char *serv,socklen_t *addrlenp){
    int listenfd , n;
    const int on = 1;
    struct addrinfo hins,*res,*ressave;
    bzero(&hins, sizeof(hins));
    hins.ai_flags = AI_PASSIVE;
    hins.ai_family = AF_UNSPEC;
    hins.ai_socktype = SOCK_STREAM;
    
    if(( n = getaddrinfo(host, serv, &hins, &res)) != 0){
        printf("tcp_listen error for %s, %s : %s\n",host,serv,gai_strerror(n));
        exit(1);
    }
    ressave = res;
    do{
        listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if(listenfd < 0)
            continue;
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if(bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
            break;
        close(listenfd);                     // bind error,close and try again
    } while((res = res->ai_next) != NULL);
    if( res == NULL){
        printf("tcp_listen error for %s, %s\n",host,serv);
        exit(1);
    }
    listen(listenfd, 5);
    if(addrlenp)
        *addrlenp = res->ai_addrlen;
    freeaddrinfo(ressave);
    return listenfd;
    
    
}


#include <time.h>
#define MAXLINE 128
int main(int argc, const char * argv[]) {
    
    int listenfd,connfd;
    socklen_t len;
    char buf[MAXLINE];
    time_t ticks;
    struct sockaddr_storage clientaddr;
//    if( argc != 2){
//        printf("usage : daytimetcpserv <service or port #>\n");
//        exit(1);
//    }
   // listenfd = tcp_listen(nullptr, argv[1], nullptr);
    listenfd = tcp_listen(nullptr, "8888", nullptr);
    for (; ; ) {
        len = sizeof(clientaddr);
        connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &len);
        printf("connnect from %s\n",inet_ntoa(((sockaddr_in*)&clientaddr)->sin_addr));
        ticks = time(nullptr);
        snprintf(buf, sizeof(buf), "%.24s\r\n",ctime(&ticks));
        write(connfd, buf, sizeof(buf));
    }
    return 0;
}
