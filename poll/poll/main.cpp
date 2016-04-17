//
//  main.cpp
//  poll
//
//  Created by future on 16/3/23.
//  Copyright © 2016年 future. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <poll.h>
#include <strings.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h> //this header has sockaddr_in
#include <sys/errno.h>



#define MAXLINE 128

void sys_error(const char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, const char * argv[]) {

    int i,maxi,listenfd,connfd,sockfd;
    socklen_t clientlen;
    int nready;
    ssize_t n;
    char buf[MAXLINE];
    
    struct pollfd client[OPEN_MAX];
    struct sockaddr_in clientaddr,serveraddr;
    
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8888);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int bindret = bind(listenfd, (struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if( bindret< 0){
        sys_error("bind");
    }
    
    listen(listenfd,5);
    for(i = 1;i < OPEN_MAX;++i)
        client[i].fd = -1;
    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;
    maxi = 0;
    
    for(;;){
        nready = poll(client,maxi + 1,0xffffffff);
        if(client[0].revents & POLLRDNORM){
            clientlen = sizeof(clientaddr);
            connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
            for(i = 1;i < OPEN_MAX;++i){
                if(client[i].fd < 0){
                    client[i].fd = connfd;
                    break;
                }
            }
            if( i == OPEN_MAX)
            {
                printf("too many clients\n");
                break;
            }
            client[i].events = POLLRDNORM;
            if( i > maxi)
                maxi = i;
            if(--nready < 0)
                continue;
        }
        for(i = 1;i <= maxi ;++i){
            if((sockfd = client[i].fd) < 0)
                continue;
            if(client[i].revents & (POLLRDNORM | POLLERR)){
                if((n = read(sockfd,buf,MAXLINE)) < 0){
                    if(errno == ECONNRESET){
                        close(sockfd);
                        client[i].fd = -1;
                    }else {
                        sys_error("read error");
                    }
                } else  if(n < 0){
                    close(sockfd);
                    client[i].fd = -1;
                }
                else{
                    write(sockfd, buf,n);
                }
                if(--nready < 0)
                    break;
            }
        }
    }
    
    
    
    
    return 0;
}
