//
//  main.cpp
//  tcp_conect
//
//  Created by future on 16/3/26.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <iostream>
#include <string>
#include <netdb.h>



int tcp_connnect(const char *host,const char *serv){
    int sockfd,n;
    struct addrinfo hints,*res,*ressave;
    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if((n = getaddrinfo(host, serv, &hints, &res)) != 0){
        std::cout << "tcp connect error for  " << host << " : " << serv << std::endl;
        exit(1);
    }
    ressave = res;
    do{
        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if(sockfd < 0)
            continue;
        if(connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
            break;
        close(sockfd);
    } while ((res = res->ai_next) != nullptr);
    if(res ==  nullptr)
    {
        std::cout << "tcp_connnect error for " << host << " : " << serv << std::endl;
        freeaddrinfo(ressave);

    }
    return sockfd;
}

int main(int argc, const char * argv[]) {
   
    int connfd = tcp_connnect("127.0.0.1", "8888");
    char buf[128];
    ssize_t n;
    while ((n = read(connfd, buf, sizeof buf)) > 0) {
        buf[n] = 0;
        fputs(buf, stdout);
    }
    
    
    
    return 0;
}
