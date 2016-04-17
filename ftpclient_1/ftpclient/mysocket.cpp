//
//  mysocket.cpp
//  ftpserver
//
//  Created by future on 16/4/8.
//  Copyright © 2016年 future. All rights reserved.
//

#include "mysocket.hpp"

void sys_error(const char *msg){
    perror(msg);
    exit(1);
}
mysocket::mysocket(){
    
}


mysocket::mysocket(const char *addr,int port){
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        sys_error("socket");
    }
    
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(addr);
    
    const int reuse = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof reuse);
    
    
}

mysocket::mysocket(in_addr addr,int port){
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        sys_error("socket");
    }
    
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr = addr;
    
    const int reuse = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof reuse);
    
    
}


int mysocket::mybind(){
    int ret;
    if((ret = ::bind(listenfd,(sockaddr*)&serveraddr,sizeof(serveraddr))) < 0)
        sys_error("bind");
    return ret;
}

int mysocket::mylisten(){
    int ret;
    if((ret = listen(listenfd, LISTENQ)) < 0)
        sys_error("lsiten");
    return ret;
}

int mysocket::myaccept(){
    clientlen = sizeof(clientaddr);
again:
    if((clientfd = ::accept(listenfd, (sockaddr*)&clientaddr  ,&clientlen)) < 0)
    {
        if( errno == EINTR)
            goto again;
        else
            sys_error("accept");
    }else {
       // std::cout << inet_ntoa(clientaddr.sin_addr) << "已连接" << std::endl;
    }
    return clientfd;

}

int mysocket::myconnect(){
    int ret;
    serverlen = sizeof(sockaddr);
    if((ret = ::connect(listenfd, (sockaddr*)&serveraddr, serverlen)) < 0)
        sys_error("connect");
    return ret;
}



