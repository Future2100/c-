//
//  main.cpp
//  ftpserver
//
//  Created by future on 16/4/6.
//  Copyright © 2016年 future. All rights reserved.
//

#include <iostream>
#include "ftpserver.hpp"
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include "filemanager.hpp"
#include <sys/socket.h>


void *deal_with(void *arg);


int main(){
    int listenfd = 0;
    
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        ftpserver::sys_error("socket");
    }
    sockaddr_in serveraddr;
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8888);
    serveraddr.sin_addr.s_addr = htonl(0);
    
    const int reuse = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof reuse);
    
    if(::bind(listenfd,(sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
        ftpserver::sys_error("bind");
    if(listen(listenfd, LISTENQ) < 0)
        ftpserver::sys_error("lsiten");
    
    while(1){
        
        pthread_t pth;
        socklen_t clientlen = sizeof(serveraddr);
        int tempclientfd  = ::accept(listenfd, nullptr, &clientlen);
        pthread_create(&pth, nullptr, deal_with, &tempclientfd);
    }

    
    
    return 0;
}