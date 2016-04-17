//
//  ftpfiletransmit.cpp
//  ftpserver
//
//  Created by future on 16/4/8.
//  Copyright © 2016年 future. All rights reserved.
//

#include "ftpfiletransmit.hpp"
#include "filemanager.hpp"
#include "mysocket.hpp"
#include <math.h>


ftpfiletransmit::ftpfiletransmit(int clientsockfd,
                                 const char *filename,                                 
                                 unsigned short port):
clientsockfd(clientsockfd),filename(filename),port(port){
    int fd = open(filename, O_RDONLY);
    std::cout << filename << std::endl;
    if(fd  < 0){
        perror("open");
        exit(1);

    }
    size = filemanager::getfilecontentsizebyfd(fd);
    addr = (char*)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if(addr == MAP_FAILED){
        perror("mmap");
        exit(1);
    }
}

void *pthread_transimit_func(void *arg){
    static int counter = 1;
    std::cout << counter ++ << std::endl;
    pthread_detach(pthread_self());
    threadmm *tm = (threadmm*)arg;
    sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);
    getsockname(tm->clientsockfd, (sockaddr*)&clientaddr, &len);

againc:
    mysocket ms(clientaddr.sin_addr,tm->port);
    int ret = ms.myconnect();
    if(ret < 0){
        usleep(5);
        goto againc;
    }
    
    size_t nleft = tm->transmitlength;
    int had  = 0;
    while (nleft) {
        size_t len = 0;
        if(nleft >= MSS)
            len = write(ms.listenfd, tm->addr + tm->off + had, MSS);
        else {
            len=  write(ms.listenfd, tm->addr + tm->off + had, nleft);
        }
        nleft -= len;
        had += len;
    }
    shutdown(ms.listenfd, SHUT_WR);
    return NULL;
}


void ftpfiletransmit::send(){
    int length = ceil((size + 0.0) / SLICE);
    threadmm *tm = new threadmm[length];//会内存泄露
    for (int i = 0; i <  length; ++i) {
        pthread_t pth;
        tm[i].addr = addr;
        tm[i].off = i*SLICE;
        tm[i].port = port + i;//需要客服端传过来
        tm[i].clientsockfd = clientsockfd;
        tm[i].transmitlength = SLICE;
        if(i == (length -1)){
            tm[i].transmitlength = size % SLICE;
        }
        pthread_create(&pth, NULL, pthread_transimit_func, &tm[i]);
    }
    
}